package com.poixao.crazyfarm;


<<<<<<< HEAD

=======
>>>>>>> master
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class AppRegister extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		final IWXAPI msgApi = WXAPIFactory.createWXAPI(context, null);
<<<<<<< HEAD
=======

>>>>>>> master
		msgApi.registerApp(Constants.APP_ID);
	}
}
