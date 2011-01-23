/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.samples;

import com.sun.squawk.util.MathUtils;
import edu.wpi.first.wpilibj.image.ColorImage;
import edu.wpi.first.wpilibj.image.CurveOptions;
import edu.wpi.first.wpilibj.image.EllipseDescriptor;
import edu.wpi.first.wpilibj.image.EllipseMatch;
import edu.wpi.first.wpilibj.image.MonoImage;
import edu.wpi.first.wpilibj.image.NIVisionException;
import edu.wpi.first.wpilibj.image.ShapeDetectionOptions;
import edu.wpi.first.wpilibj.util.SortedVector;

/**
 *
 * @author dtjones
 */
public class Target {

    public double m_majorRadius;
    public double m_minorRadius;
    public double m_xPos;
    public double m_yPos;
    public double m_score;
    public double m_rawScore;
    public double m_rotation;
    public boolean m_bothFound;

    public double m_xMax;

    Target() {
    }

    public double getHorizontalAngle() {
        double x = m_xPos;
        x = (x * 9.0 / m_xMax);
        x = MathUtils.atan2(x, 20.0);
        x = x * 180.0 / Math.PI;
        return x;
    }

    public String toString() {
        return "Target Found:\n" +
                "  Pos x: " + m_xPos + "  y: " + m_yPos + "\n" +
                "  Radius major: " + m_majorRadius + " minor: " + m_minorRadius + "\n" +
                "  Rotation: " + m_rotation + " Score: " + m_score + " Both Found: " + m_bothFound + "\n";
    }
    static EllipseDescriptor ellipseDescriptor = new EllipseDescriptor(3, 200, 3, 100);
    static CurveOptions curveOptions = new CurveOptions(0, 40, 1, 25, 15, 15, 10, 1, 0);
    static ShapeDetectionOptions shapeOptions = new ShapeDetectionOptions(ShapeDetectionOptions.IMAQ_GEOMETRIC_MATCH_SHIFT_INVARIANT, 0, 0, 75, 125, 500);


    public static Target[] findCircularTargets(ColorImage image) throws NIVisionException { //include gregs other parameters?
        int width = image.getWidth();
        int height = image.getHeight();

        MonoImage lumPlane = image.getLuminancePlane();

        EllipseMatch[] results = lumPlane.detectEllipses(ellipseDescriptor, curveOptions, shapeOptions, null);

        lumPlane.free();

        SortedVector.Comparator targetComparator = new SortedVector.Comparator() {

            public int compare(Object target1, Object target2) {
                if (((Target) target1).m_score > ((Target) target2).m_score) {
                    return 1;
                }
                if (((Target) target1).m_score < ((Target) target2).m_score) {
                    return -1;
                }
                return 0;
            }
        };

        SortedVector sortedTargetList = new SortedVector(targetComparator);
        SortedVector combinedTargetList = new SortedVector(targetComparator);

        for (int i = 0; i < results.length; i++) {
            Target target = new Target();
            target.m_rawScore = results[i].m_score;
            target.m_score =
                    (results[i].m_majorRadius * results[i].m_minorRadius) / (1001 - results[i].m_score) / (height * width) * 100;
            target.m_majorRadius = results[i].m_majorRadius / height;
            target.m_minorRadius = results[i].m_minorRadius / height;
            target.m_xPos = (2.0 * results[i].m_xPos - width) / height; //always divide by height so that x and y are same units
            target.m_yPos = (2.0 * results[i].m_yPos - height) / height;
            target.m_rotation = results[i].m_rotation;
            target.m_bothFound = false;
            target.m_xMax = (double)width / height;
            sortedTargetList.addElement(target);
        }

        while (!sortedTargetList.isEmpty()) {
            Target firstTarget = (Target) sortedTargetList.elementAt(0);
            for (int i = 1; i < sortedTargetList.size(); i++) {
                Target otherTarget = (Target) sortedTargetList.elementAt(i);
                if ((Math.abs(firstTarget.m_xPos - otherTarget.m_xPos) < Math.min(firstTarget.m_minorRadius, otherTarget.m_minorRadius)) &&
                        (Math.abs(firstTarget.m_yPos - otherTarget.m_yPos) < Math.min(firstTarget.m_majorRadius, otherTarget.m_majorRadius))) {
                    firstTarget.m_xPos = (firstTarget.m_xPos + otherTarget.m_xPos) / 2;
                    firstTarget.m_yPos = (firstTarget.m_yPos + otherTarget.m_yPos) / 2;
                    firstTarget.m_rawScore += otherTarget.m_rawScore;
                    firstTarget.m_score += otherTarget.m_score;
                    firstTarget.m_majorRadius = Math.max(firstTarget.m_majorRadius, otherTarget.m_majorRadius);
                    firstTarget.m_minorRadius = Math.max(firstTarget.m_minorRadius, otherTarget.m_minorRadius);
                    firstTarget.m_bothFound = true;
                    sortedTargetList.removeElementAt(i);
                    break;
                }
            }
            sortedTargetList.removeElementAt(0);
            combinedTargetList.addElement(firstTarget);
        }
        Target[] toReturn = new Target[combinedTargetList.size()];
        combinedTargetList.copyInto(toReturn);
        return toReturn;
    }
}
