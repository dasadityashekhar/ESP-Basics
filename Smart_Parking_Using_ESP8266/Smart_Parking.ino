#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD configuration
#define SDA_PIN D2
#define SCL_PIN D1
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Confirmed LCD I2C address

// IR sensor pins
#define SLOT1_IR D0
#define SLOT2_IR D3
#define SLOT3_IR D4
#define SLOT4_IR D7
#define ENTRY_IR D5
#define EXIT_IR D6  // Active HIGH sensor

// Servo motor pins
#define ENTRY_SERVO_PIN D8
#define EXIT_SERVO_PIN D9  // Use an available free GPIO pin

Servo entryServo;
Servo exitServo;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("System Loading...");
  delay(2000);
  lcd.clear();

  pinMode(SLOT1_IR, INPUT);
  pinMode(SLOT2_IR, INPUT);
  pinMode(SLOT3_IR, INPUT);
  pinMode(SLOT4_IR, INPUT);
  pinMode(ENTRY_IR, INPUT);
  pinMode(EXIT_IR, INPUT);

  entryServo.attach(ENTRY_SERVO_PIN);
  exitServo.attach(EXIT_SERVO_PIN);

  entryServo.write(0);
  exitServo.write(90);
}

void loop() {
  // Read IR sensor states for parking slots
  bool slot1 = digitalRead(SLOT1_IR);
  bool slot2 = digitalRead(SLOT2_IR);
  bool slot3 = digitalRead(SLOT3_IR);
  bool slot4 = digitalRead(SLOT4_IR);

  int emptySlots = (slot1 == HIGH) + (slot2 == HIGH) + (slot3 == HIGH) + (slot4 == HIGH);

  // Entry Gate Logic (active LOW)
  if (digitalRead(ENTRY_IR) == LOW) {
    lcd.clear();
    if (emptySlots > 0) {
      lcd.setCursor(0, 0);
      lcd.print("Slot Available");
      lcd.setCursor(0, 1);

      if (slot1 == HIGH) lcd.print("Go to Slot 1");
      else if (slot2 == HIGH) lcd.print("Go to Slot 2");
      else if (slot3 == HIGH) lcd.print("Go to Slot 3");
      else if (slot4 == HIGH) lcd.print("Go to Slot 4");

      entryServo.write(90);
      delay(3000);
      entryServo.write(0);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("  Parking Full  ");
      lcd.setCursor(0, 1);
      lcd.print("Please Come Later");
      delay(3000);
    }
    lcd.clear();
  }

  // Exit Gate Logic (active HIGH)
  if (digitalRead(EXIT_IR) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Exit Gate Open");
    exitServo.write(0);
    delay(3000);
    exitServo.write(90);
    lcd.clear();
  }

  // Show status on default screen
  lcd.setCursor(0, 0);
  lcd.print("Empty Slots: ");
  lcd.print(emptySlots);
  lcd.print("  "); // Clear leftover chars

  lcd.setCursor(0, 1);
  lcd.print("Smart Parking");

  delay(500);
}
