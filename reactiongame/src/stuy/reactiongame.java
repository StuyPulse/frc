/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package stuy;
import edu.wpi.first.wpilibj.*;
import java.util.Random;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class reactiongame extends SimpleRobot implements Constants {
    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    Timer gameTime;
    Random random;
    Relay acquiredlight;
    OperatorInterface oi;



    public void autonomous() {
        
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl()   {
        gameTime = new Timer();
        random = new Random();
        acquiredlight = new Relay(TUBE_ACQUIRED_LIGHT);

        int score = 0;
        double onTime;
        double initTime;
        initTime = gameTime.getFPGATimestamp();

        while(gameTime.getFPGATimestamp() - initTime < 60) {
            gameTime.delay( 2 * random.nextDouble() + 1);
            acquiredlight.set(Relay.Value.kOn);
            onTime = gameTime.getFPGATimestamp();
            while (gameTime.getFPGATimestamp() - onTime < .2  ){
                if(oi.getMinibotSwitch()){
                    score++;
                    break;}
            }
            
          acquiredlight.set(Relay.Value.kOff);
        }
    System.out.print(score);
    }
}
