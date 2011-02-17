/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;
import edu.wpi.first.wpilibj.*;


/**
 *
 * @author Not  Kevin Wang
 */
public class DESencoder extends Encoder {

    public DESencoder(DigitalSource aSource, DigitalSource bSource, DigitalSource indexSource) {
    super(aSource, bSource, indexSource);
    }

    public DESencoder(DigitalSource aSource, DigitalSource bSource, DigitalSource indexSource, boolean reverseDirection) {
    super(aSource, bSource, indexSource, reverseDirection);
    }

    public DESencoder(DigitalSource aSource, DigitalSource bSource, boolean reverseDirection, EncodingType encodingType) {
    super(aSource, bSource, reverseDirection, encodingType);
    }

    public DESencoder(DigitalSource aSource, DigitalSource bSource) {
    super(aSource, bSource);
    }

    public DESencoder(DigitalSource aSource, DigitalSource bSource, boolean reverseDirection) {
    super(aSource, bSource, reverseDirection);
    }

    public DESencoder(int aChannel, int bChannel, int indexChannel) {
    super(aChannel, bChannel,indexChannel);
    }

    public DESencoder(int aChannel, int bChannel, int indexChannel, boolean reverseDirection) {
    super(aChannel, bChannel, indexChannel, reverseDirection);
    }

    public DESencoder(int aChannel, int bChannel, boolean reverseDirection, EncodingType encodingType) {
    super(aChannel, bChannel, reverseDirection, encodingType);
    }

    public DESencoder(int aChannel, int bChannel) {
    super(aChannel, bChannel);
    }

    public DESencoder(int aChannel, int bChannel, boolean reverseDirection) {
    super(aChannel, bChannel, reverseDirection);
    }

    public DESencoder(int aSlot, int aChannel, int bSlot, int bChannel, int indexSlot, int indexChannel) {
    super(aSlot, aChannel, bSlot, bChannel, indexSlot, indexChannel);
    }

    public DESencoder(int aSlot, int aChannel, int bSlot, int bChannel, int indexSlot, int indexChannel, boolean reverseDirection) {
    super(aSlot, aChannel, bSlot, bChannel,indexSlot,indexChannel, reverseDirection);
    }

    public DESencoder(int aSlot, int aChannel, int bSlot, int bChannel, boolean reverseDirection, EncodingType encodingType) {
    super(aSlot, aChannel, bSlot, bChannel, reverseDirection, encodingType);
    }

    public DESencoder(int aSlot, int aChannel, int bSlot, int bChannel) {
    super(aSlot, aChannel, bSlot, bChannel);
    }

    public DESencoder(int aSlot, int aChannel, int bSlot, int bChannel, boolean reverseDirection) {
    super(aSlot, aChannel, bSlot, bChannel, reverseDirection);
    }
    public void free(){
        super.free();
    }
 // public DESFAGencoder()

}
