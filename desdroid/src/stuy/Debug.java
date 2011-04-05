/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

/**
 *
 * @author Alex
 */
public class Debug {
    // Set to true when debugging; it will print out exception stack traces
    // Set to false for competition: log exceptions to a file on the cRIO

    public static final boolean DEBUG_MODE = false;

    /**
     * If in debug mode, prints specified string without a newline
     * @param s
     */
    public static void print(String s) {
        if (DEBUG_MODE) {
            System.out.print(s);
        }
    }

    public static void print(int s) {
        if (DEBUG_MODE) {
            System.out.print(s);
        }
    }

    public static void print(double s) {
        if (DEBUG_MODE) {
            System.out.print(s);
        }
    }

    public static void print(boolean s) {
        if (DEBUG_MODE) {
            System.out.print(s);
        }
    }

    /**
     * If in debug mode, prints specified string with a newline
     * @param s
     */
    public static void println(String s) {
        if (DEBUG_MODE) {
            System.out.println(s);
        }
    }

    public static void println(double s) {
        if (DEBUG_MODE) {
            System.out.println(s);
        }
    }

    public static void println(int s) {
        if (DEBUG_MODE) {
            System.out.println(s);
        }
    }

    public static void println(boolean s) {
        if (DEBUG_MODE) {
            System.out.println(s);
        }
    }

    /**
     * True if in debug mode, false otherwise.
     * @return state
     */
    public static boolean getMode() {
        return DEBUG_MODE;
    }
}
