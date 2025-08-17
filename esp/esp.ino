/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.13 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.15.01 or later version;
     - for iOS 1.12.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__WIFI_POINT

#include <SoftwareSerial.h>
#include <WiFi.h>
#include <ESP32Servo.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 264 bytes
  { 255,0,0,57,0,1,1,19,0,0,0,0,4,1,106,200,1,1,5,0,
  71,5,16,42,42,56,3,88,24,80,0,0,0,0,0,0,128,68,0,0,
  72,67,0,0,72,66,0,0,72,66,24,0,135,0,0,225,67,0,0,47,
  68,94,0,0,0,0,0,0,225,67,36,0,0,47,68,0,0,122,68,71,
  58,18,42,42,56,3,74,24,80,0,0,0,0,0,0,128,68,0,0,72,
  67,0,0,72,66,0,0,72,66,24,0,135,0,0,225,67,0,0,47,68,
  94,0,0,0,0,0,0,225,67,36,0,0,47,68,0,0,122,68,71,57,
  68,42,42,56,3,88,24,80,0,0,0,0,0,0,128,68,0,0,72,67,
  0,0,72,66,0,0,72,66,24,0,135,0,0,225,67,0,0,47,68,94,
  0,0,0,0,0,0,225,67,36,0,0,47,68,0,0,122,68,71,5,67,
  42,42,56,3,74,24,80,0,0,0,0,0,0,128,68,0,0,72,67,0,
  0,72,66,0,0,72,66,24,0,135,0,0,225,67,0,0,47,68,94,0,
  0,0,0,0,0,225,67,36,0,0,47,68,0,0,122,68,67,2,124,101,
  9,1,24,41 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  float Soil_moisture1; // from 0 to 1024
  float Soil_moisture2; // from 0 to 1024
  float Soil_moisture4; // from 0 to 1024
  float Soil_moisture3; // from 0 to 1024
  char value_01[41]; // string UTF8 end zero

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
int t1,t2,h1,h2,l,w,f,average;
 float s1,s2,s3,s4;

Servo xAxisServo; // Servo for X-axis
Servo yAxisServo; // Servo for Y-axis

// Light-dependent resistor (LDR) pin definitions
const int ldrTopLeft = 34;  // Analog pin on ESP32
const int ldrTopRight = 35; // Analog pin on ESP32
const int ldrBottomLeft = 32; // Analog pin on ESP32
const int ldrBottomRight = 33; // Analog pin on ESP32



// Servo pin definitions
const int xServoPin = 25; // PWM pin on ESP32
const int yServoPin = 26; // PWM pin on ESP32

// Servo angle limits
int xPosition = 90; // Initial position of X-axis servo
int yPosition = 90; // Initial position of Y-axis servo
const int angleStep = 1; // Step size for servo movement
const int threshold = 50; // Light intensity difference threshold

SoftwareSerial NodeSerial(16, 17);


void setup() 
{
  
  RemoteXY_Init (); 
  Serial.begin(115200);
  NodeSerial.begin(57600);
  
  // TODO you setup code
   xAxisServo.attach(xServoPin);
  yAxisServo.attach(yServoPin);

  // Set initial servo positions
  xAxisServo.write(90);
  yAxisServo.write(90);


   pinMode(12, OUTPUT);


  Serial.println("Solar Tracker Initialized.");
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();

  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 
while (NodeSerial.available() > 0) {
    t1 = NodeSerial.parseFloat();
     h1 = NodeSerial.parseFloat();
     t2 = NodeSerial.parseFloat();
     h2 = NodeSerial.parseFloat();
     s1 = NodeSerial.parseFloat();
     s2 = NodeSerial.parseFloat();
     s3 = NodeSerial.parseFloat();
     s4 = NodeSerial.parseFloat();
     l = NodeSerial.parseFloat();
     w = NodeSerial.parseFloat();
     f = NodeSerial.parseFloat();
    
    if (NodeSerial.read() == '\n') {
      Serial.print("H1: "); Serial.println(h1);
      Serial.print("H2: "); Serial.println(h2);
      Serial.print("T1: "); Serial.println(t1);
      Serial.print("T2: "); Serial.println(t2);
      Serial.print("S1: "); Serial.println(s1);
      Serial.print("S2: "); Serial.println(s2);
      Serial.print("S3: "); Serial.println(s3);
      Serial.print("S4: "); Serial.println(s4);
      Serial.print("L: "); Serial.println(l);
      Serial.print("F: "); Serial.println(f);
      Serial.print("W: "); Serial.println(w); 
  }

  }


// Read LDR values
  int topLeft = analogRead(ldrTopLeft);
  int topRight = analogRead(ldrTopRight);
  int bottomLeft = analogRead(ldrBottomLeft);
  int bottomRight = analogRead(ldrBottomRight);

average=(topLeft+topRight+bottomLeft+bottomRight)/4;
if(average<300)
{digitalWrite(12,0);}
else
{digitalWrite(12,1);}
Serial.println(average);



  // Calculate averages for horizontal and vertical axes
  int avgTop = (topLeft + topRight) / 2;
  int avgBottom = (bottomLeft + bottomRight) / 2;
  int avgLeft = (topLeft + bottomLeft) / 2;
  int avgRight = (topRight + bottomRight) / 2;

  // Adjust X-axis servo
  if (abs(avgLeft - avgRight) > threshold) {
    if (avgLeft > avgRight && xPosition < 180) {
      xPosition += angleStep;
    } else if (avgLeft < avgRight && xPosition > 0) {
      xPosition -= angleStep;
    }
    xAxisServo.write(xPosition);
  }

  // Adjust Y-axis servo
  if (abs(avgTop - avgBottom) > threshold) {
    if (avgTop > avgBottom && yPosition < 180) {
      yPosition += angleStep;
    } else if (avgTop < avgBottom && yPosition > 0) {
      yPosition -= angleStep;
    }
    yAxisServo.write(yPosition);
  }

  // Debug output
 // Serial.print("TopLeft: "); Serial.print(topLeft);
 // Serial.print(" TopRight: "); Serial.print(topRight);
 // Serial.print(" BottomLeft: "); Serial.print(bottomLeft);
 // Serial.print(" BottomRight: "); Serial.println(bottomRight);

  delay(100); // Delay for stability

char humidityData[40];
char tempData[40];

sprintf(humidityData, "H1:%d%%  H2:%d%% T1:%dC T2:%dC", h1, h2, t1, t2);



RemoteXY.Soil_moisture1=s1;
RemoteXY.Soil_moisture2=s2;
RemoteXY.Soil_moisture3=s3;
RemoteXY.Soil_moisture4=s4;

memcpy(&RemoteXY.value_01, humidityData, strlen(humidityData));



}