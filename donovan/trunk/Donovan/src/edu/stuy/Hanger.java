/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Developer
 */
public class Hanger implements Ports {

    Victor winch;
    Servo aFrame;
    boolean aFrameDeployed;

    public Hanger(int winchChannel, int aFrameChannel) {
        winch = new Victor(winchChannel);
        aFrame = new Servo(aFrameChannel);
        aFrameDeployed = false;

    }

    public void startWinch() {
        if (aFrameDeployed) {
            winch.set(-1.0);
        } else {
            System.out.println("AFrame not yet deployed");
        }
    }

    public void stopWinch() {
        winch.set(0.0);
    }

    public void reverseWinch() {
        if (aFrameDeployed) {
            winch.set(0.25);
        } else {
            System.out.println("AFrame not yet deployed");
        }
    }

    public void setWinch(double getValue) {
        winch.set(getValue);
    }

    public void deployAFrame() {
        aFrame.set(1);
        aFrameDeployed = true;
    }

    public void setAFrame(double value) {
        aFrame.set(value);
    }
}
