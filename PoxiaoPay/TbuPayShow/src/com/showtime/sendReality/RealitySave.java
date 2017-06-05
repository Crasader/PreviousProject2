package com.showtime.sendReality;

import android.content.Context;
import android.content.SharedPreferences;

public class RealitySave {
	private static SharedPreferences sharedPreferences;
	private static RealitySave realitySave;

	public static RealitySave getrealitySave(Context content) {
		if (null == realitySave) {
			realitySave = new RealitySave();
		}
		getIPreferences(content);
		return realitySave;
	}

	public static SharedPreferences getIPreferences(Context content) {
		if (null == sharedPreferences) {
			sharedPreferences = content.getSharedPreferences(
					"SaveCumulativeXML", Context.MODE_PRIVATE);
		}
		return sharedPreferences;
	}

	public static void setSaveCumulative(Context content, int number) {
		number = sharedPreferences.getInt("number", 0) + number;
		SharedPreferences.Editor localEditor = getIPreferences(content).edit();
		localEditor.putInt("number", number);
		if (localEditor.commit()) {
			System.out.println("提交成功");
		} else {
			System.out.println("提交失败");
		}

	}

	public static int getSaveCumulative() {
		return sharedPreferences.getInt("number", 0);
	}
}
