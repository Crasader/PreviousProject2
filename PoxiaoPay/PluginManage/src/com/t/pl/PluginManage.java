package com.t.pl;

import java.util.Map;

import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;

import com.t.bfft.Buffett;
import com.t.bfft.PInterface;
import com.t.pl.config.NativePluginUtil;
import com.t.pl.http.RespObject;
import com.t.pl.http.SwitchCallback;
import com.t.pl.http.TbuPHttpClient;
import com.t.pl.init.InitPlugin;
import com.t.pl.load.PluginConfigUtil;
import com.t.pl.load.PluginInfos;
import com.t.pl.util.PluginFilter;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;

public class PluginManage {

	private static PluginManage instance;

	private static int pluginIndex = 0;// 当前使用的插件顺序

	private static boolean successInit = false;// 当前插件是否设置成功

	private String[] pluginSequence;// 保存从服务端获取的插件序列

	private static final String GET_INFO_SUCCCESS = "0";// 获取信息成功

	private static final String DEFAULTPLUGIN = "defaultPlugin";
	private static final String DEFAULT_SEQUENCE = "default_sequence";

	private static boolean secondConfirm = false;// 本地默认不起

	private static Activity activity;

	private RespObject respObject;

	public static PluginManage getInstance() {
		if (null == instance) {
			instance = new PluginManage();
		}
		return instance;
	}

	private PluginManage() {

	}

	/**
	 * 必须调用
	 * 
	 * @param activity
	 */
	public void initOnApplication(Context context) {
		NativePluginUtil.initPConfigInfo(context);
		PluginConfigUtil.init(context);
		InitPlugin.initPPlginIfNeedOnApplication(context);
	}

	/**
	 * 必须调用
	 * 
	 * @param activity
	 */
	public void initOnFirstAcrivity(Activity activity) {
		PluginManage.activity = activity;
		InitPlugin.initPPlginIfNeedOnActivity(activity);
		pluginSequence = getDefaultSequence();
	}

	public void quitOnApplicaton(Context context) {
		InitPlugin.quitPluginIfNeedOnApplicaton(context);
	}

	public boolean isBeyondLimit(String plginName) {
		return InitPlugin.isBeyondLimit(plginName);
	}

	public void getPSwitchFromServer(final String merchantId,
			final String pluginList) {
		PluginManage.pluginIndex = 0;// 重置插件切换顺序
		if (!timeOutCheck() && null != respObject) {
			Debug.i("PluginManage->getPSwitchFromServer->上一次的访问结果未失效");
			restorePluginLists();
			return;
		}
		String event2p = String.valueOf(TbuAndroidTools
				.getEventPointVersion(activity))
				+ String.valueOf(TbuAndroidTools.getPPointVersion(activity));
		TbuPHttpClient.getPSwitch(merchantId, event2p, pluginList,
				new SwitchCallback() {
					@Override
					public void result(String result) {
						Debug.i("PluginManage->getPSwitchFromServer 服务端信息->"
								+ result);
						if (result != null) {
							respObject = praseJson2Obj(result);
							PluginManage.secondConfirm = respObject
									.isSecondConfirm();
							Debug.i("PluginManage->secondConfirm->"
									+ PluginManage.secondConfirm);
							PluginManage.reqinterval = Integer
									.valueOf(respObject.getTimeOut());
							restorePluginLists();
						}
					}
				});
	}

	/**
	 * 回复客户端的插件列表
	 */
	public void restorePluginLists() {
		if (Buffett.onPSession) {
			// 如果在中就不在接受服务端信息
			Debug.i("PluginManage->restorePluginLists->Buffett.onPSession true");
			return;
		}
		String[] nativePlugins = NativePluginUtil.getSupportPlugins()
				.split(",");
		updatePlugins(
				respObject.getErrorCode(),
				PluginFilter.pluginsFilter(nativePlugins,
						respObject.getSequeens()));
	}

	/**
	 * 根据结果来对默认插件和插件队列进行一次更改
	 * 
	 * @param result
	 *            服务端下发本次获取信息结果
	 * @param default_Plugins
	 *            服务端下发的默认插件列表,按顺序切换
	 * @param plugins
	 *            服务端下发的当前可选插件列表,按顺序切换
	 */
	public void updatePlugins(String result, String[] pPlugins) {
		if (GET_INFO_SUCCCESS.equals(result)) {
			if (pPlugins != null && pPlugins.length > 0) {
				setDefaultSequence(pPlugins);
				pluginSequence = pPlugins;
				updateCurrentPlugin(pluginSequence[0]);
			} else {
				pluginSequence = getDefaultSequence();
				updateCurrentPlugin(getDefaultSequence()[0]);
			}
		} else {
			pluginSequence = getDefaultSequence();
			updateCurrentPlugin(getDefaultSequence()[0]);
		}
	}

	public boolean updateCurrentPlugin(String pluginId) {
		if (Buffett.onPSession) {
			Debug.i("PluginManage->updateCurrentPlugin, Buffett.onPSession = true");
			return false;
		}
		if (Buffett.getInstance() != null
				&& Buffett.getInstance().getPPluginName() != null) {
			if (Buffett.getInstance().getPPluginName()
					.equals(getPluginTypeByPluginId(pluginId))
					&& String.valueOf(Buffett.getInstance().isSecondConfirm())
							.equals(String.valueOf(PluginManage.secondConfirm))) {
				Debug.i("PluginManage->updateCurrentPlugin, plugin is same as last plugin");
				return false;
			}
		}
		if (pluginId.equals(PluginDefine.TBUSMS_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = SmPImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_TBUSMS,
					PluginManage.secondConfirm);
		} else if (pluginId.equals(PluginDefine.Z_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = ZhPImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_ZP,
					PluginManage.secondConfirm);
		}else if (pluginId.equals(PluginDefine.TK_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = tkPImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_TK,
					PluginManage.secondConfirm);
		} else if (pluginId.equals(PluginDefine.SKY_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = SPImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_SKY,
					PluginManage.secondConfirm);
		} else if (pluginId.equals(PluginDefine.LETU_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = LtPImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_LETU,
					PluginManage.secondConfirm);
		} else if (pluginId.equals(PluginDefine.IAPCMCC_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = IapMMPImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_IAPCMCC,
					PluginManage.secondConfirm);
		} else if (pluginId.equals(PluginDefine.UUC_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = UUCunPPluginImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_UUC,
					PluginManage.secondConfirm);
		} else if (pluginId.equals(PluginDefine.WX_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = GamePWxImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_WX,
					PluginManage.secondConfirm);
		}  else if (pluginId.equals(PluginDefine.GBXC_P_PLUGIN)) {
			Debug.i("PluginManage->updateCurrentPlugin = GamePayWxImpl,secondConfirm ="
					+ PluginManage.secondConfirm);
			setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_GBXC,
					PluginManage.secondConfirm);
		}  else {
			if (PluginDefine.FREE_P_PLUGIN
					.equals(getNativePPluginSequence()[0])) {
				Debug.i("PluginManage->updateCurrentPlugin 这是一个免费的包");
				setPPlginByName(activity, PluginDefine.P_PLUGINTYPE_FREE,
						PluginManage.secondConfirm);
			} else {
				Debug.i("PluginManage->updateCurrentPlugin = 服务端下发的插件列表中包含一个错误的信息:未找到ID = "
						+ pluginId + "的插件");
				pluginIndex++;
				setPPlginByName(activity, getNextPlugin(),
						PluginManage.secondConfirm);
			}

		}
		return true;
	}

	public boolean change2NextPlugin() {
		pluginIndex++;
		if (null != getNextPlugin()) {
			return updateCurrentPlugin(getNextPlugin());
		}
		return false;
	}

	/**
	 * 返回当前运营商的默认插件列表
	 * 
	 * @return
	 */
	public String[] getNativePPluginSequence() {
		return NativePluginUtil.getDefaultPPlugins().split(",");
	}

	/**
	 * 返回客户端可以支持的插件列表
	 * 
	 * @return
	 */
	public String getNativeSupportPlugins() {
		return NativePluginUtil.getSupportPlugins();
	}

	/**
	 * 插件是否实例化完成
	 * 
	 * @return
	 */
	public static boolean isSuccessInit() {
		return successInit;
	}

	public String[] getDefaultSequence() {
		SharedPreferences preferences = activity.getApplicationContext()
				.getSharedPreferences(DEFAULTPLUGIN, Context.MODE_PRIVATE);
		if (preferences != null
				&& preferences.getString(DEFAULT_SEQUENCE, "") != "") {
			String[] nativePlugins = NativePluginUtil.getSupportPlugins()
					.split(",");
			String[] defaultList = preferences.getString(DEFAULT_SEQUENCE,
					NativePluginUtil.getDefaultPPlugins()).split(",");
			return PluginFilter.pluginsFilter2(nativePlugins, defaultList);
		} else {
			return NativePluginUtil.getDefaultPPlugins().split(",");
		}
	}

	/**
	 * 解析服务端返回的数据
	 * 
	 * @param json
	 * @return
	 */
	public RespObject praseJson2Obj(String json) {
		RespObject obj = new RespObject();
		try {
			JSONObject resObj = new JSONObject(json);
			if (resObj.has("errorcode")) {
				obj.setErrorCode(String.valueOf(resObj.getInt("errorcode")));
			} else {
				Debug.e("PluginManage->praseJson2Obj 服务端下发的获取开关的返回信息未包含errorcode字段");
			}
			if (resObj.has("errormessage")) {
				obj.setErrorMessage(resObj.getString("errormessage"));
			} else {
				Debug.e("PluginManage->praseJson2Obj 服务端下发的获取开关的返回信息未包含errormessage字段");
			}
			if (resObj.has("plugin_list")) {
				String[] sequeens = resObj.getString("plugin_list").split(",");
				obj.setSequeens(sequeens);
			} else {
				Debug.e("PluginManage->praseJson2Obj 服务端下发的获取开关的返回信息未包含plugin_list字段");
			}
			if (resObj.has("second_confim")) {
				boolean second = SwitchCallback.P_SECOND_CONFIRM
						.equals(String.valueOf(resObj.getInt("second_confim"))) ? true
						: false;
				obj.setSecondConfirm(second);
			} else {
				Debug.e("PluginManage->praseJson2Obj 服务端下发的获取开关的返回信息未包含second_confim字段");
			}
			if (resObj.has("reqinterval")) {
				obj.setTimeOut(resObj.getInt("reqinterval"));
			} else {
				Debug.e("PluginManage->praseJson2Obj 服务端下发的获取开关的返回信息未包含reqinterval字段");
			}

		} catch (Exception e) {
			Debug.e("PluginManage->praseJson2Obj Exception =" + e);
		}
		return obj;
	}

	/**
	 * 插件选择协议 :字符串做静态定义
	 * 
	 * @param pluginId
	 * @return
	 */
	private String getPluginTypeByPluginId(String pluginId) {
		if (pluginId.equals(PluginDefine.TBUSMS_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_TBUSMS;
		} else if (pluginId.equals(PluginDefine.SKY_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_SKY;
		} else if (pluginId.equals(PluginDefine.LETU_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_LETU;
		} else if (pluginId.equals(PluginDefine.Z_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_ZP;
		} else if (pluginId.equals(PluginDefine.IAPCMCC_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_IAPCMCC;
		} else if (pluginId.equals(PluginDefine.UUC_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_UUC;
		} else if (pluginId.equals(PluginDefine.WX_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_WX;
		} else if (pluginId.equals(PluginDefine.GBXC_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_GBXC;
		}else if (pluginId.equals(PluginDefine.TK_P_PLUGIN)) {
			return PluginDefine.P_PLUGINTYPE_TK;
		} else {
			return null;
		}
	}

	private void setDefaultSequence(String[] plugins) {
		SharedPreferences preferences = activity.getApplicationContext()
				.getSharedPreferences(DEFAULTPLUGIN, Context.MODE_PRIVATE);
		SharedPreferences.Editor editor = preferences.edit();
		String s = "";
		for (int i = 0; i < plugins.length; i++) {
			if (i < plugins.length - 1) {
				s += plugins[i] + ",";
			} else {
				s += plugins[i];
			}
		}
		editor.putString(DEFAULT_SEQUENCE, s);
		editor.commit();
	}

	/**
	 * 获取下一个插件
	 * 
	 * @param pluginSequence
	 *            :是不重复数组
	 * @param defaultPlugin
	 * @param count
	 * @return
	 */
	private String getNextPlugin() {
		Debug.e("PluginManage->getNextPlugin  Buffett.getInstance().getPPluginName"
				+ Buffett.getInstance().getPPluginName());
		if (pluginSequence != null && pluginSequence.length > 0) {
			// 插件列表不为空
			Debug.e("PluginManage->getNextPlugin  pluginSequence.length="
					+ pluginSequence.length);
			if (pluginIndex < pluginSequence.length) {
				Debug.i("PluginManage->getNextPlugin,pluginSequence["
						+ pluginIndex + "]=" + pluginSequence[pluginIndex]);
				return pluginSequence[pluginIndex];
			} else {
				return null;
			}
		} else {
			Debug.e("PluginManage->getNextPlugin  pluginSequence is null");
			return null;
		}

	}

	private void setPPlginByName(Activity activity, String pluginName,
			boolean secondConfirm) {
		boolean success = false;
		// 获取map，遍历
		for (Map.Entry<String, String> entry : PluginInfos.getPlugins()
				.entrySet()) {
			if (pluginName != null & pluginName.equals(entry.getKey())) {
				setPPluginByClassName(entry.getValue(), activity,
						secondConfirm);
				Debug.i("PluginManage-> setPPlginByName() = "
						+ entry.getValue());
				success = true;
			}
		}
		// 遍历列表，未发现符合条件的插件
		if (!success) {
			Debug.e("PluginManage->发生错误,启用备用方案: PluginInfos.getDefaultPlufinName() = "
					+ PluginInfos.getDefaultPlufinName()+"===="+pluginName);
			setPPluginByClassName(PluginInfos.getDefaultPlufinName(),
					activity, secondConfirm);
		}
	}

	private void setPPluginByClassName(String plginClassName,
			Activity activity, boolean secondConfirm) {
		try {
			Class c = Class.forName(plginClassName);
			Object newInstance = c.newInstance();
			setPPlugin((PInterface) newInstance, activity, secondConfirm);
		} catch (Exception e) {
			Debug.e("PluginManage->setPPlginByTypeName, fail init, plginClassName = "
					+ plginClassName + ", e = " + e.toString());
		}
	}

	private void setPPlugin(PInterface pImpl, Activity activity,
			boolean secondConfirm) {
		Buffett.setPPlugin(pImpl, activity, secondConfirm);
		successInit = true;
	}

	private static long lastRespTime = 0;// 上一次访问开关的时间
	private static int reqinterval = 600;// 初始的请求间隔600秒

	private boolean timeOutCheck() {
		long currentTime = System.currentTimeMillis();
		if (currentTime - lastRespTime > reqinterval * 1000) {
			lastRespTime = currentTime;
			return true;
		}
		return false;
	}

}
