/*
  Controls two Victor motor controllers using analog input from two linear potentiometers.
  For use with the two rollers on DESdroid's grabber mechanism.
 */

#include <Servo.h>

Servo upperRoller;
Servo lowerRoller;

void setup() {
  //Serial.begin(9600);
  upperRoller.attach(10);
  lowerRoller.attach(11);
}

void loop() {
  // Read the value of the two potentiometers.
  int pot_a = analogRead(A0);
  int pot_b = analogRead(A1);
  
  // Map the values to the PWM range.
  int pwmOut_a = map(pot_a, 0, 1023, 0, 179);
  int pwmOut_b = map(pot_b, 0, 1023, 0, 179);
  
  // Print out the PWM values.
  //Serial.print(pwmOut_a, DEC);
  //Serial.print("\t");
  //Serial.println(pwmOut_b, DEC);
  
  // Send the PWM signals.
  upperRoller.write(pwmOut_a);
  lowerRoller.write(pwmOut_b);
  
  // Delay 15 milliseconds to allow time for the change to be applied.
  delay(15);
}
