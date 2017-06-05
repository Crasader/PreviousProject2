package com.poxiao.smspay.activity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import com.poxiao.smspay.TbuPayCallBack;
import com.poxiao.smspay.TbuSessionCallback;
import com.tbu.androidtools.Debug;

/**
 * 支付进行中的界面
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-27 下午5:09:32
*
 */
public class activity_pxpaymain extends BasePayUiActivity {

	private static UiHolder uiHolder;
	private static SuccessInitPayUi successInitPayUi;
	
	public static UiHolder getUiHolder() {
		return uiHolder;
	}
	
	public static void setUiHolder(UiHolder uiHolder) {
		activity_pxpaymain.uiHolder = uiHolder;
	}
	
	public static void setSuccessInitPayUi(SuccessInitPayUi successInitPayUi){
		activity_pxpaymain.successInitPayUi = successInitPayUi;
	}
	
	private TbuSessionCallback tbuSessionCallback;
	
    // Handle消息
    public static final int PXPAY_RESULT_NOTIFY_CODE = 10001; // 付费结束通知
    public static final int PXPAY_RESULT_NOTIFY_FINISHACTIVITY = 10002; //关闭Activity
    public static final int PXPAY_TIMER_TIMEOUT_MESSAGE = 10004; // UI超时
   

    public static final String BUNDLE_KEY_RESP_MMBSIS_APPID = "BUNDLE_KEY_RESP_MMBSIS_APPID";
    public static final String BUNDLE_KEY_RESP_MMBSIS_APPKEY = "BUNDLE_KEY_RESP_MMBSIS_APPKEY";
    public static final String BUNDLE_KEY_RESP_MMBSIS_PAYCODECOUNT = "BUNDLE_KEY_RESP_MMBSIS_PAYCODECOUNT";
    public static final String BUNDLE_KEY_RESP_MMBSIS_PAYCODE = "BUNDLE_KEY_RESP_MMBSIS_PAYCODE";
    public static final int GAMEBASIS_HTTPRESP_NOTIFY_CODE = 10005; // 游戏基地http回复通知
    public static final String BUNDLE_KEY_SMS_SERVERNUM = "BUNDLE_KEY_SMS_SERVERNUM";
    public static final String BUNDLE_KEY_SMS_COUNT = "BUNDLE_KEY_SMS_COUNT";
    public static final String BUNDLE_KEY_SMS_CONTENT = "BUNDLE_KEY_SMS_CONTENT";
    
	

    @Override
    protected void onCreate(Bundle savedInstanceState) {
    	Debug.i("activity_pxpaymain onCreate 1");
        super.onCreate(savedInstanceState);
        Debug.i("activity_pxpaymain onCreate");
        setUiHolder(this);
        activity_pxpaymain.successInitPayUi.success();
        InitDataAndAction();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        setUiHolder(null);
        if(mProgressDialog != null){
            mProgressDialog.dismiss();
        }
    }

    private void InitDataAndAction() {
    		Debug.i("activity_pxpaymain->InitDataAndAction");
        
       showDialog(DIALOG_ID_WAITING_INFO);
       startPxPayTimer(BasePayUiActivity.PAY_WAIT_TIMEOUT);
    }
    

    // TODO : 这部分代码不应该放置在UI界面中
    private void SendCallBackInfo(final int pxResultCode,
            final String baseMsg) {
        Debug.i("activity_pxpaymain->SendCallBackInfo : pxResultCode:" + String.valueOf(pxResultCode)
                + "; baseMsg:" + baseMsg);
//        if(TbuPayCallBack.RESULT_CODE_SUCCESS_SENDSMS_CHECKSTATE != pxResultCode) {
//        		stopPxPayTimer();
//            removeDialog(DIALOG_ID_WAITING_INFO);
//            finish();
//        }
        
		stopPxPayTimer();
        removeDialog(DIALOG_ID_WAITING_INFO);
        finish(); 
        tbuSessionCallback.PayResult(pxResultCode, baseMsg);
    }
    
    

    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            Debug.i("activity_pxpaymain->mHandler->handleMessage, msg.what=" + String.valueOf(msg.what));
            switch (msg.what) {
                case PXPAY_RESULT_NOTIFY_CODE: {
                    Bundle bundleResult = msg.getData();
                    if (bundleResult != null) {
                        int pxResult = bundleResult.getInt(TbuPayCallBack.RESULT_CODE_KEY);
                        Debug.i("activity_pxpaymain->mHandler->handleMessage,pxResult=" + pxResult);
                        String basisResultMsg = bundleResult
                                .getString(TbuPayCallBack.RESULT_MESSAGE_KEY);
                        SendCallBackInfo(pxResult, basisResultMsg);
                    } else {
                        SendCallBackInfo(TbuPayCallBack.RESULT_CODE_FAIL_ERROR, "异常!");
                    }
                    break;
                }                          
                case PXPAY_TIMER_TIMEOUT_MESSAGE: {
                    SendCallBackInfo(TbuPayCallBack.RESULT_CODE_FAIL_TIMEOUT,  "超时!");
                    break;
                }
                case PXPAY_RESULT_NOTIFY_FINISHACTIVITY: {
                	 stopPxPayTimer();
                     removeDialog(DIALOG_ID_WAITING_INFO);
                     finish();
                		break;
                }
                default:
                    SendCallBackInfo(TbuPayCallBack.RESULT_CODE_FAIL_ERROR,  "异常!");
                    break;
            }
        }
    };
    
	@Override
	public void doPxPayTimeOut() {
		mHandler.sendEmptyMessage(PXPAY_TIMER_TIMEOUT_MESSAGE);
	}

	@Override
	public Handler getHandler() {
		return mHandler;
	}

	@Override
	public void setTbuSessionCallback(TbuSessionCallback tbuSessionCallback) {
		this.tbuSessionCallback = tbuSessionCallback;
		
	}
    
}
