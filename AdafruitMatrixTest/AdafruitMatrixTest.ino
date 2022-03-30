// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <fonts/FreeSerifBold9pt7b.h>

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 3

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void loop() {
  matrix.fillScreen(0);
  // Scroll text
    matrix.setCursor(x, 5);
    matrix.print(F("Michael G. Macewich"));
    if(--x < -108) {
      x = matrix.width();
      if(++pass >= 3) pass = 0;
      matrix.setTextColor(colors[pass]);
    }
    matrix.show();
    delay(50);

  // Fill random pixels
  //  matrix.show();
  //  for (int i=0; i<256; i++) {
  //    matrix.drawPixel(random(0,16),random(0,16), RED);
  //    matrix.show();

  //Draw polyline
//  matrix.drawLine(random(0, 16), random(0, 16), random(0, 16), random(0, 16), BLUE);
//  matrix.drawLine(random(0, 16), random(0, 16), random(0, 16), random(0, 16), RED);
//  matrix.drawLine(random(0, 16), random(0, 16), random(0, 16), random(0, 16), WHITE);
//  matrix.drawLine(random(0, 16), random(0, 16), random(0, 16), random(0, 16), CYAN);
//  matrix.drawLine(random(0, 16), random(0, 16), random(0, 16), random(0, 16), GREEN);
//  matrix.show();
//  delay(1000);

  // Draw vertical and horizontal fast
//  matrix.drawFastVLine(random(0,16), 0, 15, RED);
//  matrix.drawFastHLine(0, random(0,16), 15, BLUE);
//  matrix.show();
//  delay(5);

// Draw rectangle
// Fill rectangle
//matrix.fillRect(random(0,16), random(0,16), random(3,14), random(3,14), GREEN);
//matrix.drawRect(random(0,16), random(0,16), random(16-random(0,14)), random(16-random(0,14)), RED);
//matrix.show();
//delay(1000);

// Draw,fill circles
//void drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
//void fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);

// Draw, Fill Rounded Rectangles
//void drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
//void fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);

// Triangles
//void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
//void fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

// Characters
//  matrix.setFont();
//  matrix.drawChar(3, 6, '&', RED, BLACK, 1);
//  matrix.show();
//  delay(500);
//  
//  matrix.setCursor(0, 6);
//  matrix.setTextColor(BLUE);
////  matrix.setTextColor(uint16_t color, uint16_t backgroundcolor);
//  matrix.setTextSize(1);
//  matrix.setFont(&FreeSerifBold9pt7b);
//  matrix.setTextWrap(false);
//  matrix.print(F("53"));
//  matrix.show();
//  delay(1000);


}
