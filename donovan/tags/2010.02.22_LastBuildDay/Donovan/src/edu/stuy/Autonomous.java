package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * These are the different methods for autonomus mode.
 * Note: A foot is 12 inches, in case you didn't know.
 * @author Prog
 */
public class Autonomous {

    Donovan donnie;

    public Autonomous(Donovan d) {
        donnie = d;
        // set distance per pulse of encoder
        //  move = new Move();
    }

    public void runSettingNum(int settingNum) {
        switch (settingNum) {
            case 0:
                setting0();
                break;
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

    public void setting0() {
        /*donnie.roller.start();
        donnie.dt.forwardInchesCharlie(30);
        kick();
         *
         */
    }

    /**
     * This will move robot forward 30 inches while running acquirer
     */
    public void setting1() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);
        donnie.roller.stop();
    }

    /**
     * This will perform setting1, shoot and then stop the acquirer
     */
    public void setting2() {
        donnie.roller.start();
        donnie.dt.forwardInches(30);
        kick();
    }

    /**
     * This will perform setting2 and then move 6 feet forward while running acquirer
     */
    public void setting3() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);

        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(72); //6 feet
    }

    /**
     * This will move robot back 16 feet
     * CHECK IF THIS INSTRUCTION IS CORRECT
     */
    public void setting4() {
        donnie.dt.backInches(192); //16 feet
    }

    /**
     * This will perform setting2 and then go 3 feet forward while running acquirer
     */
    public void setting5() {
        donnie.tracker.alignAuto();
        System.out.println("done aligning");
        donnie.kicker.shoot();

        /*
        donnie.roller.start();
        donnie.dt.forwardInches(30);
        kick();


        donnie.roller.start();
        donnie.dt.forwardInches(36); //3 feet
         * */

    }

    /**
     * This will perform setting5 and then stop the acquirer and shoot
     */
    public void setting6() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        kick();
    }

    /**
     * This will perform setting6 and then move robot
     * forward 3 feet while running acquirer
     */
    public void setting7() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        kick();


        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
    }

    public void setting8() {
        donnie.dt.backInches(36);
    }

    /**
     * Kicks three balls in a row:
     * 30 inches from bot to first ball,
     * then 3 feet to the next two
     */
    public void setting9() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        kick();

        donnie.roller.start();
        donnie.dt.forwardInchesOscar(36); //3 feet
        kick();
    }

    public void setting10() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);
        kick();
    }

    public void setting11() {
        donnie.roller.start();
        donnie.dt.forwardInchesOscar(30);
        kick();
    }

    /**
     * This aligns to target, kicks the ball and stops the acquirer
     * ONLY USE IN AUTONOMOUS, NOT TELEOP
     */
    private void kick() {
        donnie.tracker.alignAuto();
        donnie.kicker.shoot();
//        donnie.kicker.runKicker();
        donnie.roller.stop();
//        Timer.delay(3);
//        donnie.kicker.stop();

    }
}
