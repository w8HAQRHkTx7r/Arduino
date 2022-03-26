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
CRGB g = CRGB::Green;
CRGB o = CRGB(255, 91, 0);
CRGB y = CRGB::Yellow;
CRGB w = CRGB::White;
CRGB eyeColor = w;

void drawImage() {
leds[21]=g;leds[22]=g;
leds[41]=g;leds[40]=g;
leds[54]=g;leds[55]=g;leds[56]=g;
leds[75]=g;leds[74]=g;leds[73]=g;leds[72]=g;leds[71]=g;leds[70]=g;leds[69]=g;
leds[83]=o;leds[84]=o;leds[85]=o;leds[86]=g;leds[87]=o;leds[88]=o;leds[89]=g;leds[90]=o;leds[91]=o;
leds[109]=o;leds[108]=o;leds[107]=o;leds[106]=o;leds[105]=o;leds[104]=o;leds[103]=o;leds[102]=o;leds[101]=o;leds[100]=o;leds[99]=o;
leds[113]=o;leds[114]=o;leds[115]=o;leds[116]=w;leds[118]=o;leds[119]=o;leds[120]=o;leds[121]=w;leds[123]=o;leds[124]=o;leds[125]=o;
leds[142]=o;leds[141]=o;leds[140]=o;leds[137]=o;leds[136]=o;leds[135]=o;leds[132]=o;leds[131]=o;leds[130]=o;
leds[145]=o;leds[146]=o;leds[147]=o;leds[148]=o;leds[149]=o;leds[150]=o;leds[152]=o;leds[153]=o;leds[154]=o;leds[155]=o;leds[156]=o;leds[157]=o;
leds[174]=o;leds[173]=o;leds[172]=o;leds[171]=o;leds[170]=o;leds[166]=o;leds[165]=o;leds[164]=o;leds[163]=o;leds[162]=o;
leds[177]=o;leds[178]=o;leds[179]=o;leds[181]=o;leds[182]=o;leds[183]=o;leds[184]=o;leds[185]=o;leds[187]=o;leds[188]=o;leds[189]=o;
leds[205]=o;leds[204]=o;leds[203]=o;leds[201]=y;leds[199]=y;leds[197]=o;leds[196]=o;leds[195]=o;
leds[211]=o;leds[212]=o;leds[213]=o;leds[214]=o;leds[215]=o;leds[216]=o;leds[217]=o;leds[218]=o;leds[219]=o;
leds[235]=o;leds[234]=o;leds[233]=o;leds[232]=o;leds[231]=o;leds[230]=o;leds[229]=o;
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

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  set_max_power_indicator_LED(LED_BUILTIN);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  drawImage();
  FastLED.show();
}

void loop() {
  moveEyes();
  FastLED.show();
  delay(random(200,600));
}
