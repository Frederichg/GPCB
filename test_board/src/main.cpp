#include <Arduino.h>

#define dripper 2
#define IR1 A7
#define IR2 A6
#define touch A0
#define feeder
#define dip

// define pins and variable for feeder
#define ENA 2     // Enable pin for stepper driver
#define DIR 3      // Direction pin for stepper driver
#define PUL 4      // Pulse pin for stepper driver

#define micro 2   // Can be 1, 2, 4, 8, 16, 32

// define pins for dripper
#define dripSize A5
#define maxTime 5 //Maximum drip time in seconds

// define dip pins
#define dip0 12
#define dip1 11
#define dip2 10
#define dip3 9

// variable to contain dip positions
byte dips = 0;

#define button 13
#define IN1 A1

// declare funcitons
void testDips();
void testOut();
void testDrip();
void testFeeder();
void testTouch();

void setup() {

  // SET ALL INPUTS
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  // SET ALL OUTPUTS
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  // initial pin state for stepper motor
  #ifdef feeder
    digitalWrite(ENA, HIGH); // Dissable motor
    digitalWrite(DIR, LOW); // Clockwise when looking from top
    digitalWrite(PUL,LOW); // Start out LOW 
  #endif

  Serial.begin(115200);
}

void loop() {
  testDips();
  testOut();
  testDrip();
  testFeeder();
  testTouch();
}

void testDips () {
  // the order is dip0, dip1, dip2, dip3
  // for example, if odd dips (dip1 and dip3) are 1, dips == 0000 0101
  dips = 0 | digitalRead(dip0) << 3 | digitalRead(dip1) << 2 | digitalRead(dip2) << 1 | digitalRead(dip3);

  // only prints from the leftmost high bit
  // for example, 0000 0101 is printed as 101
  Serial.println(dips, BIN);
  delay(100);
}

void testOut () {
  // Simple test, toggle each output pin
  for (int x = 0; x < 7; x++) {
    digitalWrite(x+2, HIGH);
    Serial.println("pin " + String(x+2));
    delay(1000);
    digitalWrite(x+2, LOW);
  }
}

void testDrip () {
  // turn dripper on
  digitalWrite(dripper, HIGH);

  // reat pot
  float val = analogRead(dripSize);

  //wait
  delay(val/1023 * maxTime * 1000);
  Serial.println("valve open for " + String(val/1023 * maxTime * 1000) + " seconds (" + String(val/1023) + "%)");

  // turn dripper off
  digitalWrite(dripper, LOW);
  delay(1000);
}

void testFeeder () {
  // enable stepper
  digitalWrite(ENA, LOW);
  delay(100);

  // one full rotation
  for (int x = 0; x < 600*micro; x++){
    digitalWrite(PUL, HIGH);
    delayMicroseconds(500/micro);
    digitalWrite(PUL, LOW);
    delayMicroseconds(500/micro);
  }

  // dissable stepper
  delay(100);
  digitalWrite(ENA, HIGH);

  //wait one sec
  delay(1000);
}

void testTouch () {
  Serial.println(digitalRead(touch));
  delay(100);
}