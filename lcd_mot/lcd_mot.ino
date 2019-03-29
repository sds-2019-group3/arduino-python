/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   LCD v0 pin to +5v (330 ohm)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensor = 7;
int state = LOW;
int val = 0;

int stat = 0;

void setup() {
  //Open the Serial for Python communication
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //Set up Motion Sensor
  pinMode(sensor, INPUT_PULLUP);
  lcd.clear();
  delay(1000);
}

void loop() {
  //lcd.print
  //lcd.setCursor
  //lcd.clear

  //Read motion sensor
  val = digitalRead(sensor);
  if (val == HIGH) {
    //Request room status from Python script
    Serial.println(val);
    delay(2000);
    while(!Serial.available()){  }
    char response = Serial.read();
    //Print response from Python script
    lcd.setCursor(0,1);
    if (response == '1') {
      lcd.print("Room free");
      delay(5000);
    }
    else {
      lcd.print("Room not free");
      delay(5000);
    }
    lcd.clear();
    val = LOW;
  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Room 225");
    delay(500);
  }
}
