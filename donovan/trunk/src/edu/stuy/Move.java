/* The Move class has been deprecated.
 * forwardInches() and backInches() are
 * implemented in Autonomous.java
 */



//package edu.stuy;

//import edu.wpi.first.wpilibj.*;


//Should these methods be in DonovanDriveTrain.java ?
//Do we really need a Move class?

/**
 * This is for the robot to drive itself
 * @author Prog
 */

/*
 public class Move {
 
 static final int ENCODER_CHANNEL_A = 4; //unused? check
 static final int ENCODER_CHANNEL_B = 5; //unused? check
 Encoder encoder;
 
 public Move(){
 encoder = new Encoder(ENCODER_CHANNEL_A, ENCODER_CHANNEL_B);
 //set distance per pulse for encoder
 }
 
 public Move(Donovan d) {
 
 
 }
 
 
 
 public void forwardInches(int inches) {
 encoder.start();
 while(encoder.getDistance() < inches){
 //donnie.dt.drive(.5,0); //speed may need adjustment
 }
 encoder.reset();
 }
 
 
 public void forwardFeet(int feet) {
 forwardInches(feet * 12);
 }
 
 
 public void backInches(int inches) {
 encoder.start();
 while(encoder.getDistance() < inches){
 donnie.dt.drive(-.5,0); //speed may need adjustment
 }
 encoder.reset();
 }
 
 
 public void backFeet(int feet) {
 backInches(feet * 12);
 }
 */
