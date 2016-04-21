package com.poixao.crazyfarm.wxapi;


import android.app.Activity;
import android.os.Bundle;
import android.os.Debug;
import android.util.Log;

import com.poixao.crazyfarm.Constants;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

public class WXEntryActivity extends Activity implements IWXAPIEventHandler{
	

    private IWXAPI api;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

			
  api = WXAPIFactory.createWXAPI(this, Constants.APP_ID);
        api.handleIntent(getIntent(), this);

    }

	public void onReq(BaseReq req) {
		Log.e("TBU_DEBUG", "onshare, errCode = " + req.getType());
//		Toast.makeText(this, "openid = " + req.openId, Toast.LENGTH_SHORT).show();
//		
//		switch (req.getType()) {
//		case ConstantsAPI.COMMAND_GETMESSAGE_FROM_WX:	
//			break;
//		case ConstantsAPI.COMMAND_SHOWMESSAGE_FROM_WX:
//			break;
//		case ConstantsAPI.COMMAND_LAUNCH_BY_WX:
//			break;
//		default:
//			break;
		
	}

	// ������Ӧ�÷��͵�΢�ŵ�����������Ӧ�������ص����÷���
	@Override
	public void onResp(BaseResp resp) {
		Log.e("TBU_DEBUG","onshare, errCode = " + resp.errCode);

		
//		if (resp.getType() == ConstantsAPI.COMMAND_SENDAUTH) {
//			Toast.makeText(this, "code = " + ((SendAuth.Resp) resp).code, Toast.LENGTH_SHORT).show();
//		}
//		
//		int result = 0;
//		
//		switch (resp.errCode) {
//		case BaseResp.ErrCode.ERR_OK:
//
//			break;
//		case BaseResp.ErrCode.ERR_USER_CANCEL:
//
//			break;
//		case BaseResp.ErrCode.ERR_AUTH_DENIED:
//
//			break;
//		default:
//		
//			break;
//		}
//		
//		Toast.makeText(this, result, Toast.LENGTH_LONG).show();
		finish();
	}
	
}