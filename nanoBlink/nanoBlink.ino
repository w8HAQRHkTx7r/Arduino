#define FASTLED_INTERNAL
#include <FastLED.h>
#include "MACELib.h"

#define NUM_LEDS    256
#define DATA_PIN      3
#define CLOCK_PIN    13
#define PAUSE        10
#define BRIGHTNESS   100 
#define VOLTS         5
#define MAX_mAMPS   500
#define DELAY      1000

CRGB leds[NUM_LEDS];

void setup() { 
    pinMode(LED_BUILTIN,OUTPUT);
    cereal();
}

int mapScreenToMatrix(int row, int col) {
  int newCol = (row % 2 == 0) ? newCol = 15 - col : newCol = col;
  return row * 16 + newCol;
  }  

void printBitmap(uint16_t bitmap[], CRGB myColor) {
  Serial.println(myColor);
  for (int row=0; row<16; row++) {
    for (int col=0; col<16; col++) {
        if (bitRead(bitmap[row],col)) {
          Serial.print("x");
        }
        else {
          Serial.print(" ");
        }
      }
        Serial.println(" ");
    }
}

uint16_t tryzub[16] = {
  0b0000000100000000,
  0b0000000100000000,
  0b0010001110001000,
  0b0011000100011000,
  0b0010100100101000,
  0b0010101110101000,
  0b0011001010011000,
  0b0011101010111000,
  0b0010110101101000,
  0b0010010101001000,
  0b0011111111111000,
  0b0000010001000000,
  0b0000011011000000,
  0b0000000100000000,
  0b0000000100000000,
  0b0000000100000000
};

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DELAY);
  printBitmap(tryzub, CRGB::Yellow);
  digitalWrite(LED_BUILTIN, LOW);
  delay(DELAY);
}
   
