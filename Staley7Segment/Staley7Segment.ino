// C++ code
//

// Common Ground 7-Segment display
#define ON  HIGH
#define OFF LOW

// Common anode 7-segment display
//#define ON  LOW
//#define OFF HIGH

// pin assignments
// These are the "D" numbers on the Nano
// pin 2 is d2 is physical 5!!!!
int segmentPin[] = {
   10, // pin for g segment
    8, // pin for f segment
   A4, // e
   A2, // d
   A0, // c
    4, // b
    6, // a
    0, // DP
};
int segmentSize = sizeof(segmentPin) / sizeof(int);

// Segment table. This is pretty standard
int digits[] = {
  // abcdefg
  B1111110, // 0
  B0110000, // 1
  B1101101, // 2
  B1111001, // 3
  B0110011, // 4
  B1011011, // 5
  B1011111, // 6
  B1110000, // 7
  B1111111, // 8
  B1110011, // 9
  B1110111, // A
  B0011111, // b
  B1001110, // C
  B0111101, // d
  B1001111, // E
  B1000111, // F
};

int charCount = sizeof(digits) / sizeof(int);

void setup() {
  // set the pins used for the 7 segment display to output
  for (int pin = 0; pin < segmentSize; pin++) {
    pinMode(segmentPin[pin], OUTPUT);
    }
//  Serial.begin(9600);
}

void displayDigit(int digit, bool decimalPoint) {
  // Read the segment table bits for this digit
  for (int bit = 6; bit >=0; bit--) {
    int level = bitRead(digits[digit], bit);
    // Set the corresponding pin for this bit
    if (level == 1) {
      digitalWrite(segmentPin[bit], ON);
    } else {
        digitalWrite(segmentPin[bit], OFF);
    }
  }
}

void segmentsInOrder() {
  for (int segment=segmentSize-1; segment>=0; segment--) {
    digitalWrite(segmentPin[segment], ON);
    delay(500);
    digitalWrite(segmentPin[segment], OFF);
  }
}

void displayOff() {
  for (int segment=0; segment<segmentSize; segment++) {
    digitalWrite(segmentPin[segment], OFF);
  }
}
void loop() {
  // Test each segment
  displayOff();
  segmentsInOrder(); 
  delay(500);
  displayOff();
   
// Cycle thru all digits and display them
  for (int digit=0; digit <charCount; digit++) {
    displayDigit(digit,false);
    delay(500);
  }
  delay(250);

}
