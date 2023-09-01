#include <LiquidCrystal.h>

LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

float analogValue1, analogValue2;

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
  analogValue2 = analogRead(A1);

  // Clear the LCD
  lcd.clear();

  // Display analogValue1 (Potentiometer) on the first row
  lcd.setCursor(0, 0);
  lcd.print("Pot.meter = ");
  lcd.print(analogValue1 * 5.0 / 1023.0, 2); // Display voltage with 2 decimal places
  lcd.print("V");
  // Display analogValue2 (3.3V level) on the second row

  lcd.setCursor(0, 1);
  lcd.print("3.3 level = ");
  lcd.print(analogValue2 * 5.0 / 1023.0, 2); // Display voltage with 2 decimal places
  lcd.print("V");

  delay(100);

}
