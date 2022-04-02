// This program draws and animates a Ukrainian flag on a flagpole.
// The flag is designed as a static rectangle with the upper half
// blue and the lower half yellow.
// A sin function is computed for x value (column number) in the 
// image.  The function is stretched in x and y directions to fit the
// animation within the matrix.  The function indicates how far up
// or down those flag pixels should be raised or lowered -- displacement.
// In the next frame of the animation, the function goes through a time
// shift. This causes the sin wave to shift to the right by one column
// The flag is redrawn using these new displacements.
// At an appropriate frame rate, the flag appears to flutter in the
// wind.

#define FASTLED_INTERNAL
#import "BitArray.h"
#include <FastLED.h>
#include "MACELib.h"

// Alphabet parameters
#define MESSAGE_WIDTH 75
#define LETTER_HEIGHT 12

// LED Matrix parameters
#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH  16
#define NUM_LEDS      256
#define LAST_LED      NUM_LEDS - 1

#define DATA_PIN 3
#define CLOCK_PIN 13
#define PAUSE 10
#define BRIGHTNESS 100
#define VOLTS 5
#define MAX_mAMPS 500

#define DELAY 3000  // delay in ms between matrix frame displays
#define BITMAP_WIDTH 16  // number of bits in bitmap
#define DEBUG_BITMAP false // print bitmap before showing on matrix

CRGB leds[NUM_LEDS];
BitArray message;

int lastMessageColumn = MESSAGE_WIDTH - 1;
int currentMessageColumn = 0;

bool getNextMessageRow(int scrollDelay) {
  //  currentMessageColumn = currentMessageColumn % MESSAGE_WIDTH;
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    leds[mapScreenToMatrix(row, 15)] = CRGB::Black;
  }
  uint16_t bitrow = message.get(currentMessageColumn);
  for (int b = 0; b < LETTER_HEIGHT; b++) {
    if (bitRead(bitrow, b) == 1) {
      leds[mapScreenToMatrix(b, 15)] = CRGB::White;
    }
  }
  currentMessageColumn++;
  delay(scrollDelay);
  if (currentMessageColumn > lastMessageColumn) {
    currentMessageColumn = 0;
    return false;
  }
}

bool scrollMatrixLeft(int scrollDelay) {
  FastLED.clear();
  for (int col = 0; col < MESSAGE_WIDTH; col++) {
    int x = MATRIX_WIDTH - 1;
    int y = ((MATRIX_WIDTH - 1) * MATRIX_WIDTH) - 1;
    for (int start = x; start <= y; start += MATRIX_WIDTH * 2) {
      for (int p = start; p > start - (MATRIX_WIDTH - 1); p--) {
        leds[p] = leds[p - 1];
      }
      for (int p = start + 1; p < start + 1 + (MATRIX_WIDTH - 1); p++) {
        leds[p] = leds[p + 1];
      }
    }
    FastLED.show();
    if (!getNextMessageRow(scrollDelay)) {
      return false;
    } else {
      FastLED.show();
    }
    delay(scrollDelay);
  }
}

void defineAlphabet() {
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
}

// Convert from (0,0) in upper left to matrix index
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
  for (int row = 0; row < 16; row++) {
    for (int col = 0; col < BITMAP_WIDTH; col++) {
      if (bitRead(bitmap[row], col)) {
        int ledIndex = mapScreenToMatrix(row, col);
        leds[ledIndex] = myColor;
      }
    }
  }
  FastLED.show();
}

// print bitmap from memory
void printBitmap(uint16_t bitmap[], CRGB myColor) {
  Serial.print(myColor);
  for (int row = 0; row < 16; row++) {
    for (int col = 0; col < BITMAP_WIDTH; col++) {
      if (bitRead(bitmap[row], col)) {
        Serial.print("x");
      } else {
        Serial.print(" ");
      }
    }
    Serial.println(" ");
  }
}

// This is a degenerate form of showing the flag
// without having to do a multicolored bitmap design
void ukrainianFlag() {
  FastLED.clear();
  int topHalf = 256 / 2;
  // Start at the third row down  (16 pixels per line * 2 blank lines)
  for (int i = 32; i < topHalf; i++) {
    leds[i] = CRGB::Blue;
  }
  // Start from where the blue left off -- topHalf and continue until
  // there are 32 unlit pixels left
  for (int i = topHalf; i < 256 - 32; i++) {
    leds[i] = CRGB::Yellow;
  }
  FastLED.show();
}

// bitmap design for ukrainian tryzub
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

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  if (DEBUG_BITMAP) {
    //    cereal(); // begin Serial and wait until stable
  }
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  set_max_power_indicator_LED(LED_BUILTIN);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  defineAlphabet();

}

void waveFlag() {
  float freq = 0.5;
  float magnitude = 1.5;
  float flagWidth = 15;
  float deltaXradians = PI / flagWidth;
  int toprow = 2;
  int botrow = 13;
  for (int frame = 0; frame <= 15; frame++) {
    float radian = -frame * deltaXradians;
    FastLED.clear();
    for (int y = 2; y <= 2 + 5; y++) {
      int ledIndex = mapScreenToMatrix(y, 0);
      leds[ledIndex] = CRGB::Blue;
    }
    for (int y = 8; y <= 8 + 5; y++) {
      int ledIndex = mapScreenToMatrix(y, 0);
      leds[ledIndex] = CRGB::Yellow;
    }
    leds[mapScreenToMatrix(1, 0)] = CRGB::White;
    leds[mapScreenToMatrix(14, 0)] = CRGB::White;
    leds[mapScreenToMatrix(15, 0)] = CRGB::White;

    for (int col = 1; col <= 15; col++) {
      //      Serial.print(" frame "); Serial.print(frame);
      //      Serial.print(" radian "); Serial.print(radian);
      int displacement = round(sin(radian / freq) * magnitude);
      //      Serial.print(" displacement "); Serial.print(displacement);
      //      Serial.print(" top ");
      //      Serial.print("top:");
      //      Serial.print(toprow + displacement);
      //      Serial.print(", ");
      //      Serial.print(" bot: ");
      //      Serial.print(botrow + displacement);
      //      Serial.println(" ");

      for (int y = toprow + displacement; y <= toprow + displacement + 5; y++) {
        int ledIndex = mapScreenToMatrix(y, col);
        leds[ledIndex] = CRGB::Blue;
      }

      for (int y = toprow + displacement + 6; y <= botrow + displacement; y++) {
        int ledIndex = mapScreenToMatrix(y, col);
        leds[ledIndex] = CRGB::Yellow;
      }

      radian += deltaXradians;
    }
    FastLED.show();
    int WINDSPEED = 85;
    delay(WINDSPEED);
  }
}

void loop() {
  //  Serial.println("start loop");
  //  if (DEBUG_BITMAP) {
  //    printBitmap(tryzub, CRGB::Yellow);
  //  }
  //  showBitmap(tryzub, CRGB::Yellow);
  //  delay(DELAY);
  //  ukrainianFlag();
  //  delay(DELAY);


  //waveFlag();

  float freq = 0.5;
  float magnitude = 1.5;
  float flagWidth = 15;
  float deltaXradians = PI / flagWidth;
  int toprow = 2;

  // starting at frame 1 because starting at zero causes a delay in the animation
  // It might have something to do with the last frame equal to the 0th.
  for (int frame = 1; frame <= 15; frame++) {
    float radian = -frame * deltaXradians;
    FastLED.clear();

    // Flagpole
    leds[mapScreenToMatrix(1, 0)] = CRGB::White;
    leds[mapScreenToMatrix(14, 0)] = CRGB::White;
    leds[mapScreenToMatrix(15, 0)] = CRGB::White;

    // Part of flag anchored to the flagpole
    for (int y = 2; y <= 2 + 5; y++) {
      int ledIndex = mapScreenToMatrix(y, 0);
      leds[ledIndex] = CRGB::Blue;
    }
    for (int y = 8; y <= 8 + 5; y++) {
      int ledIndex = mapScreenToMatrix(y, 0);
      leds[ledIndex] = CRGB::Yellow;
    }

    // Rest of the flag
    for (int col = 1; col <= 14; col++) {

      int displacement = round(sin(radian / freq) * magnitude);

      for (int y = toprow + displacement; y <= toprow + displacement + 5; y++) {
        int ledIndex = mapScreenToMatrix(y, col);
        leds[ledIndex] = CRGB::Blue;
      }

      //      for (int y = toprow + displacement + 6; y <= botrow + displacement; y++) {
      for (int y = toprow + displacement + 6; y <= toprow + displacement + 11; y++) {
        int ledIndex = mapScreenToMatrix(y, col);
        leds[ledIndex] = CRGB::Yellow;
      }

      radian += deltaXradians;
    }
    FastLED.show();
    int WINDSPEED = 85;
    delay(WINDSPEED);
  }



  //  scrollMatrixLeft(100);
  //  delay(DELAY);
}
