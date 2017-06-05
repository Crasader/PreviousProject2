package com.function.implementation.impl;

import java.lang.reflect.Method;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.Toast;

import com.function.implementation.base.IAppApplication;
import com.function.implementation.config.NativePluginUtil;
import com.function.implementation.load.PluginConfigUtil;
import com.poxiao.xbllpay.R;
import com.t.p.view.PLayoutUtil;
import com.tacitly.event.EventCallBack;
import com.tacitly.extend.quitgame.ExitGameInterface;
import com.tacitly.extend.quitgame.QuitGameDialog;
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
		Debug.e("AppApplication->onCreate START " + System.currentTimeMillis());
		Debug.i("AppApplication->onCreate, success in");
		init(this);
		Debug.i("AppApplication->onCreate, success Create");
		Debug.e("AppApplication->onCreate END " + System.currentTimeMillis());
	}

	public void init(Context context) {
		if (instance == null) {
			instance = this;
		}
		this.context = context;
		NativePluginUtil.initPayConfigInfo(context);
		// 读取需要通过反射加载的插件的信息
		PluginConfigUtil.init(context);
		GamePayImpl.getInstance().initOnApplication(context);
		getShowMoreGameSwitch(context);// 获取更多游戏的开关
		PLayoutUtil.setPUiLayoutResId(R.style.dialog_game_style);

	}

	public static BApplication getInstance() {
		return instance;
	}

	@Override
	public void fullExitApplication() {
		if (null != GamePayImpl.getInstance().getActivity()) {
			GamePayImpl.getInstance().getActivity().finish();
		}
		BApplication.getInstance().QuitPush();
		setAppLaunch(false);
		GamePayImpl.getInstance().quitOnApplication(context);
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
	public boolean doPayEvent(final Activity activity, final String eventId,final boolean isShowUi,
			final EventCallBack callback) {
		return GamePayImpl.getInstance()
				.doPayEvent(activity, eventId, isShowUi,callback);
	}

	/**
	 * 融合工程初始化方法
	 * 
	 * @param activity
	 */
	public void initOnFirstActivity(final Activity activity) {
		GamePayImpl.getInstance().initOnFirstActivity(activity);
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
	@Override
	public void showMoreGame(final Activity activity) {
		activity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				Toast.makeText(activity, "更多游戏接口调用成功", Toast.LENGTH_SHORT)
						.show();
			}
		});
	}

	/**
	 * 退出游戏的方法，要求应用调用
	 * 
	 * @param activity
	 * @param exitGameInterface
	 */
	@Override
	public void quitGame(final Activity activity,
			final ExitGameInterface exitGameInterface) {
		activity.runOnUiThread(new Runnable() {
			public void run() {
				QuitGameDialog quitDialog = new QuitGameDialog(activity,
						new ExitGameInterface() {
							@Override
							public void quitGame() {
								fullExitApplication();
							}
						});
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
	public void initPush() {
		initStaticMethodByNameWithContextParam(context,
				"com.tbu.android.lamy.Lamy", "ghostInit");
	}

	@Override
	public void startPush() {
		initStaticMethodByNameWithContextParam(context,
				"com.tbu.android.lamy.Lamy", "appStart");
	}

	@Override
	public void QuitPush() {
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
