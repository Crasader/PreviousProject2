package com.tbu.androidtools.ugly.http;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import android.util.Log;

/**
 * 
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-12 上午10:15:40
*
 */
public class PoxiaoHttpUtil {
	
	public static String DoContentJoint(KeyValue... keyValueArray){
        if(keyValueArray.length > 0){
            String httpContent = new String();
            for (int i = 0; i<keyValueArray.length;i++) {  
                if(0==i)
                    httpContent += "?"+keyValueArray[i].getmKeyString()+"="+keyValueArray[i].getmValueString();
                else
                    httpContent += "&"+keyValueArray[i].getmKeyString()+"="+keyValueArray[i].getmValueString();
            } 
            
            return httpContent;
        }
        
        return null;
    }
	
	public static final byte[] input2byte(InputStream inStream)
            throws IOException {
        ByteArrayOutputStream swapStream = new ByteArrayOutputStream();
        byte[] buff = new byte[100];
        int rc = 0;
        while ((rc = inStream.read(buff, 0, 100)) > 0) {
            swapStream.write(buff, 0, rc);
            Log.e("MMP4", String.valueOf(rc));
        }
        byte[] in2b = swapStream.toByteArray();
        return in2b;
    }
}
