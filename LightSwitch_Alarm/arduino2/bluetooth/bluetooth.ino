#include <SoftwareSerial.h>
SoftwareSerial BTserial(8,9);

void setup() {
  Serial.begin(9600);
  BTserial.begin(38400);
  pinMode(10, OUTPUT);// For Bluetooth
  digitalWrite(10, HIGH);
}

void loop() {
  if (BTserial.available())
    Serial.write(BTserial.read());
  if (Serial.available())
    BTserial.write(Serial.read());
}
