package com.tbu.hd.manage;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.json.JSONException;
import org.json.JSONObject;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;
import com.tbu.androidtools.util.ReadJsonUtil;

/**
 * 
 * 活动客户端与服务端的交互
 * 
 * @author QZ
 *
 */
public class HdHttpTools {

	public  final static String HD_URL_HEAD = "8d1a6e6821c373096363f8e6c04f192935af2b929c4235e8b42a078574c08facbf277d6587435a4f";
	public  final static String UPLOAD_URL = "8d1a6e6821c373096363f8e6c04f192935af2b929c4235e8b42a078574c08fac4738420b3c2c175237e3735471586d88";

	public interface HdUpdateListener {
		public void onUpdate();
	}

	// get请求:根据游戏的id来返回需要显示的内容
	public static void doGet(HdCallback callback) {
		final String strUrl = ReadJsonUtil.decoderByDES(HD_URL_HEAD,"p_k") ;
		Debug.i("HdSystem HdHttpTools doGet strUrl="+strUrl);
		HttpParams httpParameters = new BasicHttpParams();
		// Set the timeout in milliseconds until a connection is established.
		// The default value is zero, that means the timeout is not used.
		int timeoutConnection = 3000;
		HttpConnectionParams.setConnectionTimeout(httpParameters,
				timeoutConnection);
		// Set the default socket timeout (SO_TIMEOUT)
		// in milliseconds which is the timeout for waiting for data.
		HttpConnectionParams.setSoTimeout(httpParameters, timeoutConnection);
		HttpClient httpclient = new DefaultHttpClient(httpParameters);
		HttpGet target = new HttpGet(strUrl + AppInfo.getTId());
		HttpResponse resp = null;
		InputStream is = null;
		try {
			resp = httpclient.execute(target);
			if (resp != null && resp.getStatusLine() != null
					&& resp.getStatusLine().getStatusCode() == 200) {
				is = resp.getEntity().getContent();
				String text = getStringFromInputStream(is);
				Debug.i("HdHttpTools->doGet,resp = " + text);
				String callbckText = null;
				if (text != null && text.length() > 0) {
					try {
						JSONObject json = new JSONObject(text);
						if (json.has("error")) {
							if (json.getInt("error") == 0) {
								if (json.has("data")) {
									JSONObject jobject = json
											.getJSONObject("data");
									int index = 0;
									boolean isend = false;
									StringBuffer hdText = new StringBuffer();
									do {
										isend = jobject.has("index");
										hdText.append(jobject.getString(String
												.valueOf(index)));
										index++;
									} while (isend);
									callbckText = hdText.toString();
								}
							}
						}
					} catch (JSONException e) {
						e.printStackTrace();
					}
				}
				callback.setHdTextInfo(callbckText);
				;
			}
		} catch (Exception e) {
			Debug.e("HdHttpTools->doGet,Exception " + e.toString());
		}
	}

	public static String doPost(final String strContent) {
		Debug.i("HdHttpTools->DoPost, strContent:" + strContent);
		final String strUrl = ReadJsonUtil.decoderByDES(UPLOAD_URL,"p_k") ;
		Debug.i("HdSystem HdHttpTools doPost strUrl="+strUrl);
		if (strContent == null) {
			return null;
		}
		try {
			URL url = new URL(strUrl);
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
			byte[] byteBuffer = input2byte(inputStream);

			String strResult = new String(byteBuffer);
			Debug.i("HdHttpTools->DoPost, strJson result =" + strResult);
			inputStream.close();
			urlConnection.disconnect();
			return strResult;
		} catch (Exception e) {
			Debug.e("HdHttpTools->DoPost, e = " + e.toString());
			return null;
		}

	}

	/**
	 * 构�?�请求参�?
	 * 
	 * @param phoneNumber
	 * @param msg
	 * @return
	 */
	public static String createUploadInfo(String phoneNumber, String msg) {

		KeyValue keyValue20 = new KeyValue("hdfactory", DeviceInfo.getProduct());
		KeyValue keyValue21 = new KeyValue("hdtype", DeviceInfo.getModle());
		KeyValue keyValue22 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue23 = new KeyValue("si", DeviceInfo.getsi());
		KeyValue keyValue28 = new KeyValue("channelid", AppInfo.getEntrance());
		KeyValue keyValue29 = new KeyValue("gameid", AppInfo.getTId());
		KeyValue keyValue30 = new KeyValue("phonenum", phoneNumber);
		KeyValue keyValue31;
		try {
			keyValue31 = new KeyValue("taskmsg",
					URLEncoder.encode(msg, "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue31 = new KeyValue("taskmsg", msg);
			Debug.e("BServerManager->createPayInfo, set pay_result fail. e = "
					+ e.toString());
		}
		return DoContentJoint(keyValue20, keyValue21, keyValue22, keyValue23,
				keyValue28, keyValue29, keyValue30, keyValue31);
	}

	private static String DoContentJoint(KeyValue... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();// "?"+
				else
					httpContent += "&" + keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
			}

			return httpContent;
		}

		return null;
	}

	private static byte[] input2byte(InputStream inStream) throws IOException {
		ByteArrayOutputStream swapStream = new ByteArrayOutputStream();
		byte[] buff = new byte[100];
		int rc = 0;
		while ((rc = inStream.read(buff, 0, 100)) > 0) {
			swapStream.write(buff, 0, rc);
		}
		byte[] in2b = swapStream.toByteArray();
		return in2b;
	}

	public static String getStringFromInputStream(InputStream in)
			throws IOException {
		InputStreamReader is = new InputStreamReader(in);
		StringBuilder sb = new StringBuilder();
		BufferedReader br = new BufferedReader(is);
		String read = br.readLine();
		while (read != null) {
			sb.append(read);
			read = br.readLine();

		}
		return sb.toString();
	}
}
