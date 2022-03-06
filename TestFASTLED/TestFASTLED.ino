#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS     60
#define DATA_PIN      6
#define CLOCK_PIN    13
#define PAUSE        10
#define BRIGHTNESS   25 
#define VOLTS         5
#define MAX_mAMPS   500

CRGB leds[NUM_LEDS];

void setup() { 
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
      FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
      FastLED.setBrightness(BRIGHTNESS);
      FastLED.clear();
      FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(2000);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(2000);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(2000);
  leds[1] = CRGB::Red;
  FastLED.show();
  delay(2000);
  leds[2] = CRGB::Blue;
  FastLED.show();
  delay(2000);
  leds[3] = CRGB::Green;
  FastLED.show();
  delay(2000);
}
