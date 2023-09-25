#include <LiquidCrystal.h>

LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

int analogValue1;
int joystickPosition;

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("kartoshka gang");
  lcd.setCursor(0, 1);
  lcd.print("We love potato");
  Serial.begin(9600);
}

void loop() {
  analogValue1 = analogRead(A0);
  // analogValue2 = analogRead(A1);

  joystickPosition = map(analogValue1, 0, 1023, 0, 19);

  // Clear the LCD
  lcd.clear();

//   Display analogValue1 (Potentiometer) on the first row
  lcd.setCursor(0, 0);
  lcd.print("X-position");

  lcd.setCursor(0, 1);
  lcd.print("-100%     0%   +100%");

  lcd.setCursor(joystickPosition, 2);
  lcd.print("|");

  delay(100);
}
