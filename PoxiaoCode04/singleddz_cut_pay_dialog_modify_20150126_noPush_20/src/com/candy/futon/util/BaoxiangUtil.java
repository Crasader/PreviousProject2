package com.candy.futon.util;

import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.domain.GameConfig;

import android.app.Activity;

public class BaoxiangUtil {

	public static int getBaoxiangCount(Activity activity){
		int result = 0;
		
		if(GameConfig.getInstance().checkBaoxiang()){
			result += 1;
		}
		result += GameConfig.getInstance().baoxiangCount;
		return result;
	}
	
	
	public static boolean useBaoXiang(Activity activity){
		int count = getBaoxiangCount(activity);
		if(count<=0){
			return false;
		}
		if(GameConfig.getInstance().checkBaoxiang()){
			GameConfig.getInstance().setBaoxiangReceived();
			GameConfig.getInstance().save(activity);
			return true;
		}
		GameConfig.getInstance().baoxiangCount -= 1;
		GameConfig.getInstance().save(activity);
		return true;
	}
	
	
}
