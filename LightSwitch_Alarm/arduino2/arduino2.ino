#include <SoftwareSerial.h>
#include <Servo.h>
#define SERVO_IN 5

Servo servo;
SoftwareSerial BTSerial(2,3);

char buffer[100];

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  BTSerial.begin(38400);
  servo.attach(SERVO_IN);
  servo.write(40);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTSerial.available()){
    char on = BTSerial.read();
    for(int i=40;i>0;i--)
      servo.write(i);
    delay(60000);
    for(int i=0;i<40;i++)
      servo.write(i);
    BTSerial.readBytes(buffer,99);
  }
}
