/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import com.sun.squawk.util.*;
import edu.wpi.first.wpilibj.image.*;
import edu.wpi.first.wpilibj.util.*;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Ginkgo
 */
public class DESTarget {

    public static DESTarget[] findCircularTargets(ColorImage image) throws NIVisionException { //include gregs other parameters?
        int width = image.getWidth();
        int height = image.getHeight();

        MonoImage lumPlane = image.getLuminancePlane();

        EllipseMatch[] results = lumPlane.detectEllipses(ellipseDescriptor, curveOptions, shapeOptions, null);
        if (results.length > 0 && results[0] != null) {
            System.out.println("Target found");
        }

        lumPlane.free();

        SortedVector.Comparator targetComparator = new SortedVector.Comparator() {

            public int compare(Object target1, Object target2) {
                if (((DonovanTarget) target1).m_score > ((DonovanTarget) target2).m_score) {
                    return 1;
                }
                if (((DonovanTarget) target1).m_score < ((DonovanTarget) target2).m_score) {
                    return -1;
                }
                return 0;
            }
        };

        SortedVector sortedTargetList = new SortedVector(targetComparator);
        SortedVector combinedTargetList = new SortedVector(targetComparator);

        for (int i = 0; i < results.length; i++) {
            DonovanTarget target = new DonovanTarget();
            target.m_rawScore = results[i].m_score;
            target.m_score =
                    (results[i].m_majorRadius * results[i].m_minorRadius) / (1001 - results[i].m_score) / (height * width) * 100;
            target.m_majorRadius = results[i].m_majorRadius / height;
            target.m_minorRadius = results[i].m_minorRadius / height;
            target.m_xPos = (2.0 * results[i].m_xPos - width) / height; //always divide by height so that x and y are same units
            target.m_yPos = (2.0 * results[i].m_yPos - height) / height;
            target.m_rotation = results[i].m_rotation;
            target.m_bothFound = false;
            target.m_xMax = (double) width / height;
            sortedTargetList.addElement(target);
        }

        while (!sortedTargetList.isEmpty()) {
            DonovanTarget firstTarget = (DonovanTarget) sortedTargetList.elementAt(0);
            for (int i = 1; i < sortedTargetList.size(); i++) {
                DonovanTarget otherTarget = (DonovanTarget) sortedTargetList.elementAt(i);
                if ((Math.abs(firstTarget.m_xPos - otherTarget.m_xPos) < Math.min(firstTarget.m_minorRadius, otherTarget.m_minorRadius))
                        && (Math.abs(firstTarget.m_yPos - otherTarget.m_yPos) < Math.min(firstTarget.m_majorRadius, otherTarget.m_majorRadius))) {
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
        DonovanTarget[] toReturn = new DonovanTarget[combinedTargetList.size()];
        combinedTargetList.copyInto(toReturn);
        return toReturn;
    }
}
