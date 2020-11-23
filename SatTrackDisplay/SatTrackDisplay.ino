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

String azimuth;
String altitude;

// place to store incoming characters
String inputBuffer    = "";
bool   stringComplete = false;
char   command;

// Make custom symbols
byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte az[8] = {
  B01000,
  B10100,
  B11100,
  B10100,
  B00111,
  B00001,
  B00010,
  B00111,
};

byte al[8] = {
  B01000,
  B10100,
  B11100,
  B10100,
  B00010,
  B00010,
  B00010,
  B00011,
};

byte angle[8] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00010,
  B00100,
  B01010,
  B11111,
};

byte compass[8] = {
  B00100,
  B01110,
  B11111,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
};

// Custom character names
#define DEGREE  byte(0)
#define AZ      byte(1)
#define AL      byte(2)
#define ANGLE   byte(3)
#define COMPASS byte(4)

void displayAzAl() {
  lcd.setCursor(0,1);
  
  char s[17];
  snprintf(s, sizeof(s), "%7s%8s",azimuth.c_str(),altitude.c_str());
  lcd.print(s);

  lcd.setCursor(0,1);
  lcd.write(COMPASS);
  lcd.setCursor(7,1);
  lcd.write(DEGREE);
  lcd.write(ANGLE);
  lcd.setCursor(15,1);
  lcd.write(DEGREE);
//  lcd.write(byte(2));
//  lcd.write(byte(3));
//  lcd.write(byte(4));
}

void writeLine(int row) {
  lcd.setCursor(0,row);
  lcd.print("                ");
  lcd.setCursor(0,row);
  lcd.print(inputBuffer.substring(1));
}

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  lcd.createChar(0, degree);
  lcd.createChar(1, az);
  lcd.createChar(2, al);
  lcd.createChar(3, angle);
  lcd.createChar(4, compass);
  
  lcd.clear();
  lcd.print("Waiting for data");

  delay(200);
}

void loop() {
  if (stringComplete) {
    
    String strfirstChar;
    strfirstChar = inputBuffer[0];
    strfirstChar.toLowerCase();
    char command = strfirstChar[0];
    
    switch (command) {
      case '1':
        writeLine(0);
        break;
      case '2':
        writeLine(1);
        break;
      case 'z':
        azimuth = inputBuffer.substring(1);
        displayAzAl();
        break;
      case 'l':
        altitude = inputBuffer.substring(1);
        displayAzAl();
        break;
      default:
        lcd.clear();
        lcd.print("BAD\nCOMMAND");
        lcd.setCursor(0,1);
        lcd.print(inputBuffer);
        break;
    }

    inputBuffer = "";
    stringComplete = false;
    
    }
  }
  
/*   
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
   }

  
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


// This is apparently some sort of interrupt handler
// I believe it is automaatically called whenever
// a characters comes down the serial port
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
