// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     1

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT   10  // This is how many will be used
#define STRIPLENGTH 30  // This is how many exist. Seet this many to black, then update length.

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 20 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(STRIPLENGTH, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  Serial.begin(9600);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  strip.updateLength(LED_COUNT);
}

void loop() {
  delay(500);
  Serial.println("Start now");
  for (int j=0; j<10; j++) {
     Serial.print("Countoff ");
     Serial.println(j);
     }
  delay(500);  
  for (int i=0; i<LED_COUNT; i++) {
    Serial.println(i);
    strip.setPixelColor(i, 0x00ff00);
    strip.show();
    delay(500);
    strip.setPixelColor(i, 0);
  }
    strip.fill(0x9900ff);
    strip.show();
}
