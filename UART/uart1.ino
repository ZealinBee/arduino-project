#include <LiquidCrystal.h>

LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

void setup(){
  Serial.begin(9600);
  Serial.println("Write something to the serial monitor.");
   lcd.begin(20, 4);
}

void loop(){
  if (Serial.available() > 0){
    String message = Serial.readStringUntil('\n'); 
    Serial.print("Message received, content: ");  
    Serial.println(message);

    int pos_s = -1;

    if(message.startsWith("LCD")) {
      pos_s = message.indexOf(":");
      if(pos_s > -1) {
        String stat = message.substring(pos_s + 1);
        if(stat == "Hi" || stat == "hi") {
           Serial.println("Command = LCD, Check yo LCD ");
           lcd.setCursor(0, 0);
           lcd.print("Hi");
        }else {
          	Serial.println("Wrong command");
        }
      }else {
        Serial.println("Remember to add :");
      }
    }else if(message.startsWith("Print")) {
       Serial.println("Command = Print ");
       pos_s = message.indexOf(":");
 
      if (pos_s > -1){
        String stat = message.substring(pos_s + 1);
        if (stat == "Hi" || stat == "hi") {
          Serial.println("Hi!");
        }
        else if (stat == "Hello") {
          Serial.println("Hello there!");
        }
        else {
          Serial.println("Wrong command");
        }
      }  
    }
    else{
	    Serial.println("No greeting found, try typing Print:Hi or Print:Hello, or LCD:Hello\n");
    }
  }
}