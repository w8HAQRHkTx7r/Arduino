#define FASTLED_INTERNAL
#include <FastLED.h>
#include "MACELib.h"

#define NUM_LEDS 256
#define DATA_PIN 3
#define CLOCK_PIN 13
#define PAUSE 10
#define BRIGHTNESS 100
#define VOLTS 5
#define MAX_mAMPS 500
#define DELAY 3000

#define DEBUG_BITMAP false

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  cereal();

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  set_max_power_indicator_LED(LED_BUILTIN);
}

int mapScreenToMatrix(int row, int col) {
  int newCol = (row % 2 == 0) ? newCol = 15 - col : newCol = col;
  return row * 16 + newCol;
}

void showBitmap(uint16_t bitmap[], CRGB myColor) {
  FastLED.clear();
  for (int row = 0; row < 16; row++) {
    for (int col = 0; col < 16; col++) {
      if (bitRead(bitmap[row], col)) {
        int ledIndex = mapScreenToMatrix(row,col);
        leds[ledIndex] = myColor;
      }
    }
  }
  FastLED.show();
}

void printBitmap(uint16_t bitmap[], CRGB myColor) {
  Serial.print(myColor);
  for (int row = 0; row < 16; row++) {
    for (int col = 0; col < 16; col++) {
      if (bitRead(bitmap[row], col)) {
        Serial.print("x");
      } else {
        Serial.print(" ");
      }
    }
  }
  Serial.println(" ");
}

void ukrainianFlag() {
  FastLED.clear();
  int topHalf = 256 / 2;
  for (int i = 32; i < topHalf; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = topHalf; i < 256 - 32; i++) {
    leds[i] = CRGB::Yellow;
  }
  FastLED.show();
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
  if (DEBUG_BITMAP) {
    printBitmap(tryzub, CRGB::Yellow);
  }
  showBitmap(tryzub, CRGB::Yellow);
  delay(DELAY);
  ukrainianFlag();
  delay(DELAY);
}
