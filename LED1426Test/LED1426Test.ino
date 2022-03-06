#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NUMPIXELS 12
#define PIN 6
#define DELAYVAL 500
#define BRIGHTNESS 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.clear();
}

void loop() {
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.show();
    delay(DELAYVAL);    
  }
  delay(5000);

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(DELAYVAL);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();
    delay(DELAYVAL);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    pixels.show();
    delay(DELAYVAL);
  }

#define GREEN 0x00ff00
#define RED   0xff0000
#define BLUE  0x0000ff

  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i += 2) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));
  }
  for (int i = 1; i < NUMPIXELS; i += 2) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  }
  pixels.show();
  delay(3000);

  for (int k = 0; k < 20; k++) {
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    }
    for (int i = 1; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    }
    pixels.show();
    delay(200);
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    }
    for (int i = 1; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    }
    pixels.show();
    delay(200);
  }

  pixels.fill(RED, 0, 0); // RED??
  pixels.show();
  delay(3000);

  pixels.fill(BLUE, 0, 0);
  pixels.show();
  delay(3000);

  pixels.fill(GREEN, 0, 0);  // GREEN??
  pixels.show();
  delay(3000);
}
