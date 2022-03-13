// This program takes a multi-character message and scrolls it across
// a LED matrix

#define FASTLED_INTERNAL
#import "BitArray.h"
#include <FastLED.h>
#include "MACELib.h"

// Message parameters
#define MESSAGE_WIDTH 80 // The number of columns in the messasge This should be calculable
#define LETTER_HEIGHT 12 // Number of rows in each letter

// LED Matrix parameters
#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH  16
#define NUM_LEDS      MATRIX_HEIGHT * MATRIX_WIDTH

#define DATA_PIN 3
#define CLOCK_PIN 13
#define PAUSE 10
#define BRIGHTNESS 100
#define VOLTS 5
#define MAX_mAMPS 500

#define SPEED 100
#define printMatrix false

CRGB leds[NUM_LEDS];
CRGB color = CRGB::White;

BitArray message;

int lastMessageColumn = MESSAGE_WIDTH - 1;
int currentMessageColumn = 0;

void getNextMessageRow() {
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    leds[mapScreenToMatrix(row, 15)] = CRGB::Black;
  }
  uint16_t bitrow = message.get(currentMessageColumn);
  for (int b = 0; b < LETTER_HEIGHT; b++) {
    if (bitRead(bitrow, b) == 1) {
      leds[mapScreenToMatrix(b, 15)] = CRGB::White;
    }
  }
  currentMessageColumn = (currentMessageColumn + 1) % MESSAGE_WIDTH;
}

void scrollMatrixLeft(int scrollDelay) {
//  FastLED.clear();
  for (int col = 0; col < MESSAGE_WIDTH; col++) {
    int x = MATRIX_WIDTH - 1; // index of leftmost pixel in the 0th row
    int y = ((MATRIX_WIDTH - 1) * MATRIX_WIDTH) - 1; // index of pixel to the left of the rightmost
    for (int start = x; start <= y; start += MATRIX_WIDTH * 2) {
      for (int p = start; p > start - (MATRIX_WIDTH - 1); p--) {
        leds[p] = leds[p - 1];
      }
      for (int p = start + 1; p < start + 1 + (MATRIX_WIDTH - 1); p++) {
        leds[p] = leds[p + 1];
      }
    }
    getNextMessageRow();
    FastLED.show();
    delay(scrollDelay);
    if (printMatrix) {printLEDMatrix();}
  }
}

void printLEDMatrix() {
  Serial.println("print LED matrix");
  int x = MATRIX_WIDTH - 1; // index of leftmost pixel in the 0th row
  int y = ((MATRIX_WIDTH - 1) * MATRIX_WIDTH) - 1; // index of pixel to the left of the rightmost
  for (int start = x; start <= y; start += MATRIX_WIDTH * 2) {
    for (int p = start; p >= start - (MATRIX_WIDTH - 1); p--) {
      if (leds[p] == color) { Serial.print("@");} else {Serial.print(".");}
    }
    Serial.println(" ");
    for (int p = start + 1; p <= start + 1 + (MATRIX_WIDTH - 1); p++) {
      if (leds[p] == color) {Serial.print("@");} else {Serial.print(".");}
    }
    Serial.println(" ");
  }
  delay(250);
}

void slavaUkraine() {
  message.begin(LETTER_HEIGHT, MESSAGE_WIDTH);
  message.clear();
  message.set(0, 0x3f8);
  message.set(1, 0x404);
  message.set(2, 0x404);
  message.set(3, 0x404);
  message.set(4, 0x208);
  message.set(5, 0x000);
  message.set(6, 0x400);
  message.set(7, 0x300);
  message.set(8, 0x0fc);
  message.set(9, 0x004);
  message.set(10, 0x004);
  message.set(11, 0x7fc);
  message.set(12, 0x000);
  message.set(13, 0x7f8);
  message.set(14, 0x044);
  message.set(15, 0x044);
  message.set(16, 0x044);
  message.set(17, 0x7f8);
  message.set(18, 0x000);
  message.set(19, 0x7fc);
  message.set(20, 0x444);
  message.set(21, 0x444);
  message.set(22, 0x444);
  message.set(23, 0x3b8);
  message.set(24, 0x000);
  message.set(25, 0x7f8);
  message.set(26, 0x044);
  message.set(27, 0x044);
  message.set(28, 0x044);
  message.set(29, 0x7f8);
  message.set(30, 0x000);
  message.set(31, 0x000);
  message.set(32, 0x000);
  message.set(33, 0x000);
  message.set(34, 0x00c);
  message.set(35, 0x030);
  message.set(36, 0x7c0);
  message.set(37, 0x030);
  message.set(38, 0x00c);
  message.set(39, 0x000);
  message.set(40, 0x7fc);
  message.set(41, 0x040);
  message.set(42, 0x0a0);
  message.set(43, 0x318);
  message.set(44, 0x404);
  message.set(45, 0x000);
  message.set(46, 0x7fc);
  message.set(47, 0x044);
  message.set(48, 0x044);
  message.set(49, 0x044);
  message.set(50, 0x038);
  message.set(51, 0x000);
  message.set(52, 0x7f8);
  message.set(53, 0x044);
  message.set(54, 0x044);
  message.set(55, 0x044);
  message.set(56, 0x7f8);
  message.set(57, 0x000);
  message.set(58, 0x405);
  message.set(59, 0x7fc);
  message.set(60, 0x405);
  message.set(61, 0x000);
  message.set(62, 0x7fc);
  message.set(63, 0x040);
  message.set(64, 0x040);
  message.set(65, 0x040);
  message.set(66, 0x7fc);
  message.set(67, 0x000);
  message.set(68, 0x404);
  message.set(69, 0x7fc);
  message.set(70, 0x404);
  message.set(71, 0x000);
  message.set(72, 0x000);
  message.set(73, 0x000);
  message.set(74, 0x000);
  message.set(75, 0x000);
  message.set(76, 0x000);
  message.set(77, 0x000);
  message.set(78, 0x000);
  message.set(79, 0x000);
}

// Convert from (0,0) in upper left to matrix index
int mapScreenToMatrix(int row, int col) {
  // Switch from increasing left to right into
  // increasing right to left for even numbered rows
  // Then compute a linear pixel offset
  int newCol = (row % 2 == 0) ? newCol = (MATRIX_WIDTH - 1) - col : newCol = col;
  return row * MATRIX_WIDTH + newCol;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  cereal();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  set_max_power_indicator_LED(LED_BUILTIN);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  // This is the message that will scroll
  // Adjust the message parameter defines
  // (These parameters should be encapsulated)
  slavaUkraine(); // This is the message that will scroll

}

void loop() {
  scrollMatrixLeft(SPEED);
}
