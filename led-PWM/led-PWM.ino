#include <LiquidCrystal.h>

LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

int analogValue1;
int analogValue2;
int brightness;
int finalBrightness1;
int finalBrightness2;
int buttonPin = 19;

const int led1 = 2;
const int led2 = 3;
bool lightOn = true;

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
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(19), isPressedHandler, 2);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  analogValue1 = analogRead(A8); // red
  analogValue2 = analogRead(A9); // green
  brightness = map(analogValue1, 0, 1023, 0, 255);
  finalBrightness1 = map(analogValue2, 0, 1023, 0, brightness);
  finalBrightness2 = map(analogValue2, 0, 1023, brightness, 0);

   if(lightOn == false) {
    finalBrightness1 = 0;
    finalBrightness2 = 0;
  }
  analogWrite(led1, finalBrightness1);
  analogWrite(led2, finalBrightness2);


  // Button pressed printing
  if (buttonPressed) {
    Serial.println("Current status of light: ");
    lightOn = !lightOn;
    Serial.println(lightOn);
    buttonPressed = false; 
  }

  delay(10);

}

void isPressedHandler() {
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonPressed = true;
    lastDebounceTime = millis();
  }
}