package com.tbu.wx.http;


public class KeyValue {
    String mKeyString = null;
    String mValueString = null;
    
    /** 
     * <p>Title: </p> 
     * <p>Description: </p> 
     * @param mKeyString
     * @param mValueString 
     */
    public KeyValue(String mKeyString, String mValueString) {
        this.mKeyString = mKeyString;
        this.mValueString = mValueString;
    }

    /**
     * @return the mKeyString
     */
    public String getmKeyString() {
        return mKeyString;
    }

    /**
     * @param mKeyString the mKeyString to set
     */
    public void setmKeyString(String mKeyString) {
        this.mKeyString = mKeyString;
    }

    /**
     * @return the mValueString
     */
    public String getmValueString() {
        return mValueString;
    }

    /**
     * @param mValueString the mValueString to set
     */
    public void setmValueString(String mValueString) {
        this.mValueString = mValueString;
    }

    @Override
    public String toString() {
        return "KeyValue [mKeyString=" + mKeyString + ", mValueString=" + mValueString + "]";
    }
    
    
}
