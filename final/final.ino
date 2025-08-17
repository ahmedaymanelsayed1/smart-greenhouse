#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 20, 4);

// تعريف نوع الموتور: A4988 = DRIVER (1)
AccelStepper stepper(AccelStepper::DRIVER, 9, 8); // STEP = 9, DIR = 8

// تعريف الريلاي
#define RELAY_1  22
#define RELAY_2  23
#define RELAY_3  24
#define RELAY_4  25
#define RELAY_5  26
#define RELAY_6  27
#define RELAY_7  28
int relayPins[] = {RELAY_1, RELAY_2, RELAY_3, RELAY_4, RELAY_5, RELAY_6, RELAY_7};

// تعريف الأزرار
#define BUTTON_1 30
#define BUTTON_2 31
#define BUTTON_3 32
#define BUTTON_4 33
#define BUTTON_5 34
#define BUTTON_6 35
#define BUTTON_7 36
int buttonPins[] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7};

// المسافات لكل مشروب
const int stepsPerDrink[] = {0, 2000, 4000, 6000, 8000, 10000, 12000, 14000};
int currentPosition = 0;

void setup() {
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Select a Drink:");

  for (int i = 0; i < 7; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // الريلاي مطفي بالبداية
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(7, OUTPUT); // ENABLE pin for A4988
  digitalWrite(7, LOW); // تفعيل الموتور

  stepper.setMaxSpeed(1000); // اضبط السرعة
  stepper.setAcceleration(500); // واضبط التسارع
}

void moveToDrink(int drinkNumber) {
  if (drinkNumber < 1 || drinkNumber > 7) return;

  int targetPosition = stepsPerDrink[drinkNumber];
  stepper.moveTo(targetPosition);
  
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  delay(300);

  digitalWrite(relayPins[drinkNumber - 1], LOW); // تشغيل الريلاي
  delay(5000);
  digitalWrite(relayPins[drinkNumber - 1], HIGH); // إيقاف
  currentPosition = targetPosition;
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("1.Cola 2.Fanta 3.Juice");
  lcd.setCursor(0, 2);
  lcd.print("4.Soda 5.Water 6.Tea");
  lcd.setCursor(0, 3);
  lcd.print("7.Coffee");

  for (int i = 0; i < 7; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      moveToDrink(i + 1);
      delay(500);
    }
  }
}