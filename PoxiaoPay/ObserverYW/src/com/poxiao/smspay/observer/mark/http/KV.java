package com.poxiao.smspay.observer.mark.http;

/**
 * @ClassName: KeyValue
 * @Description: TODO
 * @author songivan
 * @date 2013年9月5日 上午10:09:00
 */
public class KV {
    String mKS = null;
    String mVS = null;
    
    /** 
     * <p>Title: </p> 
     * <p>Description: </p> 
     * @param mKS
     * @param mVS 
     */
    public KV(String mKS, String mVS) {
        super();
        this.mKS = mKS;
        this.mVS = mVS;
    }

    /**
     * @return the mKeyString
     */
    public String getMks() {
        return mKS;
    }

    /**
     * @param mKS the mKeyString to set
     */
    public void setMks(String mKS) {
        this.mKS = mKS;
    }

    /**
     * @return the mValueString
     */
    public String getMvs() {
        return mVS;
    }

    /**
     * @param mVS the mValueString to set
     */
    public void setMvs(String mVS) {
        this.mVS = mVS;
    }

    @Override
    public String toString() {
        return "KeyValue [mKeyString=" + mKS + ", mValueString=" + mVS + "]";
    }
    
    
}
