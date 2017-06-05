package com.d.avos;

import android.app.Activity;
import android.content.Context;

import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;

/**
 * 统计相关内容,大部分是AvosCloud的,杂项包括指盟的广告
 * 
 * @author QZ
 *
 */
public class TbuCloudUtil {

	/**
	 * 习惯上在Application的onCreate()中调用
	 * 
	 * @param context
	 */
	public static void initTbuCloud(final Context context) {
		TbuCloud.initCloud(context, new TbuCallback() {
			@Override
			public void result(boolean result) {
				if (result) {
					Debug.i("初始化avos成功");
				}
			}
		}, AvosConfigUtil.getAvosAppId(), AvosConfigUtil.getAvosAppKey(),
				AppInfo.getVersion());
		TbuCloud.openDataRecord = AvosConfigUtil.isRecordGameDetail(); // 关闭数据记录

	}

	public static void initAvos(Activity activity) {
		TbuCloudUtil.markAppOpened(activity);
		TbuCloud.markUserType(activity.getApplicationContext());
		TbuCloud.markUserLogin(activity.getApplicationContext(),
				System.currentTimeMillis());
		if (AvosConfigUtil.isRecordGameDetail()) {
			initPh(activity.getApplicationContext(), activity.getClass());
		}
	}

	public static void markAppOpened(Activity activity) {
		// AVOS进入标记
		TbuCloud.markAppOpened(activity);
	}

	/**
	 * 需要在每个activity的onPause方法中调用 如果你的 Activity 之间有继承或者控制关系请不要同时在父和子 Activity
	 * 中重复添加 onPause 和 onResume 方法，否则会造成重复统计
	 * 
	 * @param activity
	 */
	public static void markOnPause(Activity activity) {
		TbuCloud.markOnPause(activity);
	}

	/**
	 * 需要在每个activity的onResume中调用 如果你的 Activity 之间有继承或者控制关系请不要同时在父和子 Activity
	 * 中重复添加 onPause 和 onResume 方法，否则会造成重复统计
	 * 
	 * @param activity
	 */
	public static void markOnResume(Activity activity) {
		TbuCloud.markOnResume(activity);
	}



	public static void initPh(final Context context,
			final Class<? extends Activity> cls) {
		// try {
		// com.avos.avoscloud.AVInstallation.getCurrentInstallation()
		// .saveInBackground(new com.avos.avoscloud.SaveCallback() {
		// public void done(com.avos.avoscloud.AVException e) {
		// if (e == null) {
		// // 保存成功
		// // String installationId =
		// com.avos.avoscloud.AVInstallation
		// .getCurrentInstallation()
		// .getInstallationId();
		// // 关联 installationId 到用户表等操作……
		// } else {
		// // 保存失败，输出错误信息
		// Debug.i("AVInstallation.getCurrentInstallation().saveInBackground fail,e="
		// + e.toString());
		// }
		// }
		// });
		// com.avos.avoscloud.PushService.setDefaultPushCallback(context, cls);
		// com.avos.avoscloud.PushService.subscribe(context, "public", cls);
		// } catch (Exception e) {
		// Debug.e("TBUCloud->initPush fail, e=" + e);
		// }
	}

	public static void markPersonInfo(Activity activity, String tag, String msg) {
		TbuCloud.markPersonInfo(activity, tag, msg);
	}

}
