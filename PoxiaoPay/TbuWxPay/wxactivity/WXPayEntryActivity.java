package com.poixao.crazyfarm.wxapi;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.tbu.wx.debug.Debug;
import com.tencent.mm.sdk.constants.ConstantsAPI;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelpay.PayResp;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

public class WXPayEntryActivity extends Activity implements IWXAPIEventHandler {

	private IWXAPI api;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Debug.e("pay wx onCreate ...");
		api = WXAPIFactory.createWXAPI(this, "wx884476f603eeb8be");
		api.handleIntent(getIntent(), this);
	}

	@Override
	protected void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		setIntent(intent);
		api.handleIntent(intent, this);
	}

	@Override
	public void onReq(BaseReq req) {
	}

	@Override
	public void onResp(BaseResp resp) {
		Debug.e("onPayFinish, errCode = " + resp.errCode);
		if (resp.getType() == ConstantsAPI.COMMAND_PAY_BY_WX) {
			PayResp payResp = (PayResp) resp;
			Debug.e("payresp prepayId =  " + payResp.prepayId);
			if (resp.errCode == BaseResp.ErrCode.ERR_OK) {
				//  TODO 支付成功
			} else {
				// TODO 支付失败
			}
		}
		WXPayEntryActivity.this.finish();
	}
}