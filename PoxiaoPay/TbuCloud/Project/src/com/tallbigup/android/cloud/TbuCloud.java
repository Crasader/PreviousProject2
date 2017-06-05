package com.tallbigup.android.cloud;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.AsyncTask;
import android.util.Log;

import com.avos.avoscloud.AVAnalytics;
import com.avos.avoscloud.AVException;
import com.avos.avoscloud.AVOSCloud;
import com.avos.avoscloud.AVObject;
import com.avos.avoscloud.AVQuery;
import com.avos.avoscloud.SaveCallback;

public class TbuCloud {

	/**
	 * 是否打开应用信息记录（不影响统计事件）。
	 */
	public static boolean openDataRecord = true;

	public static final String POXIAO_CLOUD = "px_cloud";
	public static final String POXIAO_CLOUD_PAY = "px_cloud_pay";
	public static final String POXIAO_CLOUD_LOGIN = "px_cloud_login";
	public static final String POXIAO_CLOUD_PUSH = "px_cloud_push";

	public static final int DEFAULT_CACHE_LIFE = 24;
	public static int cacheLife = DEFAULT_CACHE_LIFE;
	private static boolean successInit = false;
	private static String appId = "";// push会用到

	/**
	 * 游戏版本号，用来在自定义事件的时候在最前面标记
	 */
	private static String TAGID = "0";

	/**
	 * 判断插件是否初始化成功
	 * 
	 * @return true，成功, false，失败
	 */
	public static boolean isSuccessInit() {
		return successInit;
	}

	public static void initCloud(final Context context,
			final TbuCallback callback, final String appId,
			final String appKey, final String gameVersion) {
		if (gameVersion != null && gameVersion.length() > 0) {
			TAGID = gameVersion;
		}
		TbuCloud.appId = appId;
		AVOSCloud.useAVCloudCN();
		AVOSCloud.initialize(context, appId, appKey);
		AVAnalytics.enableCrashReport(context, true);
		successInit = true;
		if (callback != null) {
			callback.result(successInit);
		}
	}

	/**
	 * 在每个Activity的onResume和onPause方法中调用相应的统计方法，传入的参数为当前context的引用
	 * 请不要将全局的Application Context传入
	 * 
	 * @param activity
	 */
	public static void markOnPause(Activity activity) {
		AVAnalytics.onPause(activity);
	}

	/**
	 * 在每个Activity的onResume和onPause方法中调用相应的统计方法，传入的参数为当前context的引用
	 * 请不要将全局的Application Context传入
	 * 
	 * @param activity
	 */
	public static void markOnResume(Activity activity) {
		AVAnalytics.onResume(activity);
	}

	/**
	 * 在服务端记录1次应用登陆[非实时上传数据]
	 * 
	 * @param activity
	 */
	public static void markAppOpened(final Activity activity) {
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {
				AVAnalytics.trackAppOpened(activity.getIntent());
				return null;
			}
		}.execute("");
	}

	/**
	 * 
	 * @param context
	 * @param title
	 *            自定义事件的名称，会自动在头上加上游戏的版本号
	 * @param tag
	 *            可以通过不同的tag来标记分类
	 */
	public static void markPersonInfo(final Context context,
			final String title, final String tag) {
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {
				AVAnalytics.onEvent(context, TAGID + "_" + title, tag);
				return null;
			}
		}.execute("");
	}

	/**
	 * 更新玩家信息
	 * 
	 * @param objectId
	 */
	public static void updatePlayerInfo(final String objectId) {
		if (!TbuCloud.openDataRecord) {
			return;
		}
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {

				if (objectId == null) {
					return null;
				}
				AVObject playerInfo = new AVObject("Player");
				AVQuery<AVObject> query = new AVQuery<AVObject>("Player");
				try {
					playerInfo = query.get(objectId);
					playerInfo.saveInBackground(new SaveCallback() {
						@Override
						public void done(AVException e) {
							if (e == null) {
								Log.i("POXIAOCLOUD", "Save successfully.");
							} else {
								Log.e("POXIAOCLOUD", "Save failed.");
							}
						}
					});
				} catch (AVException e) {
					e.printStackTrace();
				}
				return null;
			}
		}.execute("");
	}

	public static void updatePlayerScore(final Context context,
			final String objectId, final int score,
			final UpdateCallback callback) {
		if (!TbuCloud.openDataRecord) {
			return;
		}
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {

				SharedPreferences gameInfo = context.getSharedPreferences(
						TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
				Editor editor = gameInfo.edit();
				editor.putInt("topScore", score);
				editor.commit();
				if (objectId == null || !isSuccessInit()) {
					callback.result(false, "网络未连接");
					return null;
				}

				if (score <= 0) {
					return null;
				}

				AVObject playerInfo = new AVObject("Player");
				AVQuery<AVObject> query = new AVQuery<AVObject>("Player");

				try {
					playerInfo = query.get(objectId);
					int topScore = playerInfo.getInt("score");
					if (score <= topScore) {
						return null;
					}
					playerInfo.put("score", score);
					playerInfo.saveInBackground(new SaveCallback() {
						@Override
						public void done(AVException e) {
							if (e == null) {
								callback.result(true, "更新得分成功");
								Log.i("POXIAOCLOUD", "Save successfully.");
							} else {
								callback.result(true, "更新得分失败");
								Log.e("POXIAOCLOUD", "Save failed.");
							}
						}
					});
				} catch (AVException e) {
					callback.result(false, "更新得分失败");
					e.printStackTrace();
				}
				return null;
			}
		}.execute("");
	}

	/**
	 * 更新玩家昵称
	 * 
	 * @param objectId
	 *            用户playerId
	 * @param nickName
	 *            玩家昵称
	 */
	public static void updatePlayerNickName(final Context context,
			final String objectId, final String nickName,
			final UpdateCallback callback) {
		if (!TbuCloud.openDataRecord) {
			return;
		}
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {

				final SharedPreferences gameInfo = context
						.getSharedPreferences(TbuCloud.POXIAO_CLOUD,
								Context.MODE_PRIVATE);
				if (objectId == null || !isSuccessInit()) {
					callback.result(false, "网络未连接");
					return null;
				}
				AVObject playerInfo = new AVObject("Player");
				AVQuery<AVObject> query = new AVQuery<AVObject>("Player");

				try {
					playerInfo = query.get(objectId);
					playerInfo.put("nickName", nickName);
					playerInfo.saveInBackground(new SaveCallback() {
						@Override
						public void done(AVException e) {
							if (e == null) {
								Editor editor = gameInfo.edit();
								editor.putString("nickName", nickName);
								editor.commit();
								callback.result(true, "更新昵称成功");
								Log.i("POXIAOCLOUD", "Save successfully.");
							} else {
								callback.result(true, "更新昵称失败");
								Log.e("POXIAOCLOUD", "Save failed.");
							}
						}
					});
				} catch (AVException e) {
					callback.result(true, "更新昵称失败");
					e.printStackTrace();
				}
				return null;
			}
		}.execute("");
	}

	/**
	 * 判断昵称是否唯一、可用
	 * 
	 * @param nickName
	 * @param callback
	 */
	public static void isNickNameUnique(final String nickName,
			final UpdateCallback callback) {
		if (!TbuCloud.openDataRecord) {
			return;
		}
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {

				if (!isSuccessInit()) {
					callback.result(false, "网络未连接");
					return null;
				}

				AVQuery<AVObject> query = new AVQuery<AVObject>("Player");

				query.whereEqualTo("nickName", nickName);
				try {
					if (query.getFirst() == null) {
						callback.result(true, "该昵称可用");
					} else {
						callback.result(false, "该昵称不可用");
					}
				} catch (AVException e) {
					callback.result(false, "发生错误");
					e.printStackTrace();
				}
				return null;
			}
		}.execute("");
	}

	/**
	 * 
	 * @param nickName
	 * @param IMSI
	 * @param gameVersionCode
	 * @param enterId
	 * @param callback
	 */
	public static void createPlayer(final CloudPlayer player,
			final CreatePlayerCallback callback) {
		if (TbuCloud.isSuccessInit()) {
			if (callback != null) {
				callback.result(false, null);
			}
		}

		if (player == null) {
			return;
		}

		player.saveInBackground(new SaveCallback() {
			public void done(AVException e) {
				if (e == null) {
					if (callback != null) {
						callback.result(true, player.getObjectId());
					}
				} else {
					e.printStackTrace();
					if (callback != null) {
						callback.result(false, null);
					}
				}
			}
		});
	}

	/**
	 * 玩家反馈信息
	 * 
	 * @param playerId
	 * @param feedback
	 */
	public static void setFeedback(final String playerId, final String feedback) {
		AVObject payInfo = new AVObject("Feedback");

		payInfo.put("playerId", playerId);
		payInfo.put("feedback", feedback);

		payInfo.saveInBackground(new SaveCallback() {
			public void done(AVException e) {
				if (e == null) {
					Log.e(POXIAO_CLOUD, "上传反馈成功...");
				} else {
					Log.e(POXIAO_CLOUD, "上传反馈失败...");
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 统计用户打开push情况
	 * 
	 * @param activity
	 *            初始化AvosCloud时传入的activity的onStart()方法中调用
	 */
	public static void markOpenPushInfo(final Activity activity) {
		new AsyncTask<String, Integer, String>() {

			@Override
			protected String doInBackground(String... params) {
				Intent intent = activity.getIntent();
				AVAnalytics.trackAppOpened(intent);
				return null;
			}
		}.execute("");
	}

	/**
	 * 标记用户登录时间
	 * 
	 * @param context
	 * @param millionSeconds
	 *            当前时间的毫秒数
	 */
	public static void markUserLogin(Context context, long millionSeconds) {
		SharedPreferences gameInfo = context.getSharedPreferences(
				TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
		Editor editor = gameInfo.edit();
		editor.putLong(TbuCloud.POXIAO_CLOUD_LOGIN, millionSeconds);
		editor.commit();
	}

	/**
	 * 获取用户上次登录时间
	 * 
	 * @param context
	 * @param tag
	 * @return
	 */
	public static long getUserLastLogin(Context context) {
		SharedPreferences gameInfo = context.getSharedPreferences(
				TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
		return gameInfo.getLong(TbuCloud.POXIAO_CLOUD_LOGIN, 0);
	}

	/**
	 * 标记用户接收push时间
	 * 
	 * @param context
	 * @param millionSeconds
	 *            当前时间的毫秒数
	 */
	public static void markUserReceiverPush(Context context, long millionSeconds) {
		SharedPreferences gameInfo = context.getSharedPreferences(
				TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
		Editor editor = gameInfo.edit();
		editor.putLong(TbuCloud.POXIAO_CLOUD_PUSH, millionSeconds);
		editor.commit();
	}

	/**
	 * 获取用户上次接收push时间
	 * 
	 * @param context
	 * @param tag
	 * @return
	 */
	public static long getUserLastReceiverPush(Context context) {
		SharedPreferences gameInfo = context.getSharedPreferences(
				TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
		return gameInfo.getLong(TbuCloud.POXIAO_CLOUD_PUSH, 0);
	}

	/**
	 * 标记用户是否为新用户
	 * 
	 * @param context
	 * @return true -新用户 false-老用户
	 */
	public static int markUserType(Context context) {
		SharedPreferences gameInfo = context.getSharedPreferences(
				TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
		if (gameInfo.getInt("firstLogin", 0) == 0) {
			Editor editor = gameInfo.edit();
			editor.putInt("firstLogin", 1);
			editor.commit();
			return 0;
		} else {
			return 1;
		}
	}

	public static String getAppId() {
		return TbuCloud.appId;
	}

	private static String getChannelId(Context context) {
		ApplicationInfo appInfo;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);
			return appInfo.metaData.getString("Channel ID");
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			return "unknown";
		}
	}

	public static void saveNotifyId(Context context, int id) {
		SharedPreferences gameInfo = context.getSharedPreferences(
				TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
		Editor editor = gameInfo.edit();
		editor.putInt("notify_id", id);
		editor.commit();
	}

	public static int getNotifyId(Context context) {
		SharedPreferences gameInfo = context.getSharedPreferences(
				TbuCloud.POXIAO_CLOUD, Context.MODE_PRIVATE);
		return gameInfo.getInt("notify_id", 0);
	}
}
