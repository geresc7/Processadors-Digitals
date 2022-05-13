#include <Arduino.h>

void setup() {
// initialize the digital pin as an output.

pinMode(1, OUTPUT);
Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
digitalWrite(1, HIGH); // turn the LED on (HIGH is the voltage level)
delay(1000); // wait for a second
Serial.println("OFF");
digitalWrite(1, LOW); // turn the LED off by making the voltage LOW
delay(1000); // wait for a second
Serial.println("ON");
}