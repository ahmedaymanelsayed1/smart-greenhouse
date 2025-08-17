#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "DHT.h"

// إعداد شاشة LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // عنوان I2C: 0x27، وأبعاد الشاشة: 16x2

SoftwareSerial UnoSerial(11, 12); // RX=11  TX=12

#define DHTPIN1 3 // Pin connected to first DHT sensor
#define DHTPIN2 4 // Pin connected to second DHT sensor
#define DHTTYPE DHT11  // DHT 11
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

int t1, t2, h1, h2, l, w, f;
int s1, s2, s3, s4, b1, b2;

void setup() {
  // إعداد شاشة الـ LCD
  lcd.init();       // تهيئة الشاشة
  lcd.backlight();  // تشغيل الإضاءة الخلفية
  SET_LCD_Boot();

  Serial.begin(115200);
  Serial.println("System start");
  UnoSerial.begin(57600); // Serial communication
  dht1.begin();
  dht2.begin();
  pinMode(2,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,INPUT);
  pinMode(13,INPUT);
  digitalWrite(9,0);
  digitalWrite(8,1);
}

void loop() {
  h1 = dht1.readHumidity();
  h2 = dht2.readHumidity();
  t1 = dht1.readTemperature();
  t2 = dht2.readTemperature();
  s1 = analogRead(0);
  s2 = analogRead(1);
  s3 = analogRead(2);
  s4 = analogRead(3);
  //l = analogRead(4);
 // w = digitalRead(8);
  f = digitalRead(2);
b1=digitalRead(10);
b2=digitalRead(13);
  // Mapping sensor values
  l = map(l, 0, 1023, 1023, 0);
  s1 = map(s1, 0, 1023, 1023, 0);
  s2 = map(s2, 0, 1023, 1023, 0);
  s3 = map(s3, 0, 1023, 1023, 0);
  s4 = map(s4, 0, 1023, 1023, 0);

 if(t1>35||t2>35)
 {
  digitalWrite(7,1);
  digitalWrite(6,0);
 }
 
 if(t1<28||t2<28)
 {
  digitalWrite(6,1);
  digitalWrite(7,0);
 }

 if(h1>80||h2>80)
 {
  digitalWrite(6,0);
  digitalWrite(7,0);
 }

 if(h1<50||h2<50)
 {
  digitalWrite(6,1);
  digitalWrite(7,1);
 }

 if(f==0)
 {
  digitalWrite(9,0);
  delay(1000);
  digitalWrite(9,1);
  delay(1000);
 }


 if(s1<450||s2<450 ||s3<450||s4<450)
 {
  digitalWrite(8,0);
 }

 if(s1>600||s2>600 ||s3>600||s4>600)
 {
  digitalWrite(8,1);
 }

String humidityData = "H1:" + String(h1) + "% H2:" + String(h2) +"% " ;
String tempData = "T1:" + String(t1) + "C T2:" + String(t2) + "C ";

String soil1 = "S1:" + String(s1) + " S2:" + String(s2) +" " ;
String soil2 = "S3:" + String(s1) + " S4:" + String(s2) +" " ;


if(b1==1)
 {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(humidityData);
 lcd.setCursor(0, 1);
 lcd.print(tempData);
 }

if(b2==1)
 {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(soil1);
 lcd.setCursor(0, 1);
 lcd.print(soil2);
 }

  
    UnoSerial.print(t1);
    UnoSerial.print(" ");
    UnoSerial.print(h1);
    UnoSerial.print(" ");
    UnoSerial.print(t2);
    UnoSerial.print(" ");
    UnoSerial.print(h2);
    UnoSerial.print(" ");
    UnoSerial.print(s1);
    UnoSerial.print(" ");
    UnoSerial.print(s2);
    UnoSerial.print(" ");
    UnoSerial.print(s3);
    UnoSerial.print(" ");
    UnoSerial.print(s4);
    UnoSerial.print(" ");
    UnoSerial.print(w);
    UnoSerial.print(" ");
    UnoSerial.print(f);
    UnoSerial.print(" ");
    UnoSerial.print(l);
    UnoSerial.print("\n");
  

  // عرض البيانات على شاشة LCD
 

  Serial.print("H1: "); Serial.println(h1);
  Serial.print("H2: "); Serial.println(h2);
  Serial.print("T1: "); Serial.println(t1);
  Serial.print("T2: "); Serial.println(t2);
  Serial.print("S1: "); Serial.println(s1);
  Serial.print("S2: "); Serial.println(s2);
  Serial.print("S3: "); Serial.println(s3);
  Serial.print("S4: "); Serial.println(s4);
  Serial.print("L: "); Serial.println(l);
 

  delay(250); // انتظر قليلاً قبل التحديث التالي
}

void SET_LCD_Boot() {
  lcd.setCursor(0, 0);
  lcd.print(" WELCOME to ");
  lcd.setCursor(0, 1);
  lcd.print(" PROJECT ");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("lena's team ");
  delay(1200);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1- temp&hum");
  lcd.setCursor(0, 1);
  lcd.print("2- soil");
}