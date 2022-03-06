#include <MACELib.h>

// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#define LED_PIN    3
#define LED_COUNT  12

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);

int pixels[LED_COUNT];

void shuffle() {
  for (int i=0; i<100; i++) {
    int first = random(0,LED_COUNT - 1);
    int second = random(0,LED_COUNT - 1);
    int temp = pixels[first];
    pixels[first] = pixels[second];
    pixels[second] = temp;
    }
  }

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

//  cereal();
//  labelValue("LED count: ", LED_COUNT, ",");
  
  for (int i=0; i<LED_COUNT; i++) {
    pixels[i] = i;
  }
}

void loop() {
  shuffle();
  for (int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(pixels[i], 0, 0, 0, 255);
    strip.show();
    delay(100);
  }
  delay(3000);
//  strip.clear();
//  strip.show();
  for (int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(pixels[i], 0, 0, 0, 0);
    strip.show();
    delay(100);
  }
  delay(1000);
}
