package com.tbu.hd;

import android.app.Activity;
import android.content.Context;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

import com.tbu.hd.dialog.HdDialog;
import com.tbu.hd.dialog.HdDialogRes;
import com.tbu.hd.manage.HdCallback;
import com.tbu.hd.manage.HdConfig;
import com.tbu.hd.manage.HdHttpTools;
import com.tbu.hd.manage.HotCallback;

/**
 * 
 * @author QZ
 *
 */
public class HdUtils {

	public static void init(Context context, int styleId, int layoutId,
			int confirmId, int cancelId, int textId) {
		HdConfig.init(context);
		HdDialogRes.setHdDialogStyleResId(styleId);
		HdDialogRes.setHdDialogLayoutResId(layoutId);
		HdDialogRes.setHdDialogConfirmResId(confirmId);
		HdDialogRes.setHdDialogCancelResId(cancelId);
		HdDialogRes.setHdDialogTextResId(textId);
	}

	/**
	 * 开关状态，从配置文件里读取
	 * 
	 * @return
	 */
	public static boolean isHdOpen() {
		return HdConfig.isHdOpen();
	}

	/**
	 * 返回任务信息
	 * 
	 * @return
	 */
	public static String getHdTaskInfo() {
		return HdConfig.getHdContent();
	}

	/**
	 * 从服务端获取信息
	 * 
	 * @param callback
	 */
	public static void getHdTextInfo(final HdCallback callback) {
		Thread thread = new Thread() {
			@Override
			public void run() {
				HdHttpTools.doGet(new HdCallback() {
					@Override
					public void setHdTextInfo(String info) {
						callback.setHdTextInfo(info);
					}
				});
			}
		};
		thread.setDaemon(true);
		thread.start();
	}

	/**
	 * 上传信息给服务端
	 * 
	 * @param phoneNumber
	 * @param msg
	 */
	public static void uploadHdInfo(final String phoneNumber, final String msg) {
		Thread thread = new Thread() {
			@Override
			public void run() {
				String info = HdHttpTools.createUploadInfo(phoneNumber, msg);
				HdHttpTools.doPost(info);
			}
		};
		thread.setDaemon(true);
		thread.start();
	}

	/**
	 * 显示dialog框
	 * 
	 * @param activity
	 */
	public static void showHdDialog(final Activity activity,
			final HotCallback hotCallback) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				HdDialog hotDialog = new HdDialog(activity,hotCallback);
				hotDialog.getWindow().setFlags(
						WindowManager.LayoutParams.FLAG_FULLSCREEN,
						WindowManager.LayoutParams.FLAG_FULLSCREEN);
				hotDialog.show();
				hotDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT);
			}
		});
	}

}
