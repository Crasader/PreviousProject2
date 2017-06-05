package com.tbu.android.lamy.util;

import java.io.File;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Environment;
/**
 * 
 * @author molo
 *
 */
public class DownloadUtil {

	public static final String PUSH_FILE_NAME = "moneydownload";
	public static final String PUSH_FILE_SUCCESS_NAME = "success";
	
	/**
	 * 判断设备是否存在SD卡(外部存储)。
	 * @return true,存在。false,不存在。
	 */
	public static boolean isSDCardExist() {
	    return Environment.getExternalStorageState().equals(
	    			Environment.MEDIA_MOUNTED);
	}
	
	/**
	 * 获取下载文件的存放路径
	 * @param fileName
	 * @param version
	 * @return
	 */
	public static String getSdFilePath(Context context, String fileName, String version){
		return (getSdRootFilePath() + File.separator +
				fileName + version + DownloadUtil.getRandomNumber(context) + ".apk");
	}
	
	public static String getSdRootFilePath() {
		return (Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator +
				PUSH_FILE_NAME );
	}
	
	public static String getSdRootSuccessFilePath() {
		return (Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator +
				PUSH_FILE_NAME+ File.separator + PUSH_FILE_SUCCESS_NAME);
	}
	
	public static String getNoSdFilePath(Context context, String fileName, String version){
		return (context.getFilesDir().getAbsolutePath() + File.separator +
				fileName + version + DownloadUtil.getRandomNumber(context) + ".apk");
	}
	
	public static String getNoSdReadFilePath(Context context, String fileName, String version){
		return fileName + version + DownloadUtil.getRandomNumber(context)  + ".apk";
	}
	
	/**
	 * 如果所在的目录不存在，要写入文件，在Android平台不会自动创建文件夹，会报错：
	 * open failed: ENOENT (No such file or directory).
	 * 所以需要自己创建以来路径上的文件夹。
	 * @param filePath
	 */
	public static void makeRootDirectory() {  
        File file = null;  
        try {  
            file = new File(DownloadUtil.getSdRootFilePath());  
            if (!file.exists()) { 
            		Debug.i("DownloadUtil->makeRootDirectory, [create]filePath = " + 
            				DownloadUtil.getSdRootFilePath());
                file.mkdir();  
            } 
            try{
            		file = new File(DownloadUtil.getSdRootSuccessFilePath());  
                if (!file.exists()) { 
                		Debug.i("DownloadUtil->makeRootDirectory, [create]filePath = " + 
                				DownloadUtil.getSdRootSuccessFilePath());
                    file.mkdir();  
                } 
            } catch (Exception e) {  
        		Debug.i("DownloadUtil->makeRootDirectory fail, filePath = " + 
        				DownloadUtil.getSdRootSuccessFilePath());
            }
            
        } catch (Exception e) {  
        		Debug.i("DownloadUtil->makeRootDirectory fail, filePath = " + 
        				DownloadUtil.getSdRootFilePath());
        }  
    }
	
	public static String getRandomNumber(Context context) {
		
		SharedPreferences sp = context.getSharedPreferences(PUSH_FILE_NAME, 0);
		String result = sp.getString("RANDOM_NUMBR", "00000");
		if("00000".equals(result)) {
			String buffer = String.valueOf(System.currentTimeMillis());
			result = "_" + buffer.substring(buffer.length() - 9, buffer.length()-1);
			Editor editor = sp.edit();
			editor.putString("RANDOM_NUMBR", result);
			editor.commit();
		}
		return result;
	}
}
