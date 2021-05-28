#include <IBusBM.h>
#include <Servo.h>

IBusBM IBus;    // IBus object
Servo myservo;  // create servo object to control a servo

void setup() {
  IBus.begin(Serial);    // iBUS object connected to serial0 RX pin
  myservo.attach(9);     // attaches the servo on pin 9 to the servo object
}

void loop() {
  int val;
  val = IBus.readChannel(0); // get latest value for servo channel 1
  myservo.writeMicroseconds(val);   // sets the servo position 
  delay(20);
}
