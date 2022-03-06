// Randomly flash and fade LEDs of various colors

#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS     144
#define DATA_PIN      6
#define CLOCK_PIN    13
#define PAUSE        10
#define BRIGHTNESS   90 
#define VOLTS         5
#define MAX_mAMPS  1000
#define FADEAMT     64

CRGB leds[NUM_LEDS];

void setup() { 
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
      FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
      FastLED.setBrightness(BRIGHTNESS);
      FastLED.clear();
      FastLED.show();
//      Serial.begin(9600);
}

void setRandomPixels(int count) {
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = leds[i].fadeToBlackBy(FADEAMT);
  }
  for (int i=0; i<count; i++) {
    int randomColor = random(1,4);
//    Serial.println(randomColor);
    int randomPixel = random(1,NUM_LEDS);
    if (randomColor == 1) {
        if (leds[randomPixel].r == 0) 
          leds[randomPixel] = CRGB::Red;
      }
    if (randomColor == 2) {
        if (leds[randomPixel].g == 0)
          leds[randomPixel] = CRGB::White;
    }
    if (randomColor == 3) {
        if (leds[randomPixel].b == 0)
          leds[randomPixel] = CRGB::Blue;
    }
  }
}

void loop() {
  delay(100);
  setRandomPixels(10);
  FastLED.show();
}
