#include <LiquidCrystal.h>

LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

int analogValue1;
int joystickPosition;
int buttonPin = 19;

bool buttonPressed = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("kartoshka gang");
  lcd.setCursor(0, 1);
  lcd.print("We love potato");
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(19), isPressedHandler, 2);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  analogValue1 = analogRead(A8);
  joystickPosition = map(analogValue1, 0, 1023, 0, 19);
  lcd.clear();

  // Display analogValue1 (Potentiometer) on the first row
  lcd.setCursor(0, 0);
  lcd.print("X-position");

  lcd.setCursor(0, 1);
  lcd.print("-100%    0%   +100%");

  lcd.setCursor(joystickPosition, 2);
  lcd.print("|");

  // Button pressed printing
  if (buttonPressed) {
    Serial.println("Button Pressed");
    buttonPressed = false;
  }


  delay(5);

}

void isPressedHandler() {
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonPressed = true;
    lastDebounceTime = millis();
  }
}