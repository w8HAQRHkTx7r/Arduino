// COMET
// MARQUEE
// RAIN

#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS 144
#define DATA_PIN 6
//#define CLOCK_PIN    13
#define PAUSE 20
#define BRIGHTNESS 30
#define VOLTS 5
#define MAX_mAMPS 500

CRGB leds[NUM_LEDS];

#define BYTE uint8_t

void setup() {
  //  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  rain();
  FastLED.show();
}

void rain() {
  // Fill tthe LEDs with color
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t hue = map(i, 0, 60, 0, 255);
    leds[i] = CHSV(hue, 255, 255);
  }
  // Blacken every 6th pixel
  for (int i = 0; i < NUM_LEDS; i += 6) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void comet() {
  const byte fadeAmt = 128;
  const int cometSize = 1;
  const int deltaHue = 16;

  static byte hue = HUE_RED;
  static int iDirection = 1;
  static int iPos = 0;

//  hue += deltaHue;

  iPos += iDirection;
  if (iPos == (NUM_LEDS - cometSize) || iPos == 0) {
    iDirection *= -1;
    if (iDirection > 0) {
      hue += deltaHue;  // Change color on direction change
      }
  }

  for (int i = 0; i < cometSize; i++) {
    leds[iPos + i].setHue(hue);  // Draw the whole comet
  }

  // Randomly fade the LEDs
  for (int j = 0; j < NUM_LEDS; j++) {
    if (random(10) > 5)
      leds[j] = leds[j].fadeToBlackBy(fadeAmt);
  }      
}

void marquee() {
  CRGB temp = leds[NUM_LEDS - 1];
  for (int l = NUM_LEDS - 1; l > 0; l--) {
    leds[l] = leds[l - 1];
  }
  leds[0] = temp;
  FastLED.show();
}

int effectCount = 0;

void loop() {
//  EVERY_N_MILLISECONDS(5000) {
//    effectCount++;
//    if ((effectCount/100) % 2 == 0) {
//      comet();
//    } else {
//      marquee();
//    }      
//    FastLED.show();
//  }
  delay(8);
  marquee();
  FastLED.show();
}
