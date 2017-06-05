package com.poxiao.smspay.activity;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.view.WindowManager;

import com.poxiao.smspay.plgin.mark.util.Debug;

public abstract class BasePayUiActivity extends Activity 
		implements UiHolder{

	public static final int PAY_WAIT_TIMEOUT = 30*1000;
	
	protected ProgressDialog mProgressDialog;
    
    protected final int DIALOG_ID_WAITING_INFO = 20001;
	
	private Timer mTimeOutTimer = null;

	@Override
    public void startPxPayTimer(int timeNum) {
		Debug.i("BasePayUiActivity->startPxPayTimer, timeNum=" + timeNum);
        stopPxPayTimer();

        if (mTimeOutTimer == null) {
            mTimeOutTimer = new Timer();
        }
        mTimeOutTimer.scheduleAtFixedRate(new PxPayTimerTask(), timeNum, timeNum);
    }

    protected void stopPxPayTimer() {
        if (mTimeOutTimer != null) {
            mTimeOutTimer.cancel();
            mTimeOutTimer = null;
        }
    }

    private class PxPayTimerTask extends TimerTask {
        @Override
        public void run() {
        		doPxPayTimeOut();
        }
    }
    
    @Override
    protected Dialog onCreateDialog(int id) {
        switch (id) {
            case DIALOG_ID_WAITING_INFO: {
                ProgressDialog progressDialog;
                progressDialog = new ProgressDialog(this);
                progressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);// 设置风格为圆形进度条
                progressDialog.setMessage("操作进行中，请稍候...");
                progressDialog.setIndeterminate(true);// 设置进度条是否为不明确
                progressDialog.setCancelable(false);// 设置进度条是否可以按退回键取消
                progressDialog.getWindow().setFlags(
						WindowManager.LayoutParams.FLAG_FULLSCREEN,
						WindowManager.LayoutParams.FLAG_FULLSCREEN);
                progressDialog.show();
                mProgressDialog = progressDialog;
                break;
            }
            default:
                break;
        }
        return super.onCreateDialog(id);
    }
    
    /**
     * 如果计费点超时的处理逻辑
     */
    public abstract void doPxPayTimeOut();
}
