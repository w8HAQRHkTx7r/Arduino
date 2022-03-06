#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS   60
#define DATA_PIN    6
#define CLOCK_PIN  13
#define PAUSE      10
#define BRIGHTNESS 30
#define VOLTS       5
#define MAX_mAMPS 500

CRGB leds[NUM_LEDS];
uint8_t values[NUM_LEDS] = { 0 };

void setValues() {
  for (int i = 0; i < NUM_LEDS; i++) {
    values[i] = random8();
    leds[i] = CHSV(values[i], 255, 255);
  }
  FastLED.show();
}

void printValues() {
  for (int i = 0; i < NUM_LEDS; i++) {
    display("led", i); display("value", values[i]); nl();
  }
}
void displayValues() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(values[i], 255, 255);
  }
  FastLED.show();
}
void setup() {
 Serial.begin(9600);
//  display("begin", 0);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  for (int i = 0; i < NUM_LEDS; i++) {
    values[i] = random8();
    leds[i] = CHSV(values[i], 255, 255);
  }
  FastLED.show();
  delay(1000);
}

void display(char* label, int value) {
 Serial.print(label);
 Serial.print(":");
 Serial.print(value);
 Serial.print(" ");
}
void nl() {
 Serial.println(" ");
}

int loopstart = 0;

void loop() {
  if (loopstart > NUM_LEDS - 1) {
//    printValues();
    delay(60000);
    return;
  }
  int pos = 0;
  uint8_t max = values[loopstart];
  for (int pixel = loopstart; pixel < NUM_LEDS; pixel++) {
    if (values[pixel] >= max) {
      max = values[pixel];
      pos = pixel;
    }
  }

  uint8_t temp = values[loopstart];
  values[loopstart] = values[pos];
  values[pos] = temp;

  displayValues();

  loopstart++;
  
  delay(50);
}
