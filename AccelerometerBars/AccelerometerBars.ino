#include <Adafruit_CircuitPlayground.h>

#define FASTLED_INTERNAL
#include <FastLED.h>
#define NUM_LEDS     60
#define DATA_PIN      6
#define CLOCK_PIN    13
#define PAUSE        10
#define BRIGHTNESS   30 
#define VOLTS         5
#define MAX_mAMPS   500
CRGB lights[NUM_LEDS];

#define backgroundbrightness 49

float measurement[3] = {0,0,0};
int offsets[3] = {0,8,16};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
//  CircuitPlayground.setAccelRange(LIS3DH_RANGE_4_G);
//  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(lights, NUM_LEDS);  // GRB ordering is assumed
      FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
      FastLED.setBrightness(BRIGHTNESS);
      FastLED.clear();
      FastLED.show();
}

float leds[3] = {5,5,5};

#define SAMPLESIZE 50
#define LIMIT      12

void putit(char* label, float vals[]) {
  Serial.print(label);
  Serial.print(" ");
  for (int i=0; i<3; i++) {
    Serial.print(vals[i]);
    Serial.print(" ");  
  }
  Serial.println("");
}

void setbackground() {
  for (int i=offsets[0]; i<offsets[0]+8; i++) {
    lights[i] = CRGB::Gold;
  }
  for (int i=offsets[1]; i<offsets[1]+8; i++) {
    lights[i] = CRGB::Black;
  }
  for (int i=offsets[2]; i<offsets[2]+8; i++) {
    lights[i] = CRGB::Gold;
  }
}

void loop() {

  float maxes[3] = {0,0,0};
  float mins[3] = {0,0,0};
  float counts = 0;
  float tots[3] = {0,0,0};
  float av[3] = {0,0,0};

  for (int i=0; i<SAMPLESIZE; i++) {
      measurement[0] = CircuitPlayground.motionX();
      measurement[1] = CircuitPlayground.motionY();
      measurement[2] = CircuitPlayground.motionZ();

      counts++;

      for (int axis=0; axis<3; axis++) {
        maxes[axis] = max(maxes[axis], measurement[axis]);
        mins[axis] = max(mins[axis], measurement[axis]);        
        tots[axis]+= measurement[axis];
        av[axis] = tots[axis]/counts;
      }
  }

//  putit("Maximums:",maxes);
  putit("Averages:",av);
//  putit("Minimums:",mins);
  
  for (int i=0; i<3; i++) {
    leds[i] = map(av[i], -LIMIT, LIMIT, 0, 8);
  }
      
  putit("Pixels:",leds);

  setbackground();
  lights[offsets[0] + int(leds[0])] = CRGB::Maroon;
  lights[offsets[1] + int(leds[1])] = CRGB::DarkGreen;
  lights[offsets[2] + int(leds[2])] = CRGB::MidnightBlue;
  FastLED.show();
  
  delay(200);
}
