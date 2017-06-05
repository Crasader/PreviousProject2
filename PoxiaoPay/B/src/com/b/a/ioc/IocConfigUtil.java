package com.b.a.ioc;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.util.ReadJsonUtil;

public class IocConfigUtil {
	private static boolean successInit = false;

	// 从本地的JSON读取需要通过反射加载的插件列表
	public static void init(Context context) {
		if (!successInit) {
			readConfig(context);
		}
	}

	private static final String CONFIG_PATH = x.y.z.b("XEVZWBlfWVVVWVhQX1EYXEVZWA==");

	private static void readConfig(Context context) {
		InputStream input = null;
		try {
			// 获取文件内容
			input = context.getAssets().open(CONFIG_PATH);
			byte[] buffer = new byte[input.available()];
			input.read(buffer);
			// 转化格式
			String info = new String(buffer, x.y.z.b("Q0JQGw4="));
			// 解密
		    String json = ReadJsonUtil.decoderByDES(context,info, ReadJsonUtil.KEY);
			JSONObject jobject;
			try {
				// 解析JSON数据
				jobject = new JSONObject(json);
				// 第一段
				if (jobject.has(x.y.z.b("V0ZGWl9VV0JfWVh/W0Za"))) {
					IocInfos.setApplicationImpl(jobject
							.getString(x.y.z.b("V0ZGWl9VV0JfWVh/W0Za")));
				} else {
					Debug.e(x.y.z.b("f1lVdVlYUF9RY0JfWhsbCBZEU1dSdVlYUF9RGldGRlpfVVdCX1lYf1tGWhZVV1gWWFlCFlBfWFI="));
					System.exit(0);
				}
				// 第二段
				if (jobject.has(x.y.z.b("RldPf1tGWg=="))) {
					JSONObject obj = jobject.getJSONObject(x.y.z.b("RldPf1tGWg=="));
					if (obj.has(x.y.z.b("VVpXRUV4V1tT")) && obj.has(x.y.z.b("UENYVUJfWVg="))) {
						IocInfos.setPayImplName(obj.getString(x.y.z.b("VVpXRUV4V1tT")));
						IocInfos.setPImplFunction(obj.getString(x.y.z.b("UENYVUJfWVg=")));
					} else {
						Debug.e(x.y.z.b("f1lVdVlYUF9RY0JfWhsbCBZEU1dSdVlYUF9RGlxFWVgWX0UWWFlCFnVZW0ZaX1dYVVMWQV9CXhZkU0dDX0RTW1NYQkU="));
						System.exit(0);
					}
				}
				successInit = true;
			} catch (JSONException e) {
				Debug.e(x.y.z.b("f1lVdVlYUF9RY0JfWhsbCBZEU1dSdVlYUF9RGnxleXhzTlVTRkJfWVgM")
						+ e.toString());
				System.exit(0);
			}
		} catch (Exception e) {
			Debug.e(x.y.z.b("f1lVdVlYUF9RY0JfWhsbCERTV1J1WVhQX1EaVVdYFlhZQhZaWVdSFlxFWVgWUERZWxZXRUVTQhYM")
					+ e.toString());
			System.exit(0);
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					Debug.e(x.y.z.b("f1lVdVlYUF9RY0JfWhsbCERTV1J1WVhQX1EaFn95c05VU0ZCX1lYFgw=")
							+ e.toString());
					System.exit(0);
				}
			}

		}
	}
}