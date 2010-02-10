/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package edu.stuy;

import edu.wpi.first.wpilibj.*;
/**
 *
 * @author Ariel
 * @author Danny Zhu
 */
public class DonovanDriveTrain extends RobotDrive implements Ports{
    
    public Gyro gyro;
    
	
	
	
	
	
    
    Encoder encoder1;
    Encoder encoder2;
	
	
    public DonovanDriveTrain(int motor1,int motor2,int motor3,int motor4,int gyroport){
        super(motor1, motor2, motor3, motor4);
        encoder1 = new Encoder(ENCODER_CHANNEL_1A, ENCODER_CHANNEL_1B);
        encoder2 = new Encoder(ENCODER_CHANNEL_2A, ENCODER_CHANNEL_2B);
        
        //must set distance per pulse for encoders
        gyro = new Gyro(gyroport);
		
		
    }
	
    public DonovanDriveTrain(int motor1, int motor2, int motor3, int motor4){
        super(motor1, motor2, motor3, motor4);
        
        encoder1 = new Encoder(ENCODER_CHANNEL_1A, ENCODER_CHANNEL_1B);
        encoder2 = new Encoder(ENCODER_CHANNEL_2A, ENCODER_CHANNEL_2B);
    }
	
	
	
    /*
     * This constructor for testing on Michael1, which not have quad encoders.
     */
    public DonovanDriveTrain(int motor1, int motor2){
		
        super(motor1, motor2);
		
    }
	
	
    /**
     * This move the robot forward in inches
     */
    public void forwardInches(int inches){
		encoder1.start();
		encoder2.start();
		
		encoder1.reset();
		encoder2.reset();
		
		while( getAvgDistance() < inches){
			drive(.5, 0); //speed may need adjustment
		}
		encoder1.stop();
		encoder2.stop();
    }
	
	/**
     * This move the robot backward in inches
     */
    public void backInches(int inches){
		encoder1.start();
		encoder2.start();
		
		encoder1.reset();
		encoder2.reset();
		
		while(getAvgDistance() < inches){
			drive(-.5, 0); //speed may need adjustment
		}
		encoder1.stop();
		encoder2.stop();
		
    }
	
    /*
     * This return the averge distance read by the encoders, in inches
     */
    public double getAvgDistance(){
        return (encoder1.getDistance() + encoder2.getDistance()) / 2.0;
    }
	
}
