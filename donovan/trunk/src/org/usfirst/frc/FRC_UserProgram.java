package org.usfirst.frc;

/*
 * StartApplication.java
 *
 */
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

/**
 * The startApp method of this class is called by the VM to start the
 * application.
 * 
 * The manifest specifies this class as MIDlet-1, which means it will
 * be selected for execution.
 */
public class FRC_UserProgram extends MIDlet {

    protected void startApp() throws MIDletStateChangeException {
        System.out.println("Hello World");
    }

    protected void pauseApp() {
    }

    protected void destroyApp(boolean unconditional) throws MIDletStateChangeException {
    }
    
}
