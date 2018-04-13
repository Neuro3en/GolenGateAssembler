
// this code will measure the temperatur readings (Pin A0)
// from the analog temp sensor as raw values, 
// it needs to be calibraded. The peltier element is attached to Pin 2 and 3
// The code is based on arduinos smooth code example
// TODO
// PID controll for the 2 temperatures to cycle throu
// calibration for the temp sensor
// LED Pin13 oitput when the protocoll is over


const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int inputPin = A0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);     
  pinMode(2, OUTPUT);           // attached to one input of the H bridge
  pinMode(3, OUTPUT);           // attached to the otehr input of the H bridge
  digitalWrite(2, HIGH);        // if one input is high and the other is low the peltier will cool, 
  digitalWrite(3, LOW);         //and heat if the inputs are low and high
     
   
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  delay(1);        // delay in between reads for stability
}
