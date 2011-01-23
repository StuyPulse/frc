package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * These are the different methods for autonomus mode.
 * Best routines (currently):
 *   Near:   2
 *   Center: 2,9, practice 6
 *   Far:    11
 * @author Prog
 */
public class Autonomous {

    Donovan donnie;

    public Autonomous(Donovan d) {
        donnie = d;
    }

    /**
     * Runs a given autonomous setting.  Called in Donovan.autonomous()
     * @param settingNum The setting number to run, comes from a DonovanOI
     */
    public void runSettingNum(int settingNum) {
        // called in Donovan.autonomous(),
        // argument comes from DonovanOI

        switch (settingNum) {
            case 1:
                setting1();
                break;
            case 2:
                setting2();
                break;
            case 3:
                setting3();
                break;
            case 4:
                setting4();
                break;
            case 5:
                setting5();
                break;
            case 6:
                setting6();
                break;
            case 7:
                setting7();
                break;
            case 8:
                setting8();
                break;
            case 9:
                setting9();
                break;
            case 10:
                setting10();
                break;
            case 11:
                setting11();
                break;
        }
    }
    
    /**
     * Applies to: far
     * aligns with the target, kicks the first ball and then acquires the second ball.
     */
    public void setting1() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(5);

        donnie.tracker.alignAuto();
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
    }
    
    /**
     * Applies to: middle; try in near
     * Moves robot forward 20 inches while running acquirer, aligns and kicks.
     *
     * IMPORTANT
     */
    public void setting2() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(20);

        donnie.tracker.alignAuto();
        kick();
    }

    /**
     * Applies to: center
     * Moves robot forward 20 inches while running acquirer,
     * aligns and kicks, moves forward 72 inches while running acquirer.
     */
    public void setting3() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(20);

        donnie.tracker.alignAuto();
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(72); //6 feet
    }

    /**
     * Applies to: far
     * Forward 5 inches, aligns and kicks, forward 72 inches
     */
    public void setting4() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(5);

        donnie.tracker.alignAuto();
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(72); //6 feet
    }

    /**
     * Applies to: center and far
     * aligns with the target, kicks the first ball and then acquires the second ball.  NO straight-drive.  
     */
    public void setting5() {
        donnie.roller.start();
        donnie.dt.forwardInchesRough(15);

        //donnie.tracker.alignAuto();
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesRough(36); //3 feet

        donnie.tracker.alignAuto();
        kick();
    }

    /**
     * Applies to: center and far
     * The robot acquires the first ball, aligns with the target, and kicks it.
     * The robot acquires the second ball, aligns with the target, and kicks it.
     *
     * WORKED BEFORE SHIPPING
     */
    public void setting6() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(15);

        donnie.tracker.alignAuto();
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet

        donnie.tracker.alignAuto();
        kick();
    }

    /**
     * Applies to: far
     * The robot acquires the first ball, aligns with the target, and kicks it.
     * The robot acquires the second ball, aligns with the target, and kicks it.
     * The robot acquires the third ball.
     */
    public void setting7() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(5);

        donnie.tracker.alignAuto();
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet

        donnie.tracker.alignAuto();
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
    }

    /**
     * 
     */
    public void setting8() {
        //similar to setting 6 without aligning in the first kick
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(5);

        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet

        donnie.tracker.alignAuto();
        kick();
    }

    /**
     * Applies to: center and far
     * Similar to setting 6, without auto align on first kick.
     * The robot acquires the first ball, DOES NOT ALIGN with target, and kicks it.
     * The robot acquires the second ball, aligns with the target, and kicks it.
     */
    public void setting9() {
        //similar to setting 6 without aligning in the first kick
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(20);

        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet

        donnie.tracker.alignAuto();
        kick();

    }

    /**
     * Applies to: far
     * The robot acquires the first ball, aligns with the target, and kicks it.
     * The robot acquires the second ball, aligns with the target, and kicks it.
     * The robot acquires the third ball, aligns with the target, and kicks it.
     */
    public void setting10() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(5); // was 30
        donnie.tracker.alignAuto();
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        donnie.tracker.alignAuto();
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        donnie.tracker.alignAuto();
        kick();
    }

    /**
     * Applies to: far
     * Similar to setting 10 without aligning in the first two kicks
     *
     * IMPORTANT
     */
    public void setting11() {
        //Similar to setting 10 without aligning in the first two kicks
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(5); // was 30
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        donnie.tracker.alignAuto();
        kick();
    }

    /**
     * This aligns to target, kicks the ball and stops the acquirer
     * ONLY USE IN AUTONOMOUS, NOT TELEOP
     */
    private void kick() {
        donnie.kicker.shoot();
        /*
         * for broken limit switch, uncomment this, comment shoot()
           donnie.kicker.runKicker();
           Timer.delay(3);
           donnie.kicker.stop();
         */

        donnie.roller.stop();
    }
}










