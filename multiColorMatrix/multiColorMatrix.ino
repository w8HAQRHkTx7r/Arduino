// This program takes a bitmap several bitmap arrays, each in a 
// different color, and combines them onto an LED matrix

#define FASTLED_INTERNAL
#include <FastLED.h>

// LED Matrix parameters
#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH  16
#define NUM_LEDS      MATRIX_HEIGHT * MATRIX_WIDTH

#define DATA_PIN     3
#define CLOCK_PIN   13
#define PAUSE       10
#define BRIGHTNESS 20
#define VOLTS        5
#define MAX_mAMPS  500

CRGB leds[NUM_LEDS];
CRGB testColor = CRGB::Black;  // Used for printing

#define DEBUG_PRINT true

// bitmap design for ukrainian tryzub
uint16_t stem[] = {
0x0000,
0x0600,
0x0300,
0x0380,
0x0FE0,
0x0240,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
};
uint16_t pumpkin[] = {
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x1DB0,
0x3FF8,
0x739C,
0x739C,
0x7EFC,
0x7C7C,
0x77DC,
0x3838,
0x1FF0,
0x0FE0,
0x0000,
};

CRGB eyeColor = CRGB::White;
uint16_t eyes[] = {
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0840,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
};
uint16_t teeth[] = {
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0280,
0x0000,
0x0000,
0x0000,
};

// print bitmap from memory
void printBitmap(uint16_t bitmap[],  int bitmapLength, CRGB myColor) {
  Serial.println("Bitmap to follow:");
  Serial.println("xxxx  fedcba9876543210 fedcba9876543210");

  // Print the symbols
  for (int row = 0; row < bitmapLength; row++) {
    
    // Print the hex
    char hexVal[4];
    sprintf(hexVal, "%04X ", bitmap[row]);
    Serial.print(hexVal); Serial.print(" ");

    // Print the binary
    for (unsigned int test = 0x8000; test; test >>= 1) {
      Serial.print(bitmap[row] & test ? '1' : '0');
    }
    Serial.print(" ");
    
    for (int col = 15; col >=0; col--) {
      if (bitRead(bitmap[row], col)) {
        Serial.print("x");
      } else {
        Serial.print(".");
      }
    }
    Serial.println(" ");
  }
}
void scrollMatrixLeft(int scrollDelay) {
//  //  FastLED.clear();
//  for (int col = 0; col < MESSAGE_WIDTH; col++) {
//    int x = MATRIX_WIDTH - 1; // index of leftmost pixel in the 0th row
//    int y = ((MATRIX_WIDTH - 1) * MATRIX_WIDTH) - 1; // index of pixel to the left of the rightmost
//    for (int start = x; start <= y; start += MATRIX_WIDTH * 2) {
//      for (int p = start; p > start - (MATRIX_WIDTH - 1); p--) {
//        leds[p] = leds[p - 1];
//      }
//      for (int p = start + 1; p < start + 1 + (MATRIX_WIDTH - 1); p++) {
//        leds[p] = leds[p + 1];
//      }
//    }
//
//    FastLED.show();
//    delay(scrollDelay);
//
//    // Clear the entire rightmost column to black
//    for (int row = 0; row < MATRIX_HEIGHT; row++) {
//      leds[ledsInLastColumn[row]] = CRGB::Black;
//    }
//
//    // For each bit in the row that's a 1, light up its matrix LED
//    for (int b = 0; b < 16; b++) {
//      if (bitRead(slava[currentMessageColumn], b) == 1) {
//        leds[ledsInLastColumn[b]] = CRGB::White;
//      }
//    }
//    currentMessageColumn = (currentMessageColumn + 1) % MESSAGE_WIDTH;
//
//    if (DEBUG_PRINT) {
//      printLEDMatrix();
//    }
//    FastLED.show();
//    delay(scrollDelay);
//  }
}
void moveEyes() {
  // Black left eye
  leds[mapScreenToMatrix(7, 5)] = CRGB::Black;
  leds[mapScreenToMatrix(7, 6)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 5)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 6)] = CRGB::Black;
  // Black right eye
  leds[mapScreenToMatrix(7, 10)] = CRGB::Black;
  leds[mapScreenToMatrix(7, 11)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 10)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 11)] = CRGB::Black;
  // Random eye direction
  int randrow = random(7,9);
  int randcol = random(5,7);
  leds[mapScreenToMatrix(randrow, randcol)] = eyeColor;
  leds[mapScreenToMatrix(randrow, randcol+5)] = eyeColor;
}
void printLEDMatrix() {
  int x = MATRIX_WIDTH - 1; // index of leftmost pixel in the 0th row
  int y = ((MATRIX_WIDTH - 1) * MATRIX_WIDTH) - 1; // index of pixel to the left of the rightmost
  for (int start = x; start <= y; start += MATRIX_WIDTH * 2) {
    for (int p = start; p >= start - (MATRIX_WIDTH - 1); p--) {
      if (leds[p] != testColor) {
        Serial.print("@");
      } else {
        Serial.print(".");
      }
      Serial.print(" ");
    }
    Serial.println(" ");
    for (int p = start + 1; p <= start + 1 + (MATRIX_WIDTH - 1); p++) {
      if (leds[p] != testColor) {
        Serial.print("@");
      } else {
        Serial.print(".");
      }
      Serial.print(" ");
    }
    Serial.println(" ");
  }
  delay(50);
}
// Convert from (0,0) in upper left to matrix index
// Used when turning on an individual (random) pixel
int mapScreenToMatrix(int row, int col) {
  // Switch from increasing left to right into
  // increasing right to left for even numbered rows
  // Then compute a linear pixel offset
//  int newCol = (row % 2 == 0) ? newCol = (MATRIX_WIDTH - 1) - col : newCol = col; This was flipping the bitmap around the vertical axis
  int newCol = (row % 2 == 0) ? newCol = col : newCol = (MATRIX_WIDTH - 1) - col;
  return row * MATRIX_WIDTH + newCol;
}
// show the bitmap in memory onto the matrix using color indicated
void showBitmap(uint16_t bitmap[], CRGB myColor, bool clearFirst) {
  if (clearFirst) {
    FastLED.clear();
  }
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    for (int col = 0; col < MATRIX_WIDTH; col++) {
      if (bitRead(bitmap[row], col)) {
        int ledIndex = mapScreenToMatrix(row, col);
        leds[ledIndex] = myColor;
      }
    }
  }
  if (clearFirst) {
    FastLED.show();
  }
  if (DEBUG_PRINT) {
    printLEDMatrix();
  }  
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  set_max_power_indicator_LED(LED_BUILTIN);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  if (DEBUG_PRINT) {
    printBitmap(stem, sizeof(stem) / sizeof(uint16_t), CRGB::Green);
    printBitmap(pumpkin, sizeof(pumpkin) / sizeof(uint16_t), CRGB::Orange);
    printBitmap(eyes, sizeof(eyes) / sizeof(uint16_t), eyeColor);
    delay(2000);
  }
}
void loop() {
  FastLED.clear();
  showBitmap(stem, CRGB::Green, false);
  showBitmap(pumpkin, CRGB(255,91,0), false); // DMC 444
  showBitmap(eyes, CRGB::White, false);
  showBitmap(teeth, CRGB(255,91,0), false);
  FastLED.show();
  delay(300);

  while (true) {
    moveEyes();
    FastLED.show();
    printLEDMatrix();
    delay(random(250,1000));
  }

}
