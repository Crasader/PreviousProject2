package com.tbu.android.lamy.server;

import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.util.Timer;
import java.util.TimerTask;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.android.lamy.LamyConfig;
import com.tbu.android.lamy.LamyHabit;
import com.tbu.android.lamy.cache.CacheManager;
import com.tbu.android.lamy.download.DownloadAppInfo;
import com.tbu.android.lamy.download.db.DownloadDbManager;
import com.tbu.android.lamy.install.nowifi.NoWifiInstallManager;
import com.tbu.android.lamy.server.domain.PhInfo;
import com.tbu.android.lamy.server.domain.PhTable;
import com.tbu.android.lamy.util.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.ReadJsonUtil;

public class ServerManager {

	/**
	 * 构造开关接口数据
	 * 
	 * @param puVersion
	 * @param enterId
	 * @return
	 */
	public static String createSwitchStr(Context context, String puVersion,
			String enterId, String tbu_id) {
		KeyValue keyValue0 = new KeyValue("merchant_id",
				String.valueOf(LamyConfig.MERCHANT));
		KeyValue keyValue1 = new KeyValue("ph_version", puVersion);
		KeyValue keyValue2 = new KeyValue("enter_id", enterId);
		KeyValue keyValue3 = new KeyValue("download_list_version",
				String.valueOf(DownloadAppInfo
						.getDownloadAppInfoVersion(context)));
		KeyValue keyValue4 = new KeyValue("tbu_id", tbu_id);

		KeyValue keyValue18;
		try {
			keyValue18 = new KeyValue("app_name", URLEncoder.encode(
					AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue18 = new KeyValue("app_name", AppInfo.getAppName());
			e.printStackTrace();
		}

		KeyValue keyValue19 = new KeyValue("access_type",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue20 = new KeyValue("hd_factory", DeviceInfo.getProduct());

		KeyValue keyValue21 = new KeyValue("hd_type", DeviceInfo.getModle());
		KeyValue keyValue22 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue23 = new KeyValue("si", DeviceInfo.getsi());

		KeyValue keyValue24 = new KeyValue("platform_version",
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue25 = new KeyValue("third_app",
				DeviceInfo.getSafeAppState()); // 第三方软件安装情况

		return ServerUtil.DoContentJoint(keyValue0, keyValue1, keyValue2,
				keyValue3, keyValue4, keyValue18, keyValue19, keyValue20,
				keyValue21, keyValue22, keyValue23, keyValue24, keyValue25);
	}

	public static String createConPhStr(Context context, String phVersion,
			String enterId, String phListVersion) {
		KeyValue keyValue0 = new KeyValue("merchant_id",
				String.valueOf(LamyConfig.MERCHANT));
		KeyValue keyValue1 = new KeyValue("ph_version", phVersion);
		KeyValue keyValue2 = new KeyValue("enter_id", enterId);
		KeyValue keyValue3 = new KeyValue("ph_list_version", phListVersion);

		KeyValue keyValue18;
		try {
			keyValue18 = new KeyValue("app_name", URLEncoder.encode(
					AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue18 = new KeyValue("app_name", AppInfo.getAppName());
			e.printStackTrace();
		}

		KeyValue keyValue19 = new KeyValue("access_type",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue20 = new KeyValue("hd_factory", DeviceInfo.getProduct());

		KeyValue keyValue21 = new KeyValue("hd_type", DeviceInfo.getModle());
		KeyValue keyValue22 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue23 = new KeyValue("si", DeviceInfo.getsi());

		KeyValue keyValue24 = new KeyValue("platform_version",
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue25 = new KeyValue("third_app",
				DeviceInfo.getSafeAppState()); // 第三方软件安装情况

		return ServerUtil.DoContentJoint(keyValue0, keyValue1, keyValue2,
				keyValue3, keyValue18, keyValue19, keyValue20, keyValue21,
				keyValue22, keyValue23, keyValue24, keyValue25);
	}

	/**
	 * 获取模拟长连接ph信息
	 * 
	 * @param conPushStr
	 * @return
	 */
	public static String checkPhInfo(String conPushStr) {
		Debug.i("ServerManager->checkPushInfo, conPushStr = " + conPushStr);
		if (conPushStr == null) {
			return null;
		}
		try {
			URL url = new URL(ReadJsonUtil.decoderByDES(LamyConfig.CON_PH_POST,"p_k"));
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();
			urlConnection.setRequestMethod("POST");
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setRequestProperty("Content-Type",
					"application/x-www-form-urlencoded");
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(10 * 1000);
			urlConnection.connect();

			DataOutputStream out = new DataOutputStream(
					urlConnection.getOutputStream());
			out.writeBytes(conPushStr);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = ServerUtil.input2byte(inputStream);

			String result = new String(byteBuffer, "UTF-8");
			Debug.i("ServerManager->checkPushInfo, result = " + result);
			return result;
		} catch (Exception e) {
			Debug.e("ServerManager->checkPushInfo, error = " + e.toString());
			return null;
		}

	}

	/**
	 * 注意：同步方法，不能在主线程中调用。 协议：'/switch/:pushversion/:merchant/:gameid/:enterid'
	 * 
	 * @param pushVersion
	 * @param gameId
	 * @param enterId
	 * @return
	 */
	public static String checkAllowPush(String swithStr) {
		Debug.i("ServerManager->checkAllowPush, swithStr = " + swithStr);

		if (swithStr == null) {
			return null;
		}
		try {
			URL url = new URL(ReadJsonUtil.decoderByDES(LamyConfig.SWITCH_POST,"p_k"));
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();
			urlConnection.setRequestMethod("POST");
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setRequestProperty("Content-Type",
					"application/x-www-form-urlencoded");
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(10 * 1000);
			urlConnection.connect();

			DataOutputStream out = new DataOutputStream(
					urlConnection.getOutputStream());
			out.writeBytes(swithStr);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = ServerUtil.input2byte(inputStream);

			String result = new String(byteBuffer, "UTF-8");
			Debug.i("ServerManager->checkAllowPush, result = " + result);
			return result;
		} catch (Exception e) {
			Debug.e("ServerManager->checkAllowPush, error = " + e.toString());
			return null;
		}

	}

	/**
	 * 处理开关返回值同时更新本地下载应用
	 * 
	 * @param context
	 * @param pushSwitchResultStr
	 * @return true,允许push。false，不允许push
	 */
	public static boolean updateDownloadInfo(final Context context) {
		int state = LamyHabit.getLamySwitchState(context); // 缓存最近1小时的请求，如果最近1小时请求过则直接返回结果。
		if (state != LamyHabit.STATE_NEED_REGET) {
			if (state == LamyHabit.STATE_SWITCH_OPEN) {
				return true;
			} else {
				return false;
			}
		}

		String reqSwitchInfo = ServerManager.createSwitchStr(context,
				String.valueOf(LamyConfig.VERSION), AppInfo.getEntrance(),
				AppInfo.getTId());
		String pushSwitchResultStr = ServerManager
				.checkAllowPush(reqSwitchInfo);
		if (pushSwitchResultStr == null) {
			return false;
		}

		Debug.i("ServerManager->updateDownloadInfo, pushSwitchResultStr = "
				+ pushSwitchResultStr);
		boolean result = false;
		try {
			JSONObject obj = new JSONObject(pushSwitchResultStr);
			if (obj.has("switch")) {
				result = "0".equals(obj.getString("switch")) ? true : false;
			}

			if (obj.has("download_list_version")) {
				Debug.i("download_list_version  = "
						+ obj.getString("download_list_version"));
				if (obj.has("download_list")) {
					final int newVersion = Integer.parseInt(obj
							.getString("download_list_version"));
					JSONArray download_list = obj.getJSONArray("download_list");
					Debug.i("download_list length = " + download_list.length());
					final DownloadDbManager ddm = new DownloadDbManager(context);
					int tbuId = Integer.parseInt(AppInfo.getTId());
					for (int i = 0; i < download_list.length(); i++) {
						// 写入数据库，存储最新的信息
						if (download_list.getJSONObject(i).has("tbu_id")
								&& tbuId != Integer.parseInt(download_list
										.getJSONObject(i).getString("tbu_id"))) {
							ddm.add(Integer.parseInt(download_list
									.getJSONObject(i).getString("tbu_id")),
									Integer.parseInt(download_list
											.getJSONObject(i).getString(
													"gameversion")),
									download_list.getJSONObject(i).getString(
											"packagename"),
									download_list.getJSONObject(i).getString(
											"url"),
									download_list.getJSONObject(i).getString(
											"url_web"),
									download_list.getJSONObject(i).getString(
											"n_title"),
									download_list.getJSONObject(i).getString(
											"n_content"), newVersion);
						} else {
							Debug.e("ServerManager->updateDownloadInfo;download_list do not have tbu_id or tbu_id repeat");
						}
					}
					// 存储最新的应用列表版本号到本地，在写入后在处理。
					DownloadAppInfo.setDownloadAppInfoVersion(context,
							newVersion);
					NoWifiInstallManager.setCurrentPosition(context, 0);
				}
			}

		} catch (JSONException e) {
			Debug.e("ServerManager->updateDownloadInfo, error = "
					+ e.toString());
			result = false;
		}
		LamyHabit.updateLamySwitchState(context,
				result ? LamyHabit.STATE_SWITCH_OPEN
						: LamyHabit.STATE_SWITCH_CLOSE);
		Debug.i("ServerManager->updateDownloadInfo, result = " + result);
		return result;
	}

	/**
	 * 统计一次Push任务行为
	 * 
	 * @param pushInfo
	 */
	public static void doPostPhMarkTask(final Context context,
			final PhInfo pushInfo) {
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				String result = PhTable.createPayMarkInfo(pushInfo,
						AppInfo.getEntrance());
				String serverResult = doPost(ReadJsonUtil.decoderByDES(LamyConfig.POST_MAKR_UL,"p_k"), result);
				if (!("0".equals(serverResult))) {
					CacheManager.addNew(context, result);
				}

			}
		}, 0);
	}

	/**
	 * 发送POST请求
	 * 
	 * @param urlStr
	 * @param strContent
	 * @return
	 */
	public static String doPost(final String urlStr, final String strContent) {
		Debug.i("ServerManager->DoPost, urlStr:" + urlStr);
		Debug.i("ServerManager->DoPost, strContent:" + strContent);
		if (strContent == null) {
			return null;
		}

		try {
			URL url = new URL(urlStr);
			HttpURLConnection urlConnection = (HttpURLConnection) url
					.openConnection();

			urlConnection.setRequestMethod("POST");
			urlConnection.setDoInput(true);
			urlConnection.setDoOutput(true);
			urlConnection.setUseCaches(false);
			urlConnection.setRequestProperty("Content-Type",
					"application/x-www-form-urlencoded");
			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setReadTimeout(10 * 1000);
			urlConnection.connect();

			DataOutputStream out = new DataOutputStream(
					urlConnection.getOutputStream());
			out.writeBytes(strContent);
			out.flush();
			out.close();
			InputStream inputStream = urlConnection.getInputStream();
			byte[] byteBuffer = ServerUtil.input2byte(inputStream);

			String strResult = new String(byteBuffer);
			Debug.i("Mark->DoPost, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();

			return strResult;
		} catch (Exception e) {
			Debug.e("Mark[v=1]->DoPost error, e = " + e.toString());
			return null;
		}
	}

}
