/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package edu.stuy;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.*;
/**
 *
 * @author Ariel
 * @author Danny Zhu
 * @author !Alejandro
 */
public class DonovanDriveTrain extends RobotDrive{
    private Gyro gyro;
    public DonovanDriveTrain(int motor1,int motor2,int motor3,int motor4,int gyroport){
        super(motor1, motor2, motor3, motor4);
        gyro = new Gyro(gyroport);
    }
}
