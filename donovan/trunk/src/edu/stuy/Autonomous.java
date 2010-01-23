package edu.stuy;

/**
 * These are the different methods for autonomus mode.
 * @author Prog
 */
public class Autonomous {

    public void runSettingNum(int settingNum) {
        switch(settingNum) {
            case 1: setting1(); break;
            case 2: setting2(); break;
            case 3: setting3(); break;
            case 4: setting4(); break;
            case 5: setting5(); break;
            case 6: setting6(); break;
            case 7: setting7(); break;
                
        }
    }
    /**
     * This will move robot forward 30 inches while running acquirer
     */
    public void setting1() {

    }

    /**
     * This will perform setting1 and then stop the acquirer and shoot
     */
    public void setting2() {
        setting1();

    }

    /**
     * This will perform setting2 and then move 6 feet forward while running acquirer
     */
    public void setting3() {
        setting2();

    }

    /**
     * This will move robot back 16 feet
     */
    public void setting4() {

    }
    /**
     * This will perform setting2 and then go 3 feet forward while running acquirer
     */
    public void setting5() {
        setting2();

    }
    /**
     * This will perform setting5 and then stop the acquirer and shoot
     */
    public void setting6() {
        setting5();

    }
    /**
     * This will perform setting6 and then move robot
     * forward 3 feet while running acquirer
     */
    public void setting7() {
        setting6();

    }

}
