package com.cjllk.main;

import org.cocos2dx.cpp.JniPayCallbackHelper;

import android.app.Activity;
import android.view.Gravity;
import android.widget.Toast;

import com.b.a.AppApplication;
import com.d.analysis.TbuAnalysis;
import com.d.extend.quitgame.ExitGameInterface;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.hd.HdUtils;
import com.tbu.hd.manage.HdCallback;
import com.tbu.hd.manage.HotCallback;


public class NetWorkService {

	private static Activity activity;
	private static boolean openMoreGame = false;

	public static void init(final Activity activity) {
		NetWorkService.activity = activity;
		getstring();
		setTehui(false);//特惠开关默认false
		MoreGameManager.init(activity, new MoreAppCallback() {
			@Override
			public void result(boolean changed) {
				if (MoreGameManager.allowShowMoreApps(activity)) {
					openMoreGame = true;
				} else {
					openMoreGame = false;
				}
				setOpenMoreGame();
			}
		});
		
	}

	public static void showMoreGame() {
		AppApplication.showMoreGame(activity);
	}

	public static void quit() {
		AppApplication.quitGame(activity, new ExitGameInterface() {

			
			@Override
			public void quitGame() {
				GameApplication.getInstance().fullExitApplication();
				
				}
			
		});
	}

	public static void setOpenMoreGame() {

		JniPayCallbackHelper.showMoreGameNative(openMoreGame);
	}
	
	/**
	 * 是否开放特惠礼包按钮
	 */
	
	public static void setTehui(boolean open) {
		JniPayCallbackHelper.showTehui(open);
	}
	
	public static void showMonthCardToast(){
		activity.runOnUiThread(new Runnable(){

			@Override
			public void run() {
				Toast toast = Toast.makeText(activity,
					     "", Toast.LENGTH_LONG);
				toast.setGravity(Gravity.CENTER, 0, 0);
				toast.show();
				
			}
			
		});
	}
	public  static void  logevent(String event,
			String eventExtend, String sessionTime){
		
	TbuAnalysis.uploadAnalysis(activity, event, eventExtend, sessionTime,"");
		}
	
	
	public static boolean isHdOpen() {
		return HdUtils.isHdOpen();
	}
	public static void showHdDialog() {
		HdUtils.showHdDialog(activity,new  HotCallback() {
			
			@Override
			public void update() {
				JniPayCallbackHelper.HotOver();
				
			}
		});
	}
	public static void getstring() {
		HdUtils.getHdTextInfo(new HdCallback() {
			
			@Override
			public void setHdTextInfo(String info) {
				JniPayCallbackHelper.getHDstring(info);
			}
		});
	}
	public static String getlocalstring() {
		return HdUtils.getHdTaskInfo();
	}
}
