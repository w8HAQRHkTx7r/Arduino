// This program reads data sent by another computer over the serial port
// and does something with it.

// place to store incoming characters
String inputBuffer = "";
bool stringComplete = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start sending data");
}

int azimuth;
int altitude;
String command = "";

void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete) {
    inputBuffer.toLowerCase();    
    if (inputBuffer.startsWith("m")) {
      // Print a text message  
      Serial.print("Display message ");
      Serial.println(inputBuffer.substring(1));  
    }
    else if (inputBuffer.startsWith("z")) {
      // Print Azimuth
      Serial.print("Display Azimuth ");
      azimuth = inputBuffer.substring(1).toInt();
      Serial.println(azimuth);      
    }
    else if (inputBuffer.startsWith("l")) {
      // Print Altitude
      Serial.print("Display Altitude ");
      altitude = inputBuffer.substring(1).toInt();
      Serial.println(altitude);
    }
    else {
      // Print unknown input error
      Serial.println("Unknown input");
    }
    inputBuffer = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputBuffer += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
