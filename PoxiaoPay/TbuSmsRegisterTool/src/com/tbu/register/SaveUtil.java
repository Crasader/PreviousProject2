package com.tbu.register;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Environment;
import android.util.Log;

public class SaveUtil {
	
	/**
	 * 本地共享数据保存工具
	 * 有sd卡需要在sd卡中保存，并且保存在应用中，如果没有sd卡只需保存应用信息
	 */
	private static String QXT_FILENAME="bendiinfo";
	
	public static void saveQXTInfo(final Context context,String number,String province){
		SimpleDateFormat formatter = new SimpleDateFormat ("yyyy-MM-dd HH:mm:ss");
		Date curDate = new Date(System.currentTimeMillis());//获取当前时间
		String savetime = formatter.format(curDate);
		String content=number+";"+province+";"+savetime;
		Log.i("B_DEBUG", "saveQXTInfo 1="+content);
		SharedPreferences preferences = context.getSharedPreferences("bendiqxt", Context.MODE_PRIVATE);
    	SharedPreferences.Editor editor = preferences.edit();
		editor.putString("phone", number);
		editor.putString("province", province);
		editor.putString("savetime", savetime);
		editor.commit();
		
		if (Environment.getExternalStorageState().equals(
                Environment.MEDIA_MOUNTED)) { 
			try {
				Log.i("B_DEBUG", "saveQXTInfo 2="+content);
				File file = new File(Environment.getExternalStorageDirectory(),
						QXT_FILENAME);
				BufferedWriter bw = new BufferedWriter(new FileWriter(file));
				bw.write(content);
				bw.close();				
			} catch (Exception e) {
				e.printStackTrace();
			}
        }
	}
	
	

	
	public static String readQXTInfo(final Context context) {
		SharedPreferences preferences = context.getSharedPreferences("bendiqxt", Context.MODE_PRIVATE);
		if(preferences!=null&&preferences.getString("phone","")!=""){	
			return preferences.getString("phone","")+";"+preferences.getString("province","")+";"+
					preferences.getString("savetime","");
		}
		
		if (Environment.getExternalStorageState().equals(
                Environment.MEDIA_MOUNTED)){ 
    		try {
    			File file = new File(Environment.getExternalStorageDirectory(),
    					QXT_FILENAME);
    			BufferedReader br = new BufferedReader(new FileReader(file));
    			String readline = br.readLine();
    			br.close();
    			Log.i("B_DEBUG", "readQXTInfo readbendiinfo ="+readline);
    			if(readline!=null){
    				String[] infos=readline.toString().split(";");    				
    		    	SharedPreferences.Editor editor = preferences.edit();
    				editor.putString("phone", infos[0]);
    				editor.putString("province", infos[1]);
    				if(infos.length>2){
    					Log.i("B_DEBUG", "readQXTInfo infos[2] ="+infos[2]);
    					editor.putString("savetime", infos[2]);
    				}
    				editor.commit();
    				return preferences.getString("phone","")+";"+preferences.getString("province","")+";"+
					preferences.getString("savetime","");
    				
    			}else{
    				return "";
    			}
    			
    		} catch (Exception e) {
    			e.printStackTrace();
    			return "";
    		}
        }else{
        	return "";
        }
		
    }
}
