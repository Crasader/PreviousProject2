package com.tbu.androidtools.device;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Environment;
import android.os.StatFs;
import android.util.Log;

/**
 * 
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-6 上午11:07:09
*
 */
public class DeviceUtil {

	/**
     * 总的ROM大小 
     * @return
     */
    public static long getTotalInternalMemorySize() {
        File path = Environment.getDataDirectory();
        StatFs stat = new StatFs(path.getPath());
        long blockSize = stat.getBlockSize();
        long totalBlocks = stat.getBlockCount();
        return totalBlocks * blockSize;
    }
    
    /**
     * 总的内存大小 RAM
     * @return 总的内存大小 RAM
     */
    public static long getTotalMemory() {
        String str1 = "/proc/meminfo";// 系统内存信息文件
        String str2;
        String[] arrayOfString;
        long initial_memory = 0;

        try {
            FileReader localFileReader = new FileReader(str1);
            BufferedReader localBufferedReader = new BufferedReader(
                    localFileReader, 8192);
            str2 = localBufferedReader.readLine();// 读取meminfo第一行，系统总内存大小

            arrayOfString = str2.split("//s+");
            for (String num : arrayOfString) {
                Log.i(str2, num + "/t");
            }
            String tmp = null;
            if (null != (tmp = arrayOfString[0])) {
                arrayOfString = tmp.split(" ");
                for (String s : arrayOfString) {
                    if (isNumber(s)) {
                        Log.d(DeviceInfo.TAG, "分割后的字符串:" + s);
                        tmp = s;
                        break;
                    }
                }
            }
            initial_memory = Integer.valueOf(tmp).intValue();// 获得系统总内存，单位是KB，乘以1024转换为Byte
            localBufferedReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return initial_memory;
    }
    
    /**
     * 判断是否可转换为数字
     * @param str
     * @return 
     */
    public static boolean isNumber(String str)
    {
        Pattern pattern = Pattern.compile("[0-9]{1,}");
        Matcher matcher = pattern.matcher((CharSequence) str);
        boolean result = matcher.matches();
        return result;
    }
    
    /**
     * 判断是否安装指定包名的应用
     * @param context
     * @param packageName
     * @return
     */
    public static  boolean isAvilible(final Context context, final String packageName){   
    		if(packageName == null) {
    			return false;
    		}
    		if(packageName.equals("")) {
    			return false;
    		}
    	
        final PackageManager packageManager = context.getPackageManager();  
        List<PackageInfo> packageInfos = packageManager.getInstalledPackages(0);   
        if(packageInfos != null){   
            for(int i = 0; i < packageInfos.size(); i++){   
                String packName = packageInfos.get(i).packageName;   
                if(packageName.equals(packName)) {
                		return true;
                }
            }   
        }   
        return false;
  }
}
