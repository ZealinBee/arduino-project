#include <Wire.h>
#include <LiquidCrystal.h>

#define CMPS14_address 0x60 // I2C slave address for CMPS compass module

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

void setup() {
    Wire.begin(); // Initialize the Wire library
    Serial.begin(9600);

    // Set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
}

void loop() {
    Wire.beginTransmission(CMPS14_address);
    Wire.write(0x02); // Access register 2 (register 2 = high byte of heading value)
    Wire.endTransmission(false); // Send the byte queued by Wire.write and keep the connection active

    Wire.requestFrom(CMPS14_address, 2, true); // Request 2 bytes from the module

    if (Wire.available() >= 2) {
      // Check that at least two bytes are available to read
      byte highByte = Wire.read(); // Read the high byte of the heading value
      byte lowByte = Wire.read(); // Read the low byte of the heading value

      int heading = (highByte << 8) + lowByte; // Combine the two bytes to get the full heading value
      int degrees = heading / 10;

      // Print the degree value to the LCD
      lcd.setCursor(0, 0);
      lcd.print(degrees);
      lcd.print(" degrees");

      int direction = degrees / 45;
      String direction_string;
      switch (direction) {
        case 0:
          direction_string = "N";
          break;
        case 1:
          direction_string = "NE";
          break;
        case 2:
          direction_string = "E";
          break;
        case 3:
          direction_string = "SE";
          break;
        case 4:
          direction_string = "S";
          break;
        case 5:
          direction_string = "SW";
          break;
        case 6:
          direction_string = "W";
          break;
        case 7:
          direction_string = "NW";
          break;
        case 8:
          direction_string = "N";
          break;
      }

      lcd.setCursor(0, 1);
      lcd.print(direction_string);
      delay(200);
      lcd.clear();
    }

    delay(100); // Wait for 100 milliseconds before the next loop
}
