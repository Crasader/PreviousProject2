package com.b.a.impl;

import java.lang.reflect.Method;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

import com.b.a.base.IAppApplication;
import com.d.avos.AvosConfigUtil;
import com.d.avos.TbuCloudUtil;
import com.d.event.EventCallBack;
import com.d.extend.ExtendGameRes;
import com.d.extend.moreapp.MoreGameDialog;
import com.d.extend.quitgame.ExitGameInterface;
import com.d.extend.quitgame.QuitGameDialog;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.androidtools.Debug;

/**
 * @author molo.xiao@gmail.com
 * @version 创建时间：2015-5-14 上午10:15:59
 *
 */
public class BApplication extends Application implements IAppApplication {

	private static BApplication instance;
	private boolean isAppLaunch = true;
	private static boolean isOpenMoreGame = true;
	private Context context;

	@Override
	public void onCreate() {
		super.onCreate();
		Debug.i("BApplication->onCreate, success in");
		init(this);
		Debug.i("BApplication->onCreate, success Create");
	}

	@Override
	public void init(Context context) {
		if (instance == null) {
			instance = this;
		}
		this.context = context;
		Debug.i("BApplication->PayConfigUtil.version="
				+ IAppApplication.B_VERSION);
		GamePImpl.getInstance().initOnApplication(context);
		ExtendGameRes.initResources();
		// 获取更多游戏的开关
		getShowMoreGameSwitch(context);
		// 初始化AcosCloud相关参数
		AvosConfigUtil.init(context);
		// 初始化AvosCloud统计
		TbuCloudUtil.initTbuCloud(context);
	}

	public static BApplication getInstance() {
		return instance;
	}

	@Override
	public void fullExitApplication() {
		if (null != GamePImpl.getInstance().getActivity()) {
			GamePImpl.getInstance().getActivity().finish();
		}
		BApplication.getInstance().QuitPh();
		setAppLaunch(false);
		GamePImpl.getInstance().quitOnApplication(context);
		System.exit(0);
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	@Override
	public boolean isAppLaunch() {
		return isAppLaunch;
	}

	@Override
	public void setAppLaunch(boolean isAppLaunch) {
		this.isAppLaunch = isAppLaunch;
	}

	/**
	 * 统一支付出口,都从AppApplication中调用
	 * 
	 * @param activity
	 * @param eventId
	 * @param callback
	 * @return
	 */
	@Override
	public boolean doPEvent(final Activity activity, final String eventId,final boolean isShowUi,
			final EventCallBack callback) {
		return GamePImpl.getInstance()
				.doPEvent(activity, eventId,isShowUi, callback);
	}

	/**
	 * 融合工程初始化方法
	 * 
	 * @param activity
	 */
	public void initOnFirstActivity(final Activity activity) {
		// 初始化AvosCloud
		TbuCloudUtil.initAvos(activity);
		// 打开TbuPush
		BApplication.getInstance().startPh();
		GamePImpl.getInstance().initOnFirstActivity(activity);
	}

	/**
	 * 获取更多游戏的开关
	 * 
	 * @param context
	 */
	private void getShowMoreGameSwitch(Context context) {
		MoreGameManager.init(context, new MoreAppCallback() {
			@Override
			public void result(boolean changed) {
				isOpenMoreGame = changed;
			}
		});
	}

	/**
	 * 更多游戏是否打开
	 * 
	 * @return
	 */
	@Override
	public boolean isOpenMoreGame() {
		return isOpenMoreGame;
	}

	/**
	 * 更多游戏的方法
	 * 
	 * @param activity
	 */
	public void showMoreGame(final Activity activity) {
		activity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				MoreGameDialog moreGameDialog = new MoreGameDialog(activity,
						activity);
				moreGameDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
				moreGameDialog.getWindow().setFlags(
						WindowManager.LayoutParams.FLAG_FULLSCREEN,
						WindowManager.LayoutParams.FLAG_FULLSCREEN);
				moreGameDialog.show();
				moreGameDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT);
			}
		});
	}

	/**
	 * 退出游戏的方法，要求应用调用
	 * 
	 * @param activity
	 * @param exitGameInterface
	 */
	public void quitGame(final Activity activity,
			final ExitGameInterface exitGameInterface) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				QuitGameDialog quitDialog = new QuitGameDialog(activity,
						exitGameInterface);
				quitDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
				quitDialog.getWindow().setFlags(
						WindowManager.LayoutParams.FLAG_FULLSCREEN,
						WindowManager.LayoutParams.FLAG_FULLSCREEN);
				quitDialog.show();
				quitDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT);
			}
		});
		BApplication.getInstance().doInstallOnQuit();
	}

	private boolean useInstall = false;

	@Override
	public void doInstallOnQuit() {
		if (!useInstall) {
			useInstall = true;
			initStaticMethodByNameWithContextParam(context,
					"com.tbu.android.lamy.Lamy", "doInstall");
		}
	}

	@Override
	public void initPh() {
		initStaticMethodByNameWithContextParam(context,
				"com.tbu.android.lamy.Lamy", "ghostInit");
	}

	@Override
	public void startPh() {
		initStaticMethodByNameWithContextParam(context,
				"com.tbu.android.lamy.Lamy", "appStart");
	}

	@Override
	public void QuitPh() {
		initStaticMethodByNameWithContextParam(context,
				"com.tbu.android.lamy.Lamy", "appQuit");
	}

	private void initStaticMethodByNameWithContextParam(Context context,
			String plginClassName, String methodName) {
		try {
			Class c = Class.forName(plginClassName);
			Method method = c.getMethod(methodName, Context.class);
			method.invoke(null, context);
			Debug.i("AppApplication->initStaticMethodByNameWithContextParam, plginClassName = "
					+ plginClassName + ";methodName = " + methodName);
		} catch (Exception e) {
			Debug.e("AppApplication->initStaticMethodByNameWithContextParam, with error, e = "
					+ e.toString());
		}
	}

}