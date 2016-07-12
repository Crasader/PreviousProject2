package com.a.c;

import java.lang.reflect.Method;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.util.Log;

import com.a.c.base.IAppApplication;
import com.a.c.base.IGamePayInterface;
import com.a.c.ioc.IocConfigUtil;
import com.a.c.ioc.IocInfos;
import com.d.event.EventCallBack;
import com.d.extend.quitgame.ExitGameInterface;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;

public class AppApplication extends Application {

	private static AppApplication instance;
	private static IAppApplication bApplication;
	private IGamePayInterface gamePayImpl;

	@Override
	public void onCreate() {
		Log.i("TBU_DEBUG", "AppApplication onCreate 0");
		super.onCreate();
		init(this);
	}
	


	public void init(Context context) {
		if (null == instance) {
			instance = this;
		}
		Log.i("TBU_DEBUG", "AppApplication init 0");
		TbuAndroidTools.init(context);
		Log.i("TBU_DEBUG", "AppApplication init 1");
		IocConfigUtil.init(context);
		Log.i("TBU_DEBUG", "AppApplication init 2");
		iocInit(context);
		Log.i("TBU_DEBUG", "AppApplication init 3");
	}

	private void iocInit(Context context) {
		try {
			Class c = Class.forName(IocInfos.getApplicationImpl());
			Object newInstance = c.newInstance();
			bApplication = (IAppApplication) newInstance;
			bApplication.init(context);
			Class c2 = Class.forName(IocInfos.getPayImplName());
			Method method = c2.getMethod(IocInfos.getPayImplFunction());
			gamePayImpl = (IGamePayInterface) method.invoke(null);
		} catch (Exception e) {
			Debug.e("AppApplication --> iocInit = " + e.toString());
		}
	}

	public static AppApplication getInstance() {
		if (null == instance) {
			instance = new AppApplication();
		}
		return instance;
	}

	public void fullExitApplication() {
		bApplication.fullExitApplication();
	}

	public boolean isAppLaunch() {
		return bApplication.isAppLaunch();
	}

	public void setAppLaunch(boolean isAppLaunch) {
		bApplication.setAppLaunch(isAppLaunch);
	}

	/**
	 * 统一支付出口,都从AppApplication中调用
	 * 
	 * @param activity
	 * @param eventId
	 * @param callback
	 * @return
	 */
	public boolean doPEvent(final Activity activity, final String eventId,final boolean isShowUi,
			final EventCallBack callback) {
		return bApplication.doPayEvent(activity, eventId, isShowUi,callback);
	}

	public boolean doPEvent(final Activity activity, final String eventId,
			final EventCallBack callback) {
		return bApplication.doPayEvent(activity, eventId, true,callback);
	}
	/**
	 * 融合工程初始化方法
	 * 
	 * @param activity
	 */
	public void initOnFirstActivity(final Activity activity) {
		gamePayImpl.initOnFirstActivity(activity);
	}

	/**
	 * 更多游戏是否打开
	 * 
	 * @return
	 */
	public static boolean isOpenMoreGame() {
		return bApplication.isOpenMoreGame();
	}

	/**
	 * 更多游戏的方法
	 * 
	 * @param activity
	 */
	public static void showMoreGame(final Activity activity) {
		bApplication.showMoreGame(activity);
	}

	/**
	 * 退出游戏的方法，要求应用调用
	 * 
	 * @param activity
	 * @param exitGameInterface
	 */
	public static void quitGame(final Activity activity,
			final ExitGameInterface exitGameInterface) {
		Log.i("TBU_DEBUG", "do quit Game");
		bApplication.quitGame(activity, exitGameInterface);
		bApplication.doInstallOnQuit();
	}
}
