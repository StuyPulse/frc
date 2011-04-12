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
 * A game designed to improve the reaction time of a person deploying
 * the minibot. The goal of this game is to pull the Minibot release
 * switch at the same time the tube acquired light on the robot goes on.
 * @author Peter Jasko
 */
public class Reactiongame extends SimpleRobot implements Constants {
    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    Timer gameTime;
    Random random;
    Relay acquiredlight;
    OperatorInterface oi;

  public void autonomous() {
        
    }

    public void operatorControl()   {
        getWatchdog().setEnabled(false);
        gameTime = new Timer();
        random = new Random();
        acquiredlight = new Relay(TUBE_ACQUIRED_LIGHT);

        int score = 0;
        int total_flashes = 0;
        double onTime;
        double initTime;
        initTime = gameTime.getFPGATimestamp();
 while (isEnabled() && isOperatorControl()) {
        while(gameTime.getFPGATimestamp() - initTime < 60) {
            gameTime.delay( 2 * random.nextDouble() + 1);
            acquiredlight.set(Relay.Value.kOn);
            total_flashes++;
            onTime = gameTime.getFPGATimestamp();
            while (gameTime.getFPGATimestamp() - onTime < .2  ){
                if(oi.getMinibotSwitch()){
                    score++;
                    break;}
            }
            acquiredlight.set(Relay.Value.kOff);
        }
    System.out.print(score + "out of" + total_flashes);
    }
 }
}