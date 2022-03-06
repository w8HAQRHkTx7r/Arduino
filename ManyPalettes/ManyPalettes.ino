#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS     256
#define DATA_PIN      3
#define CLOCK_PIN    13
#define PAUSE        10
#define BRIGHTNESS   10 
#define VOLTS         5
#define MAX_mAMPS   500

CRGB leds[NUM_LEDS];

// Original code:
#define CAP_THRESHOLD   50       //Change capacitive touch sensitivitiy here
#define FRAMES_PER_SECOND 35    // faster or slower burning fire

#define COOLING  55  // Less cooling = taller flames. Default 55, suggested range 20-100
#define SPARKING 50 //Higher chance = more roaring fire.  Default 120, suggested range 50-200
#define FADE 40  //How slowly the LEDs fade to off

static byte heat[NUM_LEDS];    // separate heat arrays for all 3 strips

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
CRGBPalette16 gPal;

//FIRST ACTIVE MODE
#define NUM_MODES 1     // actually 2 modes, mode 0 (off) and mode 1 (on)
int ledMode = 1;       // change to 0 to make the LEDs dark on startup

// End Original Code

void setup() { 
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
      FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
      FastLED.setBrightness(BRIGHTNESS);
      FastLED.clear();
      FastLED.show();

  currentBlending = LINEARBLEND;
  // Choose your color Palette
//  gPal = HeatColors_p;
//  gPal = LavaColors_p;
  gPal = RainbowColors_p;
//  gPal = CloudColors_p;
//  gPal = ForestColors_p;
//  gPal = PartyColors_p;
//  gPal = RainbowStripeColors_p;
}



//-----------------------------------------------------
void loop() {
  fire();
}
 
 void fire()
{
  
  currentPalette = HeatColors_p;
  currentPalette = gPal;
  Fire2012WithPalette(); // run simulation frame, using palette colors
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);  
  
}


void Fire2012WithPalette()
{
  random16_add_entropy( random());
  
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 3; k > 0; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < NUM_LEDS; j++) {
      byte colorindex = scale8( heat[j], 240);
      leds[j] = ColorFromPalette( currentPalette, colorindex);

    }
} 

void alloff() {  // Fade all LEDs slowly to black
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i].fadeToBlackBy( FADE );
  }
    for(int i = 0; i < NUM_LEDS; i++) {
  heat[i] = 0;
}

  FastLED.show();
  delay(20);
}
