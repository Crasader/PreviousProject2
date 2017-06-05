package com.candy.futon.activitys;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.FragmentActivity;
import android.util.Log;

import com.andy.canvasgame.service.GameConstantsService;
import com.candy.futon.GameEngine;
import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.dialog.CommonConfirmCancelDialog;
import com.candy.futon.domain.AppUpdateInfo;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.domain.GameRoom;
import com.candy.futon.service.UpgradeService;
import com.poxiao.ddz.standalone.R;

public class SplashActivity extends FragmentActivity {

	private final static String TAG = "SplashActivity";
	
	protected final static int MSG_START_LOBBY = 1;
	
	private final static int MSG_CHECK_SERVICE_STATUS = 2;
	
	private final static int MSG_CHECK_AND_ENTER_GAME = 3;
	
	private final static int MSG_CHECK_START_UP_LOG_UPDATE_PROGRESS = 4;
	
	protected final static long MIN_SHOW_SPLASH_TIME_MILLI = 1500;
	
	protected AppUpdateInfo mAppInfo;
	private UpgradeService mService;
	private final static String DIALOG_SHOW_ERROR = "dialog_show_error";
	private final static String DIALOG_SHOW_UPDATE = "dialog_show_update";
	private CommonConfirmCancelDialog dialogShowError;
	private CommonConfirmCancelDialog dialogShowUpdate;
	
	
	protected long startupTimeMills;
	
	protected Handler mHandler = new Handler(){
		
		@Override
		public void dispatchMessage(android.os.Message msg) {
			if(msg.what == MSG_START_LOBBY){
				doEnterGame();
			}else if(msg.what == MSG_CHECK_SERVICE_STATUS){
				if(GameConstantsService.getInstance() != null){
					
					
					doEnterGame();
				}else{
					mHandler.sendEmptyMessageDelayed(MSG_CHECK_SERVICE_STATUS, 10);
				}
			}else if(msg.what == MSG_CHECK_AND_ENTER_GAME){
				checkAndEnterGame();
			}else if(msg.what == MSG_CHECK_START_UP_LOG_UPDATE_PROGRESS){
				Log.d(TAG,"quit game");
				quitGame();
				
			}
			
		}

		
		
	};
	
	protected void doEnterGame() {
		
		IFutonDdzApplication application = (IFutonDdzApplication)getApplication();
		GameRoom gameRoom = GameConfig.getInstance().getGameRoomWhenStart(application.getPlayerInfo().getPoint());
		
		GameEngine.getInstance().setGameRoom(gameRoom);
		Intent intent = new Intent(this, application.getGameActivityClass());
		startActivity(intent);
		finish();
	};
	
	protected void quitGame() {
		finish();
		System.exit(0);
	}

	
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		this.startupTimeMills = System.currentTimeMillis();
		
		mHandler.sendEmptyMessageDelayed(MSG_CHECK_SERVICE_STATUS, 50);
		overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out);
	}
	
	

	@Override
	public void onBackPressed() {
		mHandler.sendEmptyMessageDelayed(MSG_CHECK_START_UP_LOG_UPDATE_PROGRESS, 10);
	}
	
	 private AppUpdateInfo buildAppUpdateInfo() {
			AppUpdateInfo tempInfo = new AppUpdateInfo();
			IFutonDdzApplication futonApplication = (IFutonDdzApplication)getApplication();
			tempInfo.gameId = futonApplication.getGameId();
			tempInfo.appVer = String.valueOf(GameConstantsService.getInstance().getVersionNameInt());
			tempInfo.url="http://111.1.17.140:8186/su.do";
			tempInfo.entryId = GameConstantsService.getInstance().getEnterId();
			return tempInfo;
		}
	
	
	 
	

	protected void checkAndEnterGame() {
		
		long timeMills = System.currentTimeMillis() - startupTimeMills ;
		if(timeMills > MIN_SHOW_SPLASH_TIME_MILLI){
			doEnterGame();
		}else{
			mHandler.sendEmptyMessageDelayed(MSG_START_LOBBY, MIN_SHOW_SPLASH_TIME_MILLI - timeMills);
		}
	}

	@Override
	protected void onResume() {
		super.onResume();
		mHandler.removeMessages(MSG_CHECK_START_UP_LOG_UPDATE_PROGRESS);
	}
}
