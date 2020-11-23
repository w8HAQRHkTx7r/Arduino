// This is an operations test of the 1602 LCD that came with my Elegoo Uno R3 Starter Kit.
// It displays some text on line 1 and random integers representing azimuth and altitude of the ISS
// on line 2.  
// The loop runs every second.
// This code does not test turning the backlight on and off.
// The wiring diagram is based on the diagram that came with the Starter Kit.



// www.elegoo.com
// 2016.12.9

/*
  LiquidCrystal Library - LCD test

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

  The circuit:
 *  1 LCD VSS to ground
 *  2 LCD VDD to 5V
 *  3 LCD V0  to pot wiper
 *  4 LCD RS  to digital pin 7
 *  5 LCD R/W to ground
 *  6 LCD E   to digital pin 8
 *  7 LCD D0  unused
 *  8 LCD D1  unused
 *  9 LCD D2  unused
 * 10 LCD D3  unused
 * 11 LCD D4  to digital pin 9
 * 12 LCD D5  to digital pin 10
 * 13 LCD D6  to digital pin 11
 * 14 LCD D7  to digital pin 12
 * 15 LCD A   to 5V
 * 16 LCD K   to ground
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int azimuth;
int altitude;

// place to store incoming characters
String inputBuffer = "";
bool stringComplete = false;
String command = "";

// Make a custom "degree" symbol
byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
};

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  lcd.clear();
  lcd.write("Waiting for data");
  delay(2000);
}

void readSerialPort() {
}


void loop() {
  if (stringComplete) {
    if (inputBuffer.startsWith("1")) {
      // Print a text message to line 1
      lcd.setCursor(0,0);
      lcd.print(inputBuffer.substring(1));
    }
    else if (inputBuffer.startsWith("2")) {
      // Print Azimuth
      lcd.setCursor(0,1);
      lcd.print(inputBuffer.substring(1));
    }
    else {
      // Print unknown input error
      lcd.clear();
      lcd.print("BAD COMMAND");
      lcd.setCursor(0,1);
      lcd.print(inputBuffer);
    }
    inputBuffer = "";
    stringComplete = false;
  }
  
/*   
  lcd.setCursor(0, 0);
  lcd.write("ISS is at");
  
  lcd.setCursor(0, 1);
  lcd.write("Az: ");
  lcd.print(azimuth);
  lcd.write(byte(0));

  lcd.write(" Al: ");
  lcd.print(altitude);
  lcd.write(byte(0));
*/

}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
      return;
    }
    inputBuffer += inChar;
  }
}
