float azimuth;
float altitude;
int readCnt = 0;

void readCSV() {

      // this function expects a series of comma separated values
      // for this demo the sequence of items must be a string, an integer, a float
      // for example testing, 123 , 4567.89
      // spaces around the commas are optional
   
        // first read severalChars into the array inputSeveral
    ++readCnt;
    Serial.print(readCnt);
      
    String inputString;
    String az;
    String al;
    Serial.flush();
    Serial.println(" enter az and al separated by a comma");
   
    while (!Serial.available()) {}
    inputString = Serial.readString();
    Serial.println(inputString);
    
    int comma = inputString.indexOf(',');
    Serial.print("comma at ");
    Serial.println(comma);
    Serial.println(inputString.length());
    if (comma > 0 && inputString.length() > comma) {
      az = inputString.substring(0,comma);
      Serial.print("az "); Serial.println(az);
      azimuth = az.toFloat();
      al = inputString.substring(comma+1);
      Serial.print("al "); Serial.println(al);
      altitude = al.toFloat(); 
    }
    Serial.flush();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readCSV();
  Serial.print("AZ:");Serial.println(azimuth);
  Serial.print("AL:");Serial.println(altitude);
}
