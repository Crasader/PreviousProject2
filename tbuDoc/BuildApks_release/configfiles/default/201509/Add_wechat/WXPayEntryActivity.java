package com.kx.byno.wxapi;
//
//import android.app.Activity;
//import android.content.Intent;
//import android.os.Bundle;
//
//import com.tallbigup.android.impl.GamePayImpl;
//import com.tallbigup.buffett.Buffett;
//import com.tallbigup.buffett.OrderResultInfo;
//import com.tbu.androidtools.Debug;
//import com.tbu.wx.util.WxAppInfo;
//import com.tencent.mm.sdk.constants.ConstantsAPI;
//import com.tencent.mm.sdk.modelbase.BaseReq;
//import com.tencent.mm.sdk.modelbase.BaseResp;
//import com.tencent.mm.sdk.modelpay.PayResp;
//import com.tencent.mm.sdk.openapi.IWXAPI;
//import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
//import com.tencent.mm.sdk.openapi.WXAPIFactory;
//
//public class WXPayEntryActivity extends Activity implements IWXAPIEventHandler {
//
//	private IWXAPI api;
//
//	@Override
//	public void onCreate(Bundle savedInstanceState) {
//		super.onCreate(savedInstanceState);
//		Debug.e("pay wx onCreate ...");
//		api = WXAPIFactory.createWXAPI(this, WxAppInfo.getWxInfo().getAppId());
//		api.handleIntent(getIntent(), this);
//	}
//
//	@Override
//	protected void onNewIntent(Intent intent) {
//		super.onNewIntent(intent);
//		setIntent(intent);
//		api.handleIntent(intent, this);
//	}
//
//	@Override
//	public void onReq(BaseReq req) {
//	}
//
//	@Override
//	public void onResp(BaseResp resp) {
//		if (resp.getType() == ConstantsAPI.COMMAND_PAY_BY_WX) {
//			PayResp payResp = (PayResp) resp;
//			Debug.e("payresp prepayId =  " + payResp.prepayId);
//			Debug.e("onPayFinish, errCode = " + resp.errCode);
//			if (resp.errCode == BaseResp.ErrCode.ERR_OK) {
//				OrderResultInfo ori = new OrderResultInfo();
//				ori.setResultCode(OrderResultInfo.PAY_SUCCESS);
//				ori.setErrorCode("" + OrderResultInfo.PAY_SUCCESS);
//				ori.setErrorMsg("支付成功!");
//				Buffett.getInstance().getPayCallBack().result(ori);	
//			} else {
//				OrderResultInfo ori = new OrderResultInfo();
//				ori.setResultCode(OrderResultInfo.PAY_FAIL);
//				ori.setErrorCode("" + OrderResultInfo.PAY_FAIL);
//				ori.setErrorMsg("支付失败!");
//				Buffett.getInstance().getPayCallBack().result(ori);
//			}
//		}else{
//			OrderResultInfo ori = new OrderResultInfo();
//			ori.setResultCode(OrderResultInfo.PAY_FAIL);
//			ori.setErrorCode("" + OrderResultInfo.PAY_FAIL);
//			ori.setErrorMsg("支付失败!");
//			Buffett.getInstance().getPayCallBack().result(ori);
//		}
//		WXPayEntryActivity.this.finish();
//	}
//}