// This program takes a bitmap array and scrolls it across an LED matrix

#define FASTLED_INTERNAL
#include <FastLED.h>

// LED Matrix parameters
#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH  16
#define NUM_LEDS      MATRIX_HEIGHT * MATRIX_WIDTH

// #define BITMAP_WIDTH  160
#define DATA_PIN 3
#define CLOCK_PIN 13
#define PAUSE 10
#define BRIGHTNESS 100
#define VOLTS 5
#define MAX_mAMPS 500

#define SPEED 100

CRGB leds[NUM_LEDS];
CRGB testColor = CRGB::Black;

#define DEBUG_PRINT true

// These are the LED numbers for the last column of the matrix
byte ledsInLastColumn[] = {
  0, 31, 32, 63, 64, 95,
  96, 127, 128, 159, 160,
  191, 192, 223, 224, 255
};

// This is a degenerate form of showing the flag
// without having to do a multicolored bitmap design
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

// bitmap design for ukrainian tryzub
uint16_t tryzub[] = {
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


uint16_t slava[] = {
  0x0FE0,
  0x1010,
  0x1010,
  0x1010,
  0x0820,
  0x0000,
  0x1000,
  0x0C00,
  0x03F0,
  0x0010,
  0x0010,
  0x1FF0,
  0x0000,
  0x1FE0,
  0x0110,
  0x0110,
  0x0110,
  0x1FE0,
  0x0000,
  0x1FF0,
  0x1110,
  0x1110,
  0x1110,
  0x0EE0,
  0x0000,
  0x1FE0,
  0x0110,
  0x0110,
  0x0110,
  0x1FE0,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0030,
  0x00C0,
  0x1F00,
  0x00C0,
  0x0030,
  0x0000,
  0x1FF0,
  0x0100,
  0x0280,
  0x0C60,
  0x1010,
  0x0000,
  0x1FF0,
  0x0110,
  0x0110,
  0x0110,
  0x00E0,
  0x0000,
  0x1FE0,
  0x0110,
  0x0110,
  0x0110,
  0x1FE0,
  0x0000,
  0x1014,
  0x1FF0,
  0x1014,
  0x0000,
  0x1FF0,
  0x0100,
  0x0100,
  0x0100,
  0x1FF0,
  0x0000,
  0x1010,
  0x1FF0,
  0x1010,
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
  0x1FF0,
  0x0010,
  0x0010,
  0x0010,
  0x0000,
  0x1FF0,
  0x1110,
  0x1110,
  0x1010,
  0x0000,
  0x1FF0,
  0x0110,
  0x0110,
  0x0110,
  0x00E0,
  0x0000,
  0x0FE0,
  0x1010,
  0x1010,
  0x1010,
  0x0FE0,
  0x0000,
  0x18E0,
  0x0510,
  0x0310,
  0x0110,
  0x1FF0,
  0x0000,
  0x1FF0,
  0x0060,
  0x0180,
  0x1E00,
  0x0180,
  0x0060,
  0x1FF0,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0FE0,
  0x1010,
  0x1010,
  0x1010,
  0x0820,
  0x0000,
  0x1000,
  0x0C00,
  0x03F0,
  0x0010,
  0x0010,
  0x1FF0,
  0x0000,
  0x1FE0,
  0x0110,
  0x0110,
  0x0110,
  0x1FE0,
  0x0000,
  0x1FF0,
  0x1110,
  0x1110,
  0x1110,
  0x0EE0,
  0x0000,
  0x1FE0,
  0x0110,
  0x0110,
  0x0110,
  0x1FE0,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000
};
int MESSAGE_WIDTH = sizeof(slava) / sizeof(uint16_t);
int currentMessageColumn = 0;

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

    FastLED.show();
    delay(scrollDelay);

    // Clear the entire rightmost column to black
    for (int row = 0; row < MATRIX_HEIGHT; row++) {
      leds[ledsInLastColumn[row]] = CRGB::Black;
    }

    // For each bit in the row that's a 1, light up its matrix LED
    for (int b = 0; b < 16; b++) {
      if (bitRead(slava[currentMessageColumn], b) == 1) {
        leds[ledsInLastColumn[b]] = CRGB::White;
      }
    }
    currentMessageColumn = (currentMessageColumn + 1) % MESSAGE_WIDTH;

    if (DEBUG_PRINT) {
      printLEDMatrix();
    }
    FastLED.show();
    delay(scrollDelay);
  }
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
  int newCol = (row % 2 == 0) ? newCol = (MATRIX_WIDTH - 1) - col : newCol = col;
  return row * MATRIX_WIDTH + newCol;
}

// show the bitmap in memory onto the matrix using color indicated
void showBitmap(uint16_t bitmap[], CRGB myColor) {
  FastLED.clear();
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    for (int col = 0; col < MATRIX_WIDTH; col++) {
      if (bitRead(bitmap[row], col)) {
        int ledIndex = mapScreenToMatrix(row, col);
        leds[ledIndex] = myColor;
      }
    }
  }
  FastLED.show();
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
    printBitmap(slava, sizeof(slava) / sizeof(uint16_t), CRGB::White);
    printBitmap(tryzub, sizeof(tryzub) / sizeof(uint16_t), CRGB::Blue);
    delay(2000);
  }
}

void loop() {
  showBitmap(tryzub,CRGB::Yellow);
  if (DEBUG_PRINT) {
    printLEDMatrix();
  }  
  delay(3000);

  scrollMatrixLeft(SPEED);
  delay(1000);

  ukrainianFlag();
  if (DEBUG_PRINT) {
    printLEDMatrix();
  }
  delay(3000);
  
}
