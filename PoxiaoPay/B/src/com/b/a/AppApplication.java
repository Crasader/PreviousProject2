package com.b.a;

import java.lang.reflect.Method;

import android.app.Activity;
import android.app.Application;
import android.content.Context;

import com.b.a.base.IAppApplication;
import com.b.a.base.IGamePInterface;
import com.b.a.ioc.IocConfigUtil;
import com.b.a.ioc.IocInfos;
import com.d.event.EventCallBack;
import com.d.extend.quitgame.ExitGameInterface;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;


public class AppApplication extends Application {

	private static AppApplication instance;
	private static IAppApplication bApplication;
	private IGamePInterface gamePImpl;
	
	

	@Override
	public void onCreate() {
		super.onCreate();
		init(this);
	}

	public void init(Context context) {
		if (null == instance) {
			instance = this;
		}
		// 初始化整个TAT工具
		TbuAndroidTools.init(context);
		// 读取IOC初始化的必要信息
		IocConfigUtil.init(context);
		// 初始化IOC
		iocInit(context);
		
		
	}
	
	


	/**
	 * 通过反射注入接口的实现类
	 * 
	 * @param context
	 */
	private void iocInit(Context context) {
		try {
			Class c = Class.forName(IocInfos.getApplicationImpl());
			Object newInstance = c.newInstance();
			bApplication = (IAppApplication) newInstance;
			bApplication.init(context);
			Class c2 = Class.forName(IocInfos.getPayImplName());
			Method method = c2.getMethod(IocInfos.getPImplFunction());
			gamePImpl = (IGamePInterface) method.invoke(null);
		} catch (Exception e) {
			Debug.e(x.y.z.b("d0ZGd0ZGWl9VV0JfWVgWGxsIFl9ZVX9YX0IWCxY=") + e.toString());
		}
	}

	public static AppApplication getInstance() {
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
	 * 统一支出口,都从AppApplication中调用
	 * 
	 * @param activity
	 * @param eventId
	 * @param callback
	 * @return
	 */
	//设置开不开界面
	public boolean doPEvent(final Activity activity, final String eventId,final boolean isShowUi,
			final EventCallBack callback) {
		return bApplication.doPEvent(activity, eventId, isShowUi,callback);
	}
	
	//默认开界面
	public boolean doPEvent(final Activity activity, final String eventId,
			final EventCallBack callback) {
		return bApplication.doPEvent(activity, eventId, true,callback);
	}

	/**
	 * 融合工程初始化方法
	 * 
	 * @param activity
	 */
	public void initOnFirstActivity(final Activity activity) {
		gamePImpl.initOnFirstActivity(activity);
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
		bApplication.quitGame(activity, exitGameInterface);
		bApplication.doInstallOnQuit();
	}
}