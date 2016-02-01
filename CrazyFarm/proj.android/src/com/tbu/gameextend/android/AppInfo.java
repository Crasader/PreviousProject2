package com.tbu.gameextend.android;

import java.util.List;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.util.Log;

public class AppInfo {

	private static String safeAppinfo = "";
	
	public static final String[] SAFEAPPS = { 
		"com.tencent.mm", // 微信
		"com.skymobi.pay.wxplugin"
		// TODO : 支付宝插件
		// TODO : 支付宝
	};
	
	public static void init(Context context) { 
		safeAppinfo = getSafeAppState(context);
	}
	
	public static String getSafeAppState(Context context) {
	if (safeAppinfo == "") {
		for (int i = 0; i < SAFEAPPS.length; i++) {
			safeAppinfo += isAvilible(context,
					SAFEAPPS[i]) ? "1" : "0";
		}
	}
	return safeAppinfo;
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
//                Log.e("MOLO_DEBUG", "packName = " + packName);
                if(packageName.equals(packName)) {
                	return true;
                }
            }   
        }   
        return false;
  }
}
