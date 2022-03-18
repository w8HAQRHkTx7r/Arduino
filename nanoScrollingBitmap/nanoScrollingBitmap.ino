// This program takes a bitmap array and scrolls it across an LED matrix

#define FASTLED_INTERNAL
#include <FastLED.h>

// Message parameters
#define MESSAGE_WIDTH 80 // The number of columns in the messasge This should be calculable
#define LETTER_HEIGHT 12 // Number of rows in each letter. Possible less than MATRIX_HEIGHT

// LED Matrix parameters
#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH  16
#define NUM_LEDS      MATRIX_HEIGHT * MATRIX_WIDTH

#define BITMAP_WIDTH  160
#define DATA_PIN 3
#define CLOCK_PIN 13
#define PAUSE 10
#define BRIGHTNESS 100
#define VOLTS 5
#define MAX_mAMPS 500

#define SPEED 100
#define printMatrix true

CRGB leds[NUM_LEDS];
CRGB color = CRGB::White;

int lastMessageColumn = MESSAGE_WIDTH - 1;
int currentMessageColumn = 0;

// These are the LED numbers for the last column of the matrix
int ledsInLastColumn[] = {
  0, 31, 32, 63, 64, 95,
  96, 127, 128, 159, 160,
  191, 192, 223, 224, 255
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

// print bitmap from memory
void printBitmap(uint16_t bitmap[], CRGB myColor) {
  Serial.println("Bitmap to follow:");
  Serial.println("fedcba9876543210 xxxx fedcba9876543210xxxx");
  for (int row = 0; row < BITMAP_WIDTH; row++) {
  Serial.print(bitmap[row], BIN); Serial.print(" ");
  Serial.print(bitmap[row], HEX); Serial.print(" ");
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

void getNextBitarrayRow() {
  // Clear the entire column to black
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    leds[ledsInLastColumn[row]] = CRGB::Black;
  }
//  Serial.println(slava[currentMessageColumn], BIN);
  // For each bit that's 1, light up the LED
  for (int b = 0; b <16; b++) {
    if (bitRead(slava[currentMessageColumn], b) == 1) {
      leds[ledsInLastColumn[b]] = CRGB::White;
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

    //    getNextMessageRow();  // Scroll the message using the bit matrix
    getNextBitarrayRow(); // Scroll the message using the bit array

    FastLED.show();
    delay(scrollDelay);
    if (printMatrix) {
      printLEDMatrix();
    }
  }
}

void printLEDMatrix() {
//  Serial.println("print LED matrix");
  int x = MATRIX_WIDTH - 1; // index of leftmost pixel in the 0th row
  int y = ((MATRIX_WIDTH - 1) * MATRIX_WIDTH) - 1; // index of pixel to the left of the rightmost
  for (int start = x; start <= y; start += MATRIX_WIDTH * 2) {
    for (int p = start; p >= start - (MATRIX_WIDTH - 1); p--) {
      if (leds[p] == color) {
        Serial.print("@");
      } else {
        Serial.print(".");
      }
      Serial.print(" ");
    }
    Serial.println(" ");
    for (int p = start + 1; p <= start + 1 + (MATRIX_WIDTH - 1); p++) {
      if (leds[p] == color) {
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
int mapScreenToMatrix(int row, int col) {
  // Switch from increasing left to right into
  // increasing right to left for even numbered rows
  // Then compute a linear pixel offset
  int newCol = (row % 2 == 0) ? newCol = (MATRIX_WIDTH - 1) - col : newCol = col;
  return row * MATRIX_WIDTH + newCol;
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

  // This is the message that will scroll
  // Adjust the message parameter defines
  // (These parameters should be encapsulated)
  //  slavaUkraine(); // This is the message that will scroll
  printBitmap(slava, CRGB::White);
}

void loop() {
  scrollMatrixLeft(SPEED);
}
