package com.poxiao.pay.xbll.plugin;

import android.app.Activity;
import android.content.Context;

import com.t.bfft.OrderInfo;
import com.t.bfft.OrderResultInfo;
import com.t.bfft.PCallback;
import com.t.bfft.PInterface;
import com.t.p.PUI;

public class GamePayDebugImpl implements PInterface {

	private boolean second_confirm = false;

	@Override
	public String getPPluginName() {
		return "px";
	}

	@Override
	public int getPVersionId() {
		return 0;
	}

	private OrderResultInfo ori;

	@Override
	public void py(final Activity activity, final OrderInfo orderInfo,
			boolean isShowUi, final PCallback payCallback) {
		PUI.showPDialog(activity, orderInfo.getPPointNum(),
				getPPluginName(), new PCallback() {

					@Override
					public void result(OrderResultInfo orderResultInfo) {
						ori = new OrderResultInfo();
						if (orderResultInfo.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
							if (second_confirm) {
								PUI.showPDialog(activity,
										orderInfo.getPPointNum(), "second",
										new PCallback() {
											@Override
											public void result(
													OrderResultInfo res) {
												if (res.getResultCode() == OrderResultInfo.CLICK_CONFIRM) {
													ori.setResultCode(OrderResultInfo.P_SUCCESS);
													ori.setErrorCode(""
															+ OrderResultInfo.P_SUCCESS);
													ori.setErrorMsg("支付成功!");
												} else {
													ori.setResultCode(OrderResultInfo.P_FAIL);
													ori.setErrorCode(""
															+ OrderResultInfo.P_FAIL);
													ori.setErrorMsg("支付失败!");
												}
											}
										});
							} else {
								ori.setResultCode(OrderResultInfo.P_SUCCESS);
								ori.setErrorCode(""
										+ OrderResultInfo.P_SUCCESS);
								ori.setErrorMsg("支付成功!");
							}
						} else {
							ori.setResultCode(OrderResultInfo.P_FAIL);
							ori.setErrorCode("" + OrderResultInfo.P_FAIL);
							ori.setErrorMsg("支付失败!");
						}
						payCallback.result(ori);
					}
				});
	}

	@Override
	public void initPPlugin(Activity activity, boolean secondConfirm) {

	}

	@Override
	public boolean isSecondConfirm() {
		return false;
	}

	public static void init(Context context) {

	}

}
