#include <Arduino.h>

#define ENA 8      // Enable pin for stepper driver
#define DIR 7      // Direction pin for stepper driver
#define PUL 6      // Pulse pin for stepper driver
#define micro 1   // Can be 1, 2, 4, 8, 16, 32

// define dip pins
#define dip0 12
#define dip1 11
#define dip2 10
#define dip3 9

// variable to contain dip positions
byte dips = 0;

#define button 13
#define ext A1 //external input

const int steps = 50; // quarter turn

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);

  pinMode(dip0, INPUT_PULLUP);
  pinMode(dip1, INPUT_PULLUP);
  pinMode(dip2, INPUT_PULLUP);
  pinMode(dip3, INPUT_PULLUP);

  pinMode(button, INPUT_PULLUP);
  pinMode(ext, INPUT_PULLUP);

  digitalWrite(ENA, HIGH); // Dissable motor
  digitalWrite(DIR, LOW); // Clockwise when looking from top
  digitalWrite(PUL,LOW); // Start out LOW

  Serial.begin(115200);
}

void loop() {
  while(Serial.available()){ // while text is available from serial monitor
    String data = Serial.readString();
    Serial.println(data);
    if(data == "FDR") {feed();}
    if(data == "TEST") {Serial.println("test");}
    // Serial.println(data);
  }
  if (!digitalRead(button) || !digitalRead(ext)) {feed();} // if button or external trigger (A1) is activated
}

void feed () {  
  digitalWrite(ENA, LOW);
  delay(100);
  for (int x = 0; x < steps*micro; x++){
    digitalWrite(PUL, HIGH);
    delayMicroseconds(500/micro);
    digitalWrite(PUL, LOW);
    delayMicroseconds(500/micro);
  }
  delay(100);
  digitalWrite(ENA, HIGH);
  delay(1000);
}