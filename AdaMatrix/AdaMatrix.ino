// https://www.youtube.com/watch?v=j_VvLHZEPZ4&list=PLYZEWO6voRB44nO2g2C2VHBNT97sCAkW3&index=41

#include <Adafruit_NeoMatrix.h>
#define LED_PIN 3
#define LED_COUNT 256

Adafruit_NeoMatrix matrix(
  LED_COUNT,
  LED_PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800);
  
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
