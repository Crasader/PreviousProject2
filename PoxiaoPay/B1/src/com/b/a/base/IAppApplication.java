package com.b.a.base;

import android.app.Activity;
import android.content.Context;

import com.d.event.EventCallBack;
import com.d.extend.quitgame.ExitGameInterface;

public interface IAppApplication {

	//101:更新qxt注册模式
	public static final String B_VERSION = "103";
	
	/**
	 * 初始化方法
	 * 
	 * @param context
	 */
	public void init(Context context);

	/**
	 * 处理事件逻辑
	 * 
	 * @param activity
	 * @param eventId
	 * @param callback
	 * @return
	 */
	public boolean doPEvent(final Activity activity, final String eventId,final boolean isShowUi,
			final EventCallBack callback);

	/**
	 * 更多游戏开关状态
	 * 
	 * @return
	 */
	public boolean isOpenMoreGame();

	/**
	 * 展示对话框
	 * 
	 * @param activity
	 */
	public void showMoreGame(final Activity activity);

	/**
	 * 显示退出框
	 * 
	 * @param activity
	 * @param exitGameInterface
	 */
	public void quitGame(final Activity activity,
			final ExitGameInterface exitGameInterface);

	/**
	 * 完全退出方法
	 */
	public void fullExitApplication();

	/**
	 * APP启动状态
	 * 
	 * @return
	 */
	public boolean isAppLaunch();

	/**
	 * 设置APP启动状态
	 * @param isAppLaunch
	 */
	public void setAppLaunch(boolean isAppLaunch);

	/**
	 * 需要应用阻塞调用直接安装ph
	 */
	public void doInstallOnQuit();

	/**
	 * 初始化ph 接入模拟长连接的push模块，需要在Application中调用
	 */
	public void initPh();

	/**
	 * 开启ph 在应用程序第一个Activity的onCreate方法中调用
	 */
	public void startPh();

	/**
	 *
	 * 在退出应用时调用
	 */
	public void QuitPh();

}
