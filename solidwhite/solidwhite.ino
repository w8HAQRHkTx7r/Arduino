// Solid white edge lit

#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS     60
#define DATA_PIN      6
#define CLOCK_PIN    13
#define PAUSE        10
#define BRIGHTNESS   50 
#define VOLTS         5
#define MAX_mAMPS  2000
#define FADEAMT     128

CRGB leds[NUM_LEDS];

void setup() { 
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
      FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
      FastLED.setBrightness(BRIGHTNESS);
      FastLED.clear();
      FastLED.show();
}

void lightThesePixels(int count) {
  for (int i=0; i<count; i++) {
    leds[i] = CRGB::White;
  }
//  for (int i=0; i<count; i++) {
//    int randomPixel = random(1,NUM_LEDS);
//    if (leds[randomPixel].r == 0) 
//      leds[randomPixel] = CRGB::Red;
//  }
}

void loop() {
  delay(100);
  lightThesePixels(10);
  FastLED.show();
}
