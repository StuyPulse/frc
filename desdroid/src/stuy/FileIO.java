/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import com.sun.squawk.io.BufferedReader;
import com.sun.squawk.microedition.io.FileConnection;
import com.sun.squawk.util.StringTokenizer;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.microedition.io.Connector;

/**
 *
 * @author Kevin Wang
 */
public class FileIO {

    private static String getFileContents(String filename) {
        String url = "file:///" + filename; // TODO: Make a directory for the text files
        String contents = "";
        try {
            FileConnection c = (FileConnection) Connector.open(url);
            BufferedReader buf = new BufferedReader(new InputStreamReader(c.openInputStream()));
            String line = "";
            while ((line = buf.readLine()) != null) {
                contents += line + "\n";
            }
            c.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return contents;
    }

    public static double[] getArray(String filename) {
        String raw = getFileContents(filename);
        StringTokenizer st = new StringTokenizer(raw);
        double[] array = new double[st.countTokens()];
        int i = 0;
        while (st.hasMoreTokens()) {
            array[i++] = Double.parseDouble(st.nextToken());
        }
        return array;
    }
}
