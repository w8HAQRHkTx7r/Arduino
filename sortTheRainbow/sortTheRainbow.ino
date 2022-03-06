#include <Adafruit_CircuitPlayground.h>

struct rgb {
  int number;
  int r;
  int g;
  int b;
};

int pixel[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#define pixels 9
rgb colors[pixels];
rgb pallette[pixels];

int upper = 7;
int lower = 1;

void showChoices(rgb colorValues) {
  Serial.print(colorValues.number); Serial.print(' ');
  Serial.print(colorValues.r); Serial.print(' ');
  Serial.print(colorValues.g); Serial.print(' ');
  Serial.println(colorValues.b);
}

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  pallette[0] = {0,   0,   0,   0}; // black
  pallette[1] = {1, 211,   0,   0}; // red
  pallette[2] = {2, 252, 102,   0}; // orange
  pallette[3] = {3, 255, 242,   0}; // yellow
  pallette[4] = {4,   0, 255,   0}; // green
  pallette[5] = {5,   0,   0, 255}; // blue
  pallette[6] = {6,  63,   0, 255}; // indigo
  pallette[7] = {7, 178,   0, 237}; // violet
  pallette[8] = {8, 255, 255, 255}; // whitte

  delay(5000);
  
  Serial.println("Pallette");
  for (int led = 0; led < pixels; led++) {
    showChoices(pallette[led]);
    CircuitPlayground.setPixelColor(led, pallette[led].r, pallette[led].g, pallette[led].b);
  }
  delay(5000);

  Serial.println("Scramble");
  for (int led = 0; led < pixels; led++) {
    int number = (rand() % (upper - lower + 1)) + lower;
    colors[led] = pallette[number];
    showChoices(colors[led]);
    CircuitPlayground.setPixelColor(led, colors[led].r, colors[led].g, colors[led].b);
  }
  delay(5000);

}

void loop() {
  // put your main code here, to run repeatedly:
  rgb temp;
  for (int i = 1; i < pixels; i++) {
    if (colors[i].number < colors[i - 1].number) {
      temp = colors[i - 1];
      colors[i - 1] = colors[i];
      colors[i] = temp;
      CircuitPlayground.setPixelColor(i - 1, colors[i - 1].r, colors[i - 1].g, colors[i - 1].b);
      CircuitPlayground.setPixelColor(i,   colors[i].r,   colors[i].g,   colors[i].b);
      delay(500);
    }
  }
}
