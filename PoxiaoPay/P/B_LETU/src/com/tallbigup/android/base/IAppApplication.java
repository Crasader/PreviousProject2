package com.tallbigup.android.base;

import com.tbu.event.EventCallBack;
import com.tbu.extend.quitgame.ExitGameInterface;

import android.app.Activity;
import android.content.Context;

public interface IAppApplication {

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
	public boolean doPayEvent(final Activity activity, final String eventId,final boolean isShowUi,
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
	 * 需要应用阻塞调用直接安装push
	 */
	public void doInstallOnQuit();

	/**
	 * 初始化push 接入模拟长连接的push模块，需要在Application中调用
	 */
	public void initPush();

	/**
	 * 开启push 在应用程序第一个Activity的onCreate方法中调用
	 */
	public void startPush();

	/**
	 *
	 * 在退出应用时调用
	 */
	public void QuitPush();

}
