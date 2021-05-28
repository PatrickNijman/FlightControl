#include <IBusBM.h>
#include <Servo.h>
/*
 * This code can be used to directly control the servos of an RC plane.
 */
 
IBusBM IBus;    // IBus object
Servo rudderservo;  // create servo object to control a servo
Servo elevatorservo;
Servo l_aileronservo;
Servo r_aileronservo;
Servo prop;

struct servo_vals { 
    int aileron_r, aileron_l, elevator, rudder, prop; 
}; 

typedef struct servo_vals servo_values_struct;

void setup() {
  IBus.begin(Serial);    // iBUS object connected to serial0 RX pin
  Serial.begin(115200);
  rudderservo.attach(11);     // attaches the servo on pin 9 to the servo object
  elevatorservo.attach(10);
  l_aileronservo.attach(6);
  r_aileronservo.attach(5);
  prop.attach(3);
}

void loop() {
  servo_values_struct servo_values;
  
  servo_values = determine_servo_values(IBus);
  
  r_aileronservo.write(servo_values.aileron_r);
  l_aileronservo.write(servo_values.aileron_l);
  elevatorservo.write(servo_values.elevator);   
  rudderservo.write(servo_values.rudder);
  prop.write(servo_values.prop);
  delay(20);
}


servo_values_struct determine_servo_values(IBusBM ibus) { 
  
    servo_values_struct s; 
    
    s.aileron_r = convert_aileron_servo_val(ibus.readChannel(0));
    s.aileron_l = convert_aileron_servo_val(ibus.readChannel(0));
    s.elevator = convert_elevator_servo_val(ibus.readChannel(1));
    s.rudder = convert_rudder_servo_val(ibus.readChannel(3));
    s.prop = ibus.readChannel(2);
    return s; 
} 

int convert_rudder_servo_val(int channel_value){
  int servo_val;
  servo_val = map(channel_value, 1000, 1999, 0, 180); 
  return servo_val;
}

int convert_elevator_servo_val(int channel_value){
  int servo_val;
  servo_val = map(channel_value, 1000, 1999, 0, 180); 
  return servo_val;
}

int convert_aileron_servo_val(int channel_value){
  int servo_val;
  servo_val = map(channel_value, 1000, 1999, 0, 180); 
  return servo_val;
}
int convert_prop_value(int channel_value){
  int servo_val;
  servo_val = map(channel_value, 1000, 1999, 0, 180); 
  return servo_val;
}
