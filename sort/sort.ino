#include <Adafruit_CircuitPlayground.h>

struct rgb {
  int r;
  int g;
  int b;
};

int pixel[] = {0,0,0,0,0,0,0,0,0,0};
rgb colors[10];
int pixels = 10;
int upper = 255;
int lower = 0;

void showChoices(rgb colorValues) {
  Serial.print(colorValues.r); Serial.print(' ');
  Serial.print(colorValues.g); Serial.print(' ');
  Serial.println(colorValues.b);    
}

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  for (int led = 0; led<pixels; led++) {
    rgb pixelColor;
    pixelColor.r = (rand() % (upper - lower + 1)) + lower;
    pixelColor.g = (rand() % (upper - lower + 1)) + lower;
    pixelColor.b = (rand() % (upper - lower + 1)) + lower;
    colors[led] = pixelColor;
    delay(1000);
    showChoices(pixelColor);
    CircuitPlayground.setPixelColor(led, pixelColor.r, pixelColor.g, pixelColor.b);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  rgb temp;
  for (int i=1; i<pixels; i++) {
    if (colors[i].r < colors[i-1].r) {
      temp = colors[i-1];
      colors[i-1] = colors[i];
      colors[i] = temp;
      CircuitPlayground.setPixelColor(i-1, colors[i-1].r, colors[i-1].g, colors[i-1].b);
      CircuitPlayground.setPixelColor(i,   colors[i].r,   colors[i].g,   colors[i].b);
    delay(500);
    }
  }
}
