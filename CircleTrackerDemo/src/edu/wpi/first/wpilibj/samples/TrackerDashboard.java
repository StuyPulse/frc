/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.samples;

import com.sun.squawk.platform.posix.natives.Time;
import edu.wpi.first.wpilibj.AnalogModule;
import edu.wpi.first.wpilibj.Dashboard;
import edu.wpi.first.wpilibj.DigitalModule;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Solenoid;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

/**
 *  Provide a method to update dashboard data.
 * @author dtjones
 */
public class TrackerDashboard {

    public TrackerDashboard() {
        Timer dashTimer = new Timer();
        dashTimer.schedule(new TimerTask() {

            public void run() {
                updateDefaultDashboard();
            }
        }, 0, 100);
    }

    void updateDefaultDashboard() {
        Dashboard lowDashData = DriverStation.getInstance().getDashboardPackerLow();
        lowDashData.addCluster();
        {
            lowDashData.addCluster();
            {     //analog modules
                lowDashData.addCluster();
                {
                    for (int i = 1; i <= 8; i++) {
                        lowDashData.addFloat((float) AnalogModule.getInstance(1).getAverageVoltage(i));
                    }
                }
                lowDashData.finalizeCluster();
                lowDashData.addCluster();
                {
                    for (int i = 1; i <= 8; i++) {
                        lowDashData.addFloat((float) AnalogModule.getInstance(2).getAverageVoltage(i));
                    }
                }
                lowDashData.finalizeCluster();
            }
            lowDashData.finalizeCluster();

            lowDashData.addCluster();
            { //digital modules
                lowDashData.addCluster();
                {
                    lowDashData.addCluster();
                    {
                        int module = 4;
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addShort(DigitalModule.getInstance(module).getAllDIO());
                        lowDashData.addShort(DigitalModule.getInstance(module).getDIODirection());
                        lowDashData.addCluster();
                        {
                            for (int i = 1; i <= 10; i++) {
                                lowDashData.addByte((byte) DigitalModule.getInstance(module).getPWM(i));
                            }
                        }
                        lowDashData.finalizeCluster();
                    }
                    lowDashData.finalizeCluster();
                }
                lowDashData.finalizeCluster();

                lowDashData.addCluster();
                {
                    lowDashData.addCluster();
                    {
                        int module = 6;
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayReverse());
                        lowDashData.addShort(DigitalModule.getInstance(module).getAllDIO());
                        lowDashData.addShort(DigitalModule.getInstance(module).getDIODirection());
                        lowDashData.addCluster();
                        {
                            for (int i = 1; i <= 10; i++) {
                                lowDashData.addByte((byte) DigitalModule.getInstance(module).getPWM(i));
                            }
                        }
                        lowDashData.finalizeCluster();
                    }
                    lowDashData.finalizeCluster();
                }
                lowDashData.finalizeCluster();

            }
            lowDashData.finalizeCluster();

            lowDashData.addByte(Solenoid.getAll());
        }
        lowDashData.finalizeCluster();
        lowDashData.commit();
    }
    Date time = new Date();

    public void updateVisionDashboard(double joyStickX, double gyroAngle, double gyroRate,
            double targetX, Target[] targets) {

        Dashboard highDashData = DriverStation.getInstance().getDashboardPackerHigh();
        highDashData.addCluster(); // wire (2 elements)
        {
            highDashData.addCluster(); // tracking data
            {
                highDashData.addDouble(joyStickX); // Joystick X
                highDashData.addDouble(((gyroAngle + 360.0 + 180.0) % 360.0) - 180.0); // angle
                highDashData.addDouble(gyroRate); // angular rate
                highDashData.addDouble(targetX); // other X
                }
            highDashData.finalizeCluster();
            highDashData.addCluster(); // target Info (2 elements)
            {
                highDashData.addArray();
                {
                    for (int i = 0; i < targets.length; i++) {
                        highDashData.addCluster(); // targets
                        {
                            highDashData.addDouble(targets[i].m_score); // target score
                            highDashData.addCluster(); // Circle Description (5 elements)
                            {
                                highDashData.addCluster(); // Position (2 elements)
                                {
                                    highDashData.addFloat((float) (targets[i].m_xPos / targets[i].m_xMax)); // X
                                    highDashData.addFloat((float) targets[i].m_yPos); // Y
                                    }
                                highDashData.finalizeCluster();

                                highDashData.addDouble(targets[i].m_rotation); // Angle
                                highDashData.addDouble(targets[i].m_majorRadius); // Major Radius
                                highDashData.addDouble(targets[i].m_minorRadius); // Minor Radius
                                highDashData.addDouble(targets[i].m_rawScore); // Raw score
                                }
                            highDashData.finalizeCluster(); // Position
                            }
                        highDashData.finalizeCluster(); // targets
                        }
                }
                highDashData.finalizeArray();


                highDashData.addInt((int) time.getTime());
            }
            highDashData.finalizeCluster(); // target Info
            }
        highDashData.finalizeCluster(); // wire
        highDashData.commit();
    }
}
