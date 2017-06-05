package com.candy.futon;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.net.ConnectivityManager;
import android.os.IBinder;
import android.view.Gravity;
import android.widget.TextView;

import com.andy.canvasgame.GameApplication;
import com.andy.canvasgame.IGameApplication;
import com.andy.canvasgame.service.SoundService;
import com.andy.canvasgame.settings.GameSetting;
import com.andy.canvasgame.util.CrashHandler;
import com.andy.canvasgame.util.ToastUtil;
import com.candy.futon.activitys.GameActivity;
import com.candy.futon.activitys.SplashActivity;
import com.candy.futon.dialog.ChargeDialog;
import com.candy.futon.domain.DefaultPlayerGenerator;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.domain.GameID;
import com.candy.futon.domain.IPlayerGenerator;
import com.candy.futon.domain.PlayerInfo;
import com.candy.futon.service.DownloadService;

import com.poxiao.ddz.standalone.R;

public class FutonDdzApplication extends GameApplication implements IGameApplication, IFutonDdzApplication{

	public final static String AI_LOG_KEY = "AI_LOG";
	
	private PlayerInfo playerInfo;

	private BroadcastReceiver mNetworkStateReceiver;
	
	private IPlayerGenerator playerGenerator;
	
	private DownloadService mDownloadService;
	
	@Override
	public Class<? extends Activity> getSplashScreenClass() {
		return SplashActivity.class;
	}

	@Override
	public void onCreate() {
		super.onCreate();
		// 异常处理，不需要处理时注释掉这两句即可！  
	    CrashHandler crashHandler = CrashHandler.getInstance();   
	    // 注册crashHandler   
	    crashHandler.init(getApplicationContext());   
	    
		GameSetting.getInstance().init(getApplicationContext());
		SoundService.getInstance().init(new String[]{"1.ogg","10.ogg","11.ogg","12.ogg","13.ogg","100.ogg","101.ogg","2.ogg","3.ogg","4.ogg","5.ogg","6.ogg","7.ogg","8.ogg","9.ogg","baojing1.ogg","baojing2.ogg","buyao1.ogg","buyao2.ogg","buyao3.ogg","buyao4.ogg","dani1.ogg","dani2.ogg","dani3.ogg","dui1.ogg","dui10.ogg","dui11.ogg","dui12.ogg","dui13.ogg","dui2.ogg","dui3.ogg","dui4.ogg","dui5.ogg","dui6.ogg","dui7.ogg","dui8.ogg","dui9.ogg","feiji.ogg","liandui.ogg","NoOrder.ogg","Order.ogg","sandaiyi.ogg","sandaiyidui.ogg","shunzi.ogg","sidaier.ogg","sidailiangdui.ogg","tuple1.ogg","tuple10.ogg","tuple11.ogg","tuple12.ogg","tuple13.ogg","tuple2.ogg","tuple3.ogg","tuple4.ogg","tuple5.ogg","tuple6.ogg","tuple7.ogg","tuple8.ogg","tuple9.ogg","wangzha.ogg","zhadan.ogg"});
		
		GameConfig.getInstance().load(getApplicationContext());
		playerInfo = PlayerInfo.getHeroPlayer(this);
		TextView view = new TextView(this);
		view.setBackgroundResource(R.drawable.lobby_info_bg);
		view.setGravity(Gravity.CENTER);
		view.setTextColor(Color.WHITE);
		ToastUtil.setTextView(view);
		ToastUtil.setGravityAndXY(Gravity.CENTER, 0, 0);
		mNetworkStateReceiver = new ConnectionChangeReceiver();
		IntentFilter filter = new IntentFilter();  
		filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION); 
		registerReceiver(mNetworkStateReceiver, filter); 
		bindDownloadService();
		
	}

	@Override
	public PlayerInfo getPlayerInfo() {
		return playerInfo;
	}
	
	@Override
	public void addCoin2Hero(int coin){
		addCoin2Hero(coin, true);
	}



	@Override
	public Class<? extends GameActivity> getGameActivityClass() {
		return GameActivity.class;
	}







	@Override
	public Class<? extends ChargeDialog> getChargeDialogClass() {
		// TODO Auto-generated method stub
		return ChargeDialog.class;
	}





	@Override
	public IPlayerGenerator getPlayerGenerator(){
		if(this.playerGenerator == null){
			this.playerGenerator = new DefaultPlayerGenerator();
		}
		return this.playerGenerator;
	}



	@Override
	public int getGameId() {
		return GameID.KAIXIN_DDZ;
	}



	@Override
	public String getPromoteNotAvaliableString() {
		return getPackageName() +"promote_download_not_avaliable";
	}



	@Override
	public String getPromoteDownloadProgressString() {
		return getPackageName() +"promote_download_progress";
	}



	@Override
	public String getPromoteDownloadCompleteString() {
		return getPackageName() +"promote_download_complete";
	}



	@Override
	public String getPromoteDownloadStartString() {
		return getPackageName() +"promote_download_start";
	}



	@Override
	public String getPromoteDownloadErrorString() {
		return getPackageName() +"promote_download_error";
	}

	private void bindDownloadService(){
		Intent intent = new Intent(this, DownloadService.class);
		bindService(intent, mDownloadConn, Context.BIND_AUTO_CREATE);
	}
	
	private ServiceConnection mDownloadConn = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			if(!(service instanceof DownloadService.LocalDownloadServiceBinder)){
				return;
			}
			mDownloadService = ((DownloadService.LocalDownloadServiceBinder)service).getService();
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			mDownloadService = null;
		}
    };

	@Override
	public void addCoin2Hero(int coin, boolean playAnimation) {
		int currentCoin = getPlayerInfo().getPoint();
		this.getPlayerInfo().setPoint(currentCoin + coin);
		PlayerInfo.savePlayerInfo(getApplicationContext(), getPlayerInfo());
		if(GameEngine.getInstance() != null && playAnimation){
			GameEngine.getInstance().startCoinAnimation(currentCoin, coin);
		}
	}
	
	private  static Bitmap getBitmapFromURL(String src) {
	    try {
	        URL url = new URL(src);
	        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
	        connection.setDoInput(true);
	        connection.connect();
	        InputStream input = connection.getInputStream();
	        Bitmap myBitmap = BitmapFactory.decodeStream(input);
	        return myBitmap;
	    } catch (IOException e) {
	        e.printStackTrace();
	        return null;
	    }
	}
	
	public int getPayDialogHintId(){
		return 0;
	}
}
