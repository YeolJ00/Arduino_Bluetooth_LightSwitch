#include <SoftwareSerial.h>
#include <Servo.h>
#define SERVO_IN 5

Servo servo;
SoftwareSerial BTSerial(2,3);

int angle = 0;

void setup() {
 
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  servo.attach(SERVO_IN);
  servo.write(10);
  
}
int i=0;
int up=1;
void loop() {
  if(up==1){
    servo.write(i);
    i++;
  }else{
    servo.write(i);
    i--;
  }
  if(i==40||i==0){
    up = 1-up;
  }
  delay(100);
}
