#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
RTC_DS1307 RTC;
#define H_PIN 12
#define M_PIN 13

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BTserial(8,9);

uint8_t alarm_hour = 0;//Alarm Hour
uint8_t alarm_minute = 0;//Alarm Minute
int SensorPin = A3;
int light_value;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  BTserial.begin(38400);
  pinMode(10, OUTPUT);// For Bluetooth
  digitalWrite(10, HIGH);
  
  Wire.begin();//I2C = RTC(Real Time C)
  RTC.begin();
  
 lcd.begin(16, 2);//size of LCD if not I2C
  //lcd.init();
  //lcd.backlight();
  lcd.clear();
  
  pinMode(H_PIN,INPUT_PULLUP);
  pinMode(M_PIN,INPUT_PULLUP);

  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__)); // Use ONCE then comment out and reload
    //RTC.adjust(DateTime(2019,12,8,11,1,0)); // Set time manually ONCE as above
  }
}

void loop() {
  if (BTserial.available())
    Serial.write(BTserial.read());
  if (Serial.available())
    BTserial.write(Serial.read());
    
  DateTime now = RTC.now(); //Get Current Time From RTC
  lcd.setCursor(0, 0);      //Print Current Time at (0,0)
  if (now.hour()<10)
    lcd.print('0');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  if (now.minute()<10)
    lcd.print('0');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  if (now.second()<10)
    lcd.print('0');
  lcd.print(now.second(), DEC);
  lcd.print("  ");

  lcd.setCursor(0, 1);       //Print Alarm Time at (0,1)
  if (alarm_hour<10)
    lcd.print('0');
  lcd.print(alarm_hour, DEC);
  lcd.print(':');
  if (alarm_minute<10)
    lcd.print('0');
  lcd.print(alarm_minute, DEC);
  lcd.print("-Alarm");

  if(digitalRead(H_PIN) == LOW){
    alarm_hour = alarm_hour+1;
    if(alarm_hour==24) alarm_hour = 0;
    delay(400);
  }
  if(digitalRead(M_PIN) == LOW){
    alarm_minute++; 
    if(alarm_minute==60) alarm_minute=0;
    delay(400);
  }
  
  light_value = analogRead(SensorPin);
  if (now.hour() == alarm_hour && now.minute() == alarm_minute && light_value < 700){//add Light Sensor condition
    Click();
    delay(1000);
  }
}

void Click() {
  //some Bluetooth connection
  BTserial.write('1');
  delay(10);
}
