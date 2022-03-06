#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS     256
#define DATA_PIN      3
//#define CLOCK_PIN    13
#define PAUSE        30
#define BRIGHTNESS   5 
#define VOLTS         5
#define MAX_mAMPS   500

CRGB leds[NUM_LEDS];

#define BYTE uint8_t
BYTE startHue = 0;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  rain(startHue);
  FastLED.show();
  Serial.begin(9600);
}

void rain(BYTE startHue) {
  for (int i=0; i<NUM_LEDS; i++) {
    BYTE hue = map(i, 0, 60, startHue, startHue+255) % 255;
    Serial.print("Hue:");Serial.println(hue);
    leds[i] = CHSV(hue, 255, 255);
    }
  FastLED.show();
  }


void loop() { 
  EVERY_N_MILLISECONDS(3000) {
//    CRGB temp = leds[NUM_LEDS-1];
//    for (int l=NUM_LEDS-1; l>0; l--) {
//       leds[l] = leds[l-1];  
//    }
//    leds[0] = temp;    
    rain(++startHue);
    for (int l=0; l<NUM_LEDS; l++) {
      leds[l] = CRGB::Black;
    }
    FastLED.show();
    delay(1000);
  }
}
