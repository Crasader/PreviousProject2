package com.t.p;

import android.app.Activity;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;

import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.p.ca.PUICallBack;
import com.t.p.view.pui.PUIDialog;

public class PUI {
	// 自有的支付界面
	public static void showPDialog(final Activity activity,
			final int pPoint, final String payPluginName,
			final PCallback callback) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				final PUIDialog dialog = new PUIDialog(activity, pPoint,
						payPluginName, new PUICallBack() {
							@Override
							public void pConfirm() {
								OrderResultInfo result = new OrderResultInfo();
								result.setResultCode(OrderResultInfo.CLICK_CONFIRM);
								result.setErrorCode(""
										+ OrderResultInfo.CLICK_CONFIRM);
								result.setErrorMsg("点击确定");
								callback.result(result);
							}

							@Override
							public void pCancel() {
								OrderResultInfo result = new OrderResultInfo();
								result.setResultCode(OrderResultInfo.CLICK_CANCEL);
								result.setErrorCode(""
										+ OrderResultInfo.CLICK_CANCEL);
								result.setErrorMsg("点击取消");
								callback.result(result);
							}
						});
				dialog.getWindow().setFlags(
						WindowManager.LayoutParams.FLAG_FULLSCREEN,
						WindowManager.LayoutParams.FLAG_FULLSCREEN);
				dialog.show();
				dialog.getWindow().setLayout(LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT);
			}
		});
	}
}
