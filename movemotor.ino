#include <LiquidCrystal.h>
#include <Wire.h>

#define Motor_forward         0
#define Motor_return          1
#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10

int analogValue1;
int analogValue2;
int joystickPositionX;
int joystickPositionY;

const int encoderPinA = 2; // A channel
const int encoderPinB = 3; // B channel

int encoderValue = 0;
int lastEncoderValue = 0;

LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

void setup()
{

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("ENC B Pulses: ");

  Serial.begin(9600);
}

void loop() {
  int pwm_R = 0;
  int pwm_L = 0;
  int left = 0;
  int right = 0;

  while (true) {
    analogValue1 = analogRead(A8); // y
    analogValue2 = analogRead(A9); // x
    joystickPositionY = map(analogValue1, 0, 1023, -100, 100); // Invert Y-axis
    joystickPositionX = map(analogValue2, 0, 1023, -100, 100); // Invert X-axis
    // Calculate motor speeds based on joystick positions
    int baseSpeed = map(abs(joystickPositionY), 0, 100, 0, 255);
    int steering = map(joystickPositionX, -100, 100, -255, 255);

    pwm_L = baseSpeed + steering;
    pwm_R = baseSpeed - steering;

    // Ensure that the motor speeds are within the valid range (0-255)
    pwm_L = constrain(pwm_L, 0, 255);
    pwm_R = constrain(pwm_R, 0, 255);

    // Set the direction pins based on joystick position
    if (joystickPositionY < 0) {
      left = 1;
      right = 1;
    } else if (joystickPositionY > 0) {
      left = 0;
      right = 0;
    }

    analogWrite(Motor_L_pwm_pin, 0);
      analogWrite(Motor_R_pwm_pin, 0);
    // Apply the motor control signals
    // digitalWrite(Motor_R_dir_pin, right);
    // digitalWrite(Motor_L_dir_pin, left);
    // analogWrite(Motor_L_pwm_pin, pwm_L);
    // analogWrite(Motor_R_pwm_pin, pwm_R);

    // Add a delay for control loop stability (adjust as needed)
    //delay(20); // 50 Hz update rate for control

    // Stop the motors if the joystick is centered
    // if (joystickPositionY == 0 && joystickPositionX == 0) {
    //   analogWrite(Motor_L_pwm_pin, 0);
    //   analogWrite(Motor_R_pwm_pin, 0);
    // }
    int encoderStateB = digitalRead(encoderPinB);
    while (encoderValue<470){
      encoderValue++;
      lcd.setCursor(13, 0);
      lcd.print(encoderValue);
      Serial.println(encoderValue);
      analogWrite(Motor_L_pwm_pin, 255);
      analogWrite(Motor_R_pwm_pin, 255);
    }   
    
    lastEncoderValue = encoderStateB;
    analogWrite(Motor_L_pwm_pin, 0);
    analogWrite(Motor_R_pwm_pin, 0);
    encoderValue=0;
    while (encoderValue<470){
      encoderValue++;
      lcd.print(encoderValue);
      analogWrite(Motor_R_pwm_pin, pwm_R);
      analogWrite(Motor_R_pwm_pin, 255);
    }
    
  }
}