#include <Adafruit_CircuitPlayground.h>

int pixel[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int digits = 10;

void clearit()  {
  for (int led = 0; led <= digits; led++) {
    CircuitPlayground.setPixelColor(led, 0, 80, 80);
  }
}

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  clearit();
  delay(2000);
  Serial.begin(9600);
}

int rotations = 5;
int lightedpixel = 0;
int priorpixel = 0;
float wait = 10;



void loop() {

  while (!CircuitPlayground.leftButton()) {
    
  }
  
  while (wait < 600) {
    Serial.println(wait);
    CircuitPlayground.setPixelColor(priorpixel, 0, 0, 0);
    CircuitPlayground.setPixelColor(lightedpixel, 255, 0, 0);
    delay(wait);
    priorpixel = lightedpixel;
    lightedpixel = ++lightedpixel % 10;
    wait *= 1.07;
  }
  Serial.println(lightedpixel);
  wait = 1;
//  clearit();
  CircuitPlayground.playTone(440, 500);
  delay(2000);
}
