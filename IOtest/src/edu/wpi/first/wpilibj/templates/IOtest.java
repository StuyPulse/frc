/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.wpi.first.wpilibj.templates;


import edu.wpi.first.wpilibj.*;//RobotDrive;
/*import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO.tDigitalConfig;
*/


/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */



public class IOtest extends SimpleRobot {
    /**
     * This function is called once each time the robot enters autonomous mode.
     */
  // CONSTANTS
final int ACQUIRER_BUTTON = 2;
final int ACQUIRER_ROLLER = 4;
final int ACQUIRER_SPEED_CONTROL = 2;


private RobotDrive drivetrain;
private Joystick leftStick;
private Joystick rightStick;
private DriverStationEnhancedIO enhancedIO;
private boolean testButton1;
private double acquirerSpeedSetting;
private Victor acquirer;


public IOtest()
{
drivetrain = new RobotDrive(1,2);
leftStick = new Joystick(1);
leftStick = new Joystick(2);
getWatchdog().setEnabled(false);

// IO Setup
enhancedIO = DriverStation.getInstance().getEnhancedIO();  //get driverstation IO instance

try{
enhancedIO.setDigitalConfig(ACQUIRER_BUTTON,DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
// no analog in setup
} //normally low; tie switch to +V

catch(DriverStationEnhancedIO.EnhancedIOException ex){}
acquirer = new Victor(ACQUIRER_ROLLER);
}

    public void autonomous()
    {
      /*  for (int i = 0; i < 4; i++)
        {
            drivetrain.drive(0.5,0.0);
            Timer.delay(2.0);
          drivetrain.drive(0.0,0.75);
        }
       drivetrain.drive(0.0,0.0);
    */
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl()
    {
    getWatchdog().setEnabled(false);
        while (true && isOperatorControl() && isEnabled())
        {
            drivetrain.tankDrive(leftStick, rightStick);
            Timer.delay(0.005);
            try{
            testButton1 = enhancedIO.getDigital(ACQUIRER_BUTTON);
            acquirerSpeedSetting = enhancedIO.getAnalogIn(ACQUIRER_SPEED_CONTROL);
            acquirerSpeedSetting = (acquirerSpeedSetting - (2^13))/ (2^13); // normalize to -1.0 to 1.0
            }
        catch(DriverStationEnhancedIO.EnhancedIOException ex)
        {
            testButton1 = false;
            acquirerSpeedSetting =0;
        }
            if (testButton1)    //button press
            { acquirer.set(acquirerSpeedSetting ); /* run acquirer*/}
            else
            {acquirer.set(0);/*stop acquirer*/}
        }
            }

}