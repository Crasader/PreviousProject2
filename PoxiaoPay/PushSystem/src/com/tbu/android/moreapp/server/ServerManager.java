package com.tbu.android.moreapp.server;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.content.Context;

import com.tbu.android.moreapp.DebugForMoreGame;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;

public class ServerManager {

	public static String createMoreGameReqStr(Context context, String plginVersion, String enterId,
			String moregame_version, String tbu_id) {
		KeyValue keyValue0 = new KeyValue("plgin_version", plginVersion);
		KeyValue keyValue1 = new KeyValue("moregame_version", moregame_version);
		KeyValue keyValue2 = new KeyValue("enter_id", enterId);
		KeyValue keyValue3 = new KeyValue("tbu_id", tbu_id);
		KeyValue keyValue4 = new KeyValue("si", DeviceInfo.getsi());
		KeyValue keyValue5 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue6 = new KeyValue("hd_type", DeviceInfo.getModle());
		KeyValue keyValue7 = new KeyValue("lac", DeviceInfo.getLac());
		KeyValue keyValue8 = new KeyValue("cid", DeviceInfo.getCid());
		KeyValue keyValue9 = new KeyValue("ua", DeviceInfo.getUA());
		return DoContentJoint(
				keyValue0, 	keyValue1, 	keyValue2, keyValue3,keyValue4,keyValue5,keyValue6,keyValue7,keyValue8,keyValue9);
	}
	
	/**
	 * 发送POST请求
	 * @param urlStr
	 * @param strContent
	 * @return
	 */
	public static String doPost(final String urlStr, final String strContent) {
		DebugForMoreGame.i("[MoreApp]ServerManager->DoPost, urlStr:" + urlStr);
		DebugForMoreGame.i("[MoreApp]ServerManager->DoPost, strContent:" + strContent);
        if (strContent == null) {
            return null;
        }

        try {
            URL url = new URL(urlStr);
            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();

            urlConnection.setRequestMethod("POST");
            urlConnection.setDoInput(true);
            urlConnection.setDoOutput(true);
            urlConnection.setUseCaches(false);
            urlConnection.setRequestProperty("Content-Type","application/x-www-form-urlencoded");
            urlConnection.setConnectTimeout(10 * 1000);
            urlConnection.setReadTimeout(10 * 1000);
            urlConnection.connect();

            DataOutputStream out = new DataOutputStream(urlConnection.getOutputStream());
            out.writeBytes(strContent);
            out.flush();
            out.close();
            InputStream inputStream = urlConnection.getInputStream();
            byte[] byteBuffer = input2byte(inputStream);
            
            String strResult = new String(byteBuffer);
            DebugForMoreGame.i("[MoreApp]ServerManager->DoPost, strJson result =" + strResult);
            inputStream.close();
            urlConnection.disconnect();

            return strResult;
        } catch (Exception e) {
            DebugForMoreGame.e("[MoreApp]ServerManager->DoPost error, e = " + e.toString());
            return null;
        }
    }
	
	public static String DoContentJoint(KeyValue... keyValueArray) {
        if(keyValueArray.length > 0){
            String httpContent = new String();
            for (int i = 0; i<keyValueArray.length;i++) {  
                if(0==i)
                    httpContent += keyValueArray[i].getmKeyString()+"="+keyValueArray[i].getmValueString();//"?"+
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
        }
        byte[] in2b = swapStream.toByteArray();
        return in2b;
    }
}
