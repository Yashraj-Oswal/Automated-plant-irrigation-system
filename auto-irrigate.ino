#include <BoltIoT-Arduino-Helper.h>

int sensor_pin = A0;
int output_value;
int temp = A1;
int IN1=7;
int IN2=8;
int IN3=12;
int IN4=13;

void setup() { 
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  
  boltiot.begin(Serial); //Initialize the Bolt interface over serial UART. Serial could be replaced with Serial0 or Serial1 on Arduino Mega boards.
       //In this example, the TX pin of Bolt is connected to the RX pin of Arduino Serial Port
       //and the TX pin of Bolt is connected to the TX pin of Arduino Serial Port
  //pinMode(2,INPUT); //Set pin 2 as the input. We will use send this pin's state as the data to the Bolt cloud
  delay(2000);
}

void loop() {
  output_value = analogRead(sensor_pin);
  output_value = map(output_value,550,10,0,100);
  if(output_value < 15)
 {
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
 }
 else
 {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
 }
 delay(1000);
  int analogValue = analogRead(temp);
  float millivolts = (analogValue/1024.0)*3300;
  float celsius = millivolts/10;
  if(celsius >=21)
  {
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(1000);
    
    }
    else
    {
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      delay(1000);
    }
  boltiot.processPushDataCommand(output_value,celsius); //Send data to the Bolt cloud, when the Bolt polls the Arduino for data.
 delay(1000);
/*This function needs to be called regularly. Calling the processPushDataCommand function once every second is required*/
  
}
