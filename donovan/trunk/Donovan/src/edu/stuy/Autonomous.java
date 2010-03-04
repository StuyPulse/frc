package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * These are the different methods for autonomus mode.
 * Best routines (currently):
 *   Near:   4
 *   Center: 9
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
     * Applies to: anywhere
     * Moves robot forward 30 inches while running acquirer, stops acquirer.
     */
    public void setting1() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);
        donnie.roller.stop();
    }

    /**
     * Applies to: anywhere
     * Moves robot forward 30 inches while running acquirer, aligns and kicks.
     */
    public void setting2() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);

        donnie.tracker.alignAuto();
        kick();
    }

    /**
     * Applies to: center and far
     * Moves robot forward 30 inches while running acquirer,
     * aligns and kicks, moves forward 72 inches while running acquirer.
     */
    public void setting3() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);

        donnie.tracker.alignAuto();
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(72); //6 feet
    }

    /**
     * Applies to: near
     * This will move robot back 16 feet
     * Robot should be backwards, to push the ball into goal
     * Probably won't work because backInches doesn't have straight code
     */
    public void setting4() {
        donnie.dt.backInches(192); //16 feet
        // probably won't work

        // use drive straight code (Oscar)?
    }

    /**
     * Applies to: center and far
     * aligns with the target, kicks the first ball and then acquires the second ball.
     */
    public void setting5() {


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);

        donnie.tracker.alignAuto();
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
    }

    /**
     * Applies to: center and far
     * The robot acquires the first ball, aligns with the target, and kicks it.
     * The robot acquires the second ball, aligns with the target, and kicks it.
     */
    public void setting6() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);

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
        donnie.dt.forwardInchesOscar(30);

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
     * Applies to: near
     * Goes back 36 inches.
     * May not work properly due to lack of straight code in backInches
     * (See good straight code in forwardInchesOscar.)
     */
    public void setting8() {
        donnie.dt.backInches(36);
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
        donnie.dt.forwardInchesOscar(30);

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
