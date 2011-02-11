package stuy;

import com.sun.squawk.util.MathUtils;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.image.*;

import edu.wpi.first.wpilibj.util.SortedVector;

/* ALGO
 * 1. 
 */
public class DESTarget implements PIDSource {

    public double m_majorRadius;
    public double m_minorRadius;
    public double m_xPos;
    public double m_yPos;
    public double m_score;
    public double m_rawScore;
    public double m_rotation;
    public boolean m_bothFound;
    public double m_xMax;

    public double getHorizontalAngle() {
        double x = m_xPos;
        x = (x * 9.0 / m_xMax);
        x = MathUtils.atan2(x, 20.0);
        x = x * 180.0 / Math.PI;
        return x;
    }

    public double pidGet() {
        return m_xPos;
    }

    public String toString() {
        return "Target Found:\n"
                + "  Pos x: " + m_xPos + "  y: " + m_yPos + "\n"
                + "  Radius major: " + m_majorRadius + " minor: " + m_minorRadius + "\n"
                + "  Rotation: " + m_rotation + " Score: " + m_score + " Both Found: " + m_bothFound + "\n";
    }
    static EllipseDescriptor ellipseDescriptor = new EllipseDescriptor(3, 200, 3, 100);
    static CurveOptions curveOptions = new CurveOptions(0, 40, 1, 25, 15, 15, 10, 1, 0);
    static ShapeDetectionOptions shapeOptions = new ShapeDetectionOptions(ShapeDetectionOptions.IMAQ_GEOMETRIC_MATCH_SHIFT_INVARIANT, 0, 0, 75, 125, 500);

    public static DESTarget[] findCircularTargets(ColorImage image) throws NIVisionException { //include gregs other parameters?
        int width = image.getWidth();
        int height = image.getHeight();

        BinaryImage binImage = image.thresholdHSL(0, 255, 0, 21, 160, 255);
        binImage.write("BINIMAGE.png");
        binImage.free();
        HSLImage hslImage = new HSLImage("BINIMAGE.png");

        MonoImage lumPlane = hslImage.getLuminancePlane();
        hslImage.free();

        EllipseMatch[] results = lumPlane.detectEllipses(ellipseDescriptor, curveOptions, shapeOptions, null);
        lumPlane.free();


        SortedVector.Comparator targetComparator = new SortedVector.Comparator() {

            public int compare(Object target1, Object target2) {
                if (((DESTarget) target1).m_score > ((DESTarget) target2).m_score) {
                    return 1;
                }
                if (((DESTarget) target1).m_score < ((DESTarget) target2).m_score) {
                    return -1;
                }
                return 0;
            }
        };

        SortedVector sortedTargetList = new SortedVector(targetComparator);

        for (int i = 0; i < results.length; i++) {

            DESTarget target = new DESTarget();
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

          /*  System.out.println("\n Mscore= " + results[i].m_score + " \n major rad= " + results[i].m_majorRadius + "\n Minor Radius= " + results[i].m_minorRadius + "\nScore="
                     + target.m_score); */
            sortedTargetList.addElement(target);
        }


        DESTarget[] toReturn = new DESTarget[sortedTargetList.size()];
        sortedTargetList.copyInto(toReturn);
        return toReturn;
    }
}
