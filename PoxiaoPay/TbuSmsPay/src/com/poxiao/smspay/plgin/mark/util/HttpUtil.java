package com.poxiao.smspay.plgin.mark.util;

import java.io.DataOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpUtil {

	/**
	 * 发送POST请求
	 * @param urlStr
	 * @param strContent
	 * @return
	 */
	public static String DoPost(final String urlStr, final String strContent) {
		Debug.i("Mark->DoPost, urlStr:" + urlStr);
		Debug.i("Mark->DoPost, strContent:" + strContent);
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
            byte[] byteBuffer = MarkUtil.input2byte(inputStream);
            
            String strResult = new String(byteBuffer);
            Debug.i("Mark->DoPost, strJson result =" + strResult);
            inputStream.close();
            urlConnection.disconnect();

            return strResult;
        } catch (Exception e) {
            Debug.e("Mark[v=1]->DoPost error, e = " + e.toString());
            return null;
        }
    }
}
