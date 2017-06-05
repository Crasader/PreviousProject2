package com.candy.futon.activitys;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.andy.canvasgame.BaseActivity;
import com.andy.canvasgame.IGameApplication;
import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.service.MusicService;
import com.andy.canvasgame.util.ToastUtil;
import com.candy.futon.GameEngine;
import com.candy.futon.GamePackageInfo;
import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.dialog.BaseDialog;
import com.candy.futon.dialog.ChargeDialog;
import com.candy.futon.dialog.CommonConfirmCancelDialog;
import com.candy.futon.dialog.InputCellPhoneDialog;
import com.candy.futon.dialog.QuitGameDialog;
import com.candy.futon.dialog.SettingDialog;
import com.candy.futon.domain.ChargeConfig;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.domain.PrizePackageType;
import com.candy.futon.receivers.BatteryReceiver;
import com.candy.futon.service.DownloadService;
import com.candy.futon.service.MarqueeUpdater;
import com.candy.futon.service.MarqueeUpdater.MarqueeListener;
import com.candy.futon.view.DdzGameView;
import com.candy.futon.view.PokerView;
import com.candy.futon.widget.CurrentTimeTextViewWidget;
import com.poxiao.ddz.standalone.R;
public abstract class GameActivity extends BaseActivity{

	public final static int MSG_SHOW_GAME_RESULT = 1;
	
	private final static int MSG_UPDATE_TIME = 2;
	
	public final static int MSG_SHOW_SETTING = 3;
	
	public final static int MSG_BACK2LOBBY = 4;
	
	public final static int MSG_SHOW_TOAST = 5;
	
	public final static int MSG_PROMOTE_QUIT = 6;
	
	public final static int MSG_MUST_QUIT = 7;
	
	public final static int MSG_SHOW_START_BTN = 14;
	
	public final static int MSG_SHOW_USER_INFO = 15;
	
	public final static int MSG_SHOW_CHARGE_DIALOG = 16;
	
	public final static int MSG_SHOW_FINAL_PRIZE_DIALOG = 17;
	
	public final static int MSG_ON_ROUND_OVER = 18;
	
	public final static int MSG_B_CARD_REMAINDER = 19;

	public final static int MSG_CONFIRM_BUY_CARD_REMAINDER = 20;
	
	public static final int MSG_CONFIRM_PAY_WHILE_FIRST_LOSE = 21;
	
	protected final static int MSG_CONFIRM_GET_PRIZE_PACKAGE = 22;
	
	public final static int MSG_SHOW_GET_PRIZE_PACKAGE = 23;
	
	public final static int MSG_SHOW_PAY_WHILE_FIRST_LOSE = 24;
	
	public final static int MSG_CANCEL_BUY_CARD_REMAINDER = 25;
	
	public final static int MSG_CANCEL_PAY_WHILE_FIRST_LOSE = 26;
	
	public final static int MSG_CONFIRM_BUY_GOOD_START = 27;
	
	public final static int MSG_SHOW_BUY_GOOD_START = 28;
	
	public final static int MSG_SHOW_PAY_10_YUAN = 29;
	
	public final static int MSG_CONFIRM_PAY_10_YUAN = 30;
	
	public final static int MSG_CANCEL_PAY_10_YUAN = 31;
	
	
	public final static int MSG_SHOW_CONFIRM_DOWNLOAD_GAME_DIALOG = 32;
	
	public final static int MSG_SHOW_CONFIRM_CANCEL_DOWNLOAD_GAME_DIALOG = 33;

	public final static int MSG_CONFIRM_DOWNLOAD_GAME = 34;
	
	public final static int MSG_CONFIRM_CANCEL_DOWNLOAD_GAME = 35;
	
	public final static int MSG_CONFIRM_INSTALL_GAME = 36;
	
	
	public final static int MSG_CHECK_PROMOTE_GAME = 37;

	
	public final static int MSG_CANCEL_BUY_GOOD_START = 38;
	
	public final static int MSG_SHOW_BEG_FOR_PAY_DIALOG = 39;
	
	public final static int MSG_SHOW_BEG_FOR_PAY_AGAIN_DIALOG = 40;
	
	public final static int MSG_CONFIRM_BEG_FOR_PAY = 41;
	
	public final static int MSG_CONFIRM_BEG_AGAIN_PAY = 42;
	

	public static final int MSG_SHOW_USER_FREE_GOOD_START = 43;

	public static final int MSG_CONFIRM_FREE_GOOD_START = 44;
	
	public static final int MSG_CHECK_PAY_DIALOG = 45;
	
	public static final int MSG_FAIL_BEG_PAY = 46;
	
	public static final int MSG_DELAY_FOR_MSG = 47;
	

	private static final int MSG_CHECK_USE_PAUSE_TOO_LONG = 48;
	
	public static final int MSG_SHOW_TASK_REWARD_AND_INPUT_CELL_PHONE = 49;
	
	public static final int MSG_CHECK_MARQUEE = 50;
	
	protected DdzGameView mGameView;
	
	
	private SettingDialog mSettingDialog;
	
	private QuitGameDialog mQuitGameDialog;

	
	
	
	private ChargeDialog mChargeDialog;
	
	private CommonConfirmCancelDialog mConfirmCancelDownLoadDialog;
	
	private CommonConfirmCancelDialog mConfirmDownloadDialog;
	
	private CommonConfirmCancelDialog mConfirmInstallDdzDialog;
	
	private CommonConfirmCancelDialog mConfirmInstallQBSKDialog;
	
	private final static String GAME_RESULT_DIALOG_TAG = "game_result_dialog";
	
	private final static String GAME_SETTING_DIALOG_TAG = "game_setting_dialog";
	
	private final static String QUIT_GAME_DIALOG_TAG = "quit_game_dialog";
	
	protected final static String BUY_CLOSE_DIALOG_TAG = "buy_close_dialog";
	
	private final static String USER_INFO_DIALOG_TAG = "user_info_dialog";
	
	protected static final String PAY_WHILE_FIRST_LOSE_DIALOG_TAG = "pay_while_first_lose_dialog";
	
	protected static final String SHOW_JIUJI_PRIZE_PACAKGE_DIALOG_TAG = "show_jiuji_prize_package_dialog_tag";
	
	protected final static String BUY_CARD_REMAINDER_DIALOG_TAG = "buy_card_remainder_dialog_tag";
	
	protected final static String BUY_GOOD_START_DIALOG_TAG = "buy_good_start_dialog_tag";
	
	protected final static String PAY_10_YUAN_DIALOG_TAG = "pay_10_yuan_dialog_tag";

	private final static String CONFIRM_CANCEL_DOWNLOAD_DIALOG_TAG = "confirm_cancel_download_dialog_tag";
	
	private final static String CONFIRM_DOWNLOAD_DIALOG_TAG = "confirm_download_dialog_tag";
	
	private final static String CONFIRM_INSTALL_DIALOG_TAG = "confirm_install_dialog_tag";
	
	protected final static String BEG_FOR_PAY_DIALOG_TAG = "beg_for_pay_dialog_tag";
	
	protected final static String BEG_FOR_PAY_AGAIN_TAG = "beg_for_pay_again_tag";
	
	private final static String FREE_GOOD_START_DIALOG_TAG = "free_good_start_dialog_tag";
	
	
	private BatteryReceiver batteryReceiver = null;
	
	private CurrentTimeTextViewWidget currentTimeWidget;
	
	private final static long MSG_UPDATE_INTERNAL = 5000;

	
	protected HashMap<String, BaseDialog> dialogMap;
	
	private DownloadBroadCastReceiver receiver;
	
	
	
	private long lastConfirmPayTime = 0;
	
	protected PrizePackageType prizeType;
	
	private static final int USER_PAUSE_TOO_LONG_MILLI = 30 * 1000;
	

	protected InputCellPhoneDialog inputCellPhoneDialog;
	
	protected boolean isDialogShowing = false;
	
	private static GameActivity instance;
	
	class DownloadBroadCastReceiver extends BroadcastReceiver {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if(action.equals(DownloadService.BROADCAST_DOWNLOAD_COMPLETE)){
				int index = intent.getExtras().getInt(DownloadService.BUNDLE_EXTRA_GAME_INDEX_KEY);
				String saveTo = intent.getExtras().getString(DownloadService.BUNDLE_EXTRA_GAME_SAVE_TO);
				showConfirmInstallGameDialog(index, saveTo);
				hideDownloadProgress(index);
			}else if(action.equals(DownloadService.BROADCAST_DOWNLOAD_ERROR)){
				int index = intent.getExtras().getInt(DownloadService.BUNDLE_EXTRA_GAME_INDEX_KEY);
				ToastUtil.resultNotify(GameActivity.this, DownloadService.PROMOTE_GAMES[index].getGameName() +"下载失败，请检查网络后再重试");	
				hideDownloadProgress(index);
				
			}else if(action.equals(DownloadService.BROADCAST_DOWNLOAD_PROGRESS)){
				int index = intent.getExtras().getInt(DownloadService.BUNDLE_EXTRA_GAME_INDEX_KEY);
				int progress = intent.getExtras().getInt(DownloadService.BUNDLE_EXTRA_PROGRESS_KEY);
				GamePackageInfo gameInfo = DownloadService.PROMOTE_GAMES[index];
				GameEngine.getInstance().updateDownloadProgress(gameInfo, progress);
				if(mQuitGameDialog != null){
					mQuitGameDialog.updateDownloadProgress(index, progress);
				}
			}else if(action.equals(DownloadService.BROADCAST_NOT_AVALIABLE)){
				int index = intent.getExtras().getInt(DownloadService.BUNDLE_EXTRA_GAME_INDEX_KEY);
				ToastUtil.resultNotify(GameActivity.this, DownloadService.PROMOTE_GAMES[index].getGameName() +"即将推出，敬请期待");
				hideDownloadProgress(index);
			}else if(action.equals(DownloadService.BROADCAST_START_DOWNLOAD)){
				
			}
		}

		protected void hideDownloadProgress(int index) {
			GameEngine.getInstance().hideDownloadProgress(DownloadService.PROMOTE_GAMES[index]);
			if(mQuitGameDialog != null){
				mQuitGameDialog.hideDownloadProgress(index);
			}
		}

	}

	protected void doGameUpdate(String saveTo) {
		
		if (saveTo != null) {
			Uri data = Uri.parse("file://" + saveTo);
			Intent intent = new Intent(Intent.ACTION_VIEW);
			intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			intent.setDataAndType(data,
					"application/vnd.android.package-archive");
			startActivity(intent);
			
		}
	}

	protected Handler handler = new Handler(){
		public void handleMessage(android.os.Message msg) {
			
			if(msg.what == MSG_SHOW_GAME_RESULT){
				
			}else if(msg.what == MSG_UPDATE_TIME){
				currentTimeWidget.updateTime();
				handler.sendEmptyMessageDelayed(MSG_UPDATE_TIME, MSG_UPDATE_INTERNAL);
			}else if(msg.what == MSG_SHOW_SETTING){
				if(mSettingDialog == null){
					mSettingDialog = new SettingDialog();
					dialogMap.put(GAME_SETTING_DIALOG_TAG, mSettingDialog);
				}
				mSettingDialog.show(getSupportFragmentManager(), GAME_SETTING_DIALOG_TAG);
			}else if(msg.what == MSG_BACK2LOBBY){
				finish();
			}else if(msg.what == MSG_SHOW_TOAST){
				String msgString = (String)msg.obj;
				ToastUtil.resultNotify(GameActivity.this, msgString);
			}else if(msg.what == MSG_PROMOTE_QUIT){
				String tipString = (String)msg.obj;
				showQuitGameDialog(tipString);
			}else if(msg.what == MSG_MUST_QUIT){
				GameActivity.this.finish();
				GameEngine.getInstance().forceQuit();
			}else if(msg.what == MSG_SHOW_START_BTN){
				checkAndShowStartBtnOrGameTip();
			}else if(msg.what == MSG_SHOW_USER_INFO){
				
			}else if(msg.what == MSG_SHOW_CHARGE_DIALOG){
				
				showChargeDialog(msg.arg1 > 0);
			}else if(msg.what == MSG_ON_ROUND_OVER){
				onRoundOver();
			}else if(msg.what == MSG_B_CARD_REMAINDER){
				beforeShowPayDialog();
				onBuyCardRemainder();
			}else if(msg.what == MSG_CONFIRM_BUY_CARD_REMAINDER){
				if(isClickTooQuick()){
					return;
				}
				buyCardRemainder();
			}else if(msg.what == MSG_CONFIRM_PAY_WHILE_FIRST_LOSE){
				if(isClickTooQuick()){
					return;
				}
				payWhileFirstLose();
			}else if(msg.what == MSG_CONFIRM_GET_PRIZE_PACKAGE){
				IFutonDdzApplication application = (IFutonDdzApplication)getApplication();
				application.addCoin2Hero(1000, false);
				GameEngine.getInstance().playGetPrizeAnimation();
			}else if(msg.what == MSG_SHOW_PAY_WHILE_FIRST_LOSE){
				beforeShowPayDialog();
				onPayWhileFirstLose();
			}else if(msg.what == MSG_SHOW_GET_PRIZE_PACKAGE){
				onShowGetPrizePackage();
			}else if(msg.what == MSG_CANCEL_BUY_CARD_REMAINDER){
				buyCardRemainderFail();
			}else if(msg.what == MSG_CANCEL_PAY_WHILE_FIRST_LOSE){
				payWhileFirstLoseFailed();
			}else if(msg.what == MSG_CONFIRM_BUY_GOOD_START){
				if(isClickTooQuick()){
					return;
				}
				buyGoodStart();
			}else if(msg.what == MSG_SHOW_BUY_GOOD_START){
				beforeShowPayDialog();
				onBuyGoodStart();
			}else if(msg.what == MSG_SHOW_PAY_10_YUAN){
				prizeType = null;
				if(msg.obj != null){
					prizeType = (PrizePackageType)msg.obj;
				}
				beforeShowPayDialog();
				onPay10Yuan();
			}else if(msg.what == MSG_CONFIRM_PAY_10_YUAN){
				if(isClickTooQuick()){
					return;
				}
				pay10Yuan();
			}else if(msg.what == MSG_CANCEL_PAY_10_YUAN){
				cancelPay10Yuan();
			}else if(msg.what == MSG_SHOW_CONFIRM_DOWNLOAD_GAME_DIALOG){
				showConfirmDownloadGameDialog(msg.arg1);
			}else if(msg.what == MSG_SHOW_CONFIRM_CANCEL_DOWNLOAD_GAME_DIALOG){
				showConfirmCancelDownloadGameDialog(msg.arg1);
			}else if(msg.what == MSG_CONFIRM_CANCEL_DOWNLOAD_GAME){
				DownloadService.getInstance().stopDownload(msg.arg1);
			}else if(msg.what == MSG_CONFIRM_DOWNLOAD_GAME){
				GamePackageInfo info = DownloadService.PROMOTE_GAMES[msg.arg1];
				boolean success = DownloadService.getInstance().downloadGame(info);
				if(success){
					GameEngine.getInstance().updateDownloadProgress(info, 0);
					if(mQuitGameDialog != null){
						mQuitGameDialog.updateDownloadProgress(msg.arg1, 0);
					}
				}else{
					ToastUtil.resultNotify(GameActivity.this, info.getGameName() +"下载失败，请检查网络后再重试");
				}
			}else if(msg.what == MSG_CONFIRM_INSTALL_GAME){
				doGameUpdate((String)msg.obj);
			}else if(msg.what == MSG_CHECK_PROMOTE_GAME){
				
				
				onCheckPromoteGame(msg);
				
				
			}else if(msg.what == MSG_CANCEL_BUY_GOOD_START){
				buyGoodStartFail();
			}else if(msg.what == MSG_SHOW_BEG_FOR_PAY_DIALOG){
				beforeShowPayDialog();
				showBegForPayDialog();
			}else if(msg.what == MSG_SHOW_BEG_FOR_PAY_AGAIN_DIALOG){
				beforeShowPayDialog();
				showBegForPayDialogAgain();
			}else if(msg.what == MSG_CONFIRM_BEG_FOR_PAY){
				if(isClickTooQuick()){
					return;
				}
				onPayForBeg();
			}else if(msg.what == MSG_CONFIRM_BEG_AGAIN_PAY){
				if(isClickTooQuick()){
					return;
				}
				onPayForBegAgain();
			}else if(msg.what == MSG_SHOW_USER_FREE_GOOD_START){
				showFreeGoodStartDialog();
			}else if(msg.what == MSG_CONFIRM_FREE_GOOD_START){
				onConfirmFreeGoodStart();
			}else if(msg.what == MSG_CHECK_PAY_DIALOG){
				checkPayDialogs();
			}else if(msg.what == MSG_FAIL_BEG_PAY){
				payForBegFail();
			}else if(msg.what == MSG_DELAY_FOR_MSG){
				int msgId = msg.arg1;
				handler.sendEmptyMessageDelayed(msgId, 1000);
			}else if(msg.what == MSG_CHECK_USE_PAUSE_TOO_LONG){
				if(GameEngine.getInstance().usePauseToolong(USER_PAUSE_TOO_LONG_MILLI)){
					if(isDialogNotShowing() ){
						prizeType = PrizePackageType.KENG_PLAYER_PAUSE;
						onPay10Yuan();
					}
					
				}
				handler.sendEmptyMessageDelayed(MSG_CHECK_USE_PAUSE_TOO_LONG, 5000);
			}else if(msg.what == MSG_SHOW_TASK_REWARD_AND_INPUT_CELL_PHONE){
				ToastUtil.resultNotify(instance, "恭喜你，打开宝箱，获赠3000银币，还可上传手机号码抽大奖！");
				IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)getApplication();
				futonDdzApplication.addCoin2Hero(3000);
				showInputCellPhoneDialog();
			}else if(msg.what == MSG_CHECK_MARQUEE){
				MarqueeUpdater.getInstance().update(GameActivity.this);
				handler.sendEmptyMessageDelayed(MSG_CHECK_MARQUEE, 30 * 10000);
			}
		}

		
		

		
	};
	
	protected void showInputCellPhoneDialog(){
		if(inputCellPhoneDialog == null){
			inputCellPhoneDialog = new InputCellPhoneDialog();
		}
		inputCellPhoneDialog.show(getSupportFragmentManager(), InputCellPhoneDialog.TAG);
	}
	
	private boolean isDialogNotShowing() {
		if(isDialogShowing){
			return false;
		}
		return true;
	}
	
	protected void showQuitGameDialog(String tipString) {
		if(mQuitGameDialog == null){
			mQuitGameDialog = new QuitGameDialog();
			mQuitGameDialog.setMsgs(handler.obtainMessage(MSG_MUST_QUIT),null, handler.obtainMessage(MSG_CHECK_PROMOTE_GAME));
			dialogMap.put(QUIT_GAME_DIALOG_TAG, mQuitGameDialog);
		}
		mQuitGameDialog.setTipString(tipString);
		mQuitGameDialog.show(getSupportFragmentManager(), QUIT_GAME_DIALOG_TAG);
	}

	protected boolean isClickTooQuick() {
		long currentTime = System.currentTimeMillis();
		if(currentTime - lastConfirmPayTime < GameConfig.getInstance().payMinJiange){
			ToastUtil.resultNotify(this, "您点击得太快了，休息一下吧");
			return true;
		}
		lastConfirmPayTime = currentTime;
		return false;
	}

	protected void beforeShowPayDialog() {
		// TODO Auto-generated method stub
		
	}

	protected void payForBegFail() {
		handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
	}

	protected void onConfirmFreeGoodStart() {
		handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
		GameConfig.getInstance().giveUserFreeGoodStart = true;
		goodStartBuyed(1 + GameConfig.getInstance().getRemaindGoodStartCount());
	}

	protected void showFreeGoodStartDialog() {
		
	}

	protected abstract void onPayForBegAgain();

	protected abstract void onPayForBeg();

	protected void showBegForPayDialogAgain() {
		
	}

	protected void showBegForPayDialog() {
		
	}

	protected void onCheckPromoteGame(android.os.Message msg) {
		int index = msg.arg1;
		GamePackageInfo gameInfo = DownloadService.PROMOTE_GAMES[msg.arg1];
		
		Intent intent = getPackageManager().getLaunchIntentForPackage(gameInfo.getPackageName());
		if(intent == null){
			if(DownloadService.getInstance().isInProgress(gameInfo)){
				Message newMsg = handler.obtainMessage(GameActivity.MSG_SHOW_CONFIRM_CANCEL_DOWNLOAD_GAME_DIALOG, index, 0);
				newMsg.sendToTarget();
			}else{
				Message newMsg = handler.obtainMessage(GameActivity.MSG_SHOW_CONFIRM_DOWNLOAD_GAME_DIALOG, index, 0);
				newMsg.sendToTarget();
			}
		}else{
			startActivity(intent);
			if(GameConfig.getInstance().quitWhenLaunchPromote){
				finish();
				GameEngine.getInstance().doQuitGame();
			}
		}
	}
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		if(GameConstantsService.getInstance() == null){
			this.finish();
			return;
		}
		instance = this;
		
		PokerView.initDrawables(getResources());
		setContentView(R.layout.activity_game);
		mGameView = (DdzGameView)findViewById(R.id.gameView);
		
		
		GameEngine.getInstance().init(this, mGameView, handler);
		
		playNormalBgMusic();
		initTimeAndBattery();
		
		IntentFilter filter=new IntentFilter(); 
		filter.addAction(DownloadService.BROADCAST_DOWNLOAD_COMPLETE);
		filter.addAction(DownloadService.BROADCAST_DOWNLOAD_ERROR);
		filter.addAction(DownloadService.BROADCAST_DOWNLOAD_PROGRESS);
		
		filter.addAction(DownloadService.BROADCAST_NOT_AVALIABLE);
		filter.addAction(DownloadService.BROADCAST_START_DOWNLOAD);
		receiver = new DownloadBroadCastReceiver();
		LocalBroadcastManager.getInstance(this).registerReceiver(receiver, filter);
		this.mGameView.getViewRoot().invalidate();
		
		
		Object object = getLastCustomNonConfigurationInstance();
		if(object != null){
			this.dialogMap = (HashMap<String, BaseDialog>)object;
		}else{
			this.dialogMap = new HashMap<String, BaseDialog>();
		}
		restoreDialogs();
		
		
		MarqueeUpdater.getInstance().setListener(new MarqueeListener() {
			
			@Override
			public void onUpdate() {
				GameEngine.getInstance().updateMarquee();
			}
		});
		handler.sendEmptyMessage(MSG_CHECK_MARQUEE);
		
	}

	protected void playNormalBgMusic() {
		IGameApplication application = (IGameApplication)getApplication();
		if(assetExists(getAssets(), "musics/normal.ogg")){
			application.playMusicLoop(new String[]{"normal.ogg"});
		}else{
			application.playMusicLoop(new String[]{"normal.mp3"});
		}
	}
	
	protected static boolean assetExists(AssetManager assets, String name) {
	    try {
	        // using File to extract path / filename
	        // alternatively use name.lastIndexOf("/") to extract the path
	        File f = new File(name);
	        String parent = f.getParent();
	        if (parent == null) parent = "";
	        String fileName = f.getName();
	        // now use path to list all files
	        String[] assetList = assets.list(parent);
	        if (assetList != null && assetList.length > 0) {
	            for (String item : assetList) {
	                if (fileName.equals(item))
	                    return true;
	            }
	        }
	    } catch (IOException e) {
	        // Log.w(TAG, e); // enable to log errors
	    }
	    return false;
	}
	
	protected void showConfirmCancelDownloadGameDialog(int arg1) {
		if(mConfirmCancelDownLoadDialog == null){
			mConfirmCancelDownLoadDialog = new CommonConfirmCancelDialog();
		}
		GamePackageInfo gameInfo = DownloadService.PROMOTE_GAMES[arg1];
		mConfirmCancelDownLoadDialog.setMessage(getString(R.string.promote_cancel_download, gameInfo.getGameName()));
		mConfirmCancelDownLoadDialog.setCloseMsg(null);
		Message msg = handler.obtainMessage(MSG_CONFIRM_CANCEL_DOWNLOAD_GAME);
		msg.arg1 = arg1;
		mConfirmCancelDownLoadDialog.setConfirmMsg(msg);
		mConfirmCancelDownLoadDialog.show(getSupportFragmentManager(), CONFIRM_CANCEL_DOWNLOAD_DIALOG_TAG);
	}

	protected void showConfirmDownloadGameDialog(int arg1) {
		if(mConfirmDownloadDialog == null){
			mConfirmDownloadDialog = new CommonConfirmCancelDialog();
		}
		GamePackageInfo gameInfo = DownloadService.PROMOTE_GAMES[arg1];
		mConfirmDownloadDialog.setMessage(getString(R.string.promote_confirm_download, gameInfo.getGameName()));
		mConfirmDownloadDialog.setCloseMsg(null);
		Message msg = handler.obtainMessage(MSG_CONFIRM_DOWNLOAD_GAME);
		msg.arg1 = arg1;
		mConfirmDownloadDialog.setConfirmMsg(msg);
		mConfirmDownloadDialog.show(getSupportFragmentManager(), CONFIRM_DOWNLOAD_DIALOG_TAG);
	}
	
	protected void showConfirmInstallGameDialog(int arg1, String saveTo){
		if(mConfirmInstallDdzDialog == null){
			mConfirmInstallDdzDialog = new CommonConfirmCancelDialog();
		}
		if(mConfirmInstallQBSKDialog == null){
			mConfirmInstallQBSKDialog = new CommonConfirmCancelDialog();
		}
		
		CommonConfirmCancelDialog dialog = null;
		
		GamePackageInfo gameInfo = DownloadService.PROMOTE_GAMES[arg1];
		if(gameInfo == GamePackageInfo.DDZ){
			dialog = mConfirmInstallDdzDialog;
		}else{
			dialog = mConfirmInstallQBSKDialog;
		}
		dialog.setMessage(getString(R.string.promote_confirm_install, gameInfo.getGameName()));
		dialog.setCloseMsg(null);
		Message msg = handler.obtainMessage(MSG_CONFIRM_INSTALL_GAME);
		msg.obj = saveTo;
		dialog.setConfirmMsg(msg);
		dialog.show(getSupportFragmentManager(), CONFIRM_INSTALL_DIALOG_TAG);
	}

	protected void cancelPay10Yuan() {
		handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
		IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)this.getApplication();
		GameConfig.getInstance().changeGameRoom(futonDdzApplication.getPlayerInfo().getPoint());
	}

	
	protected void pay10YuanSuccess(){
		handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
		IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)this.getApplication();
		futonDdzApplication.addCoin2Hero(50000);
		GameConfig.getInstance().changeGameRoom(futonDdzApplication.getPlayerInfo().getPoint());
		GameConfig.getInstance().payedUser = true;
		GameConfig.getInstance().save(GameActivity.this);
	}

	protected void pay10YuanFail(){
		cancelPay10Yuan();
	}
	
	protected void onBuyCardRemainder() {
		
	}

	protected void onPayWhileFirstLose(){
		
	}
	
	protected void onShowGetPrizePackage(){
		
	}
	
	protected void onBuyGoodStart(){
		

	}
	
	protected void onPay10Yuan(){
		
	}
	
	protected void onRoundOver() {
		
	}

	private void restoreDialogs() {
		mChargeDialog = (ChargeDialog) dialogMap.get(ChargeDialog.TAG);
		if(mChargeDialog != null){
			mChargeDialog.setActivityFailSafe(this);
		}
		
		
		
		
		mQuitGameDialog = (QuitGameDialog)dialogMap.get(QUIT_GAME_DIALOG_TAG);
		if(mQuitGameDialog != null){
			mQuitGameDialog.setActivityFailSafe(this);
		}
		
		mSettingDialog = (SettingDialog)dialogMap.get(GAME_SETTING_DIALOG_TAG);
		if(mSettingDialog!= null){
			mSettingDialog.setActivityFailSafe(this);
		}
		
		
	}

	protected void showChargeDialog(boolean isDefaultChargeConfig) {
		IFutonDdzApplication application = (IFutonDdzApplication)getApplication();
		if(mChargeDialog == null){
			try {
				mChargeDialog = application.getChargeDialogClass().newInstance();
			} catch (InstantiationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			dialogMap.put(ChargeDialog.TAG, mChargeDialog);
		}
		if(isDefaultChargeConfig){
			mChargeDialog.setCurrentChargeConfig(ChargeConfig.getDefaultChargeConfig());
		}else{
			mChargeDialog.setCurrentChargeConfig(null);
		}

		mChargeDialog.setPrefixString("");
		mChargeDialog.show(getSupportFragmentManager(), ChargeDialog.TAG);
	}


	protected boolean isShowGirlSay(){
		return true;
	}

	
	protected void checkAndShowStartBtnOrGameTip() {
		if(!isShowGirlSay()){
			GameEngine.getInstance().doShowStartBtn();
			return;
		}
		
		Log.d("Temp","check and show start btn");
		
		checkAndShowStartBtnOrGameTipInNormalRoom();
		
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		DownloadService.getInstance().cancelQuitWhenAllFinish();
		handler.sendEmptyMessageDelayed(MSG_CHECK_USE_PAUSE_TOO_LONG, 5000);
	}

	

	private void checkAndShowStartBtnOrGameTipInNormalRoom() {
		GameEngine.getInstance().doShowStartBtn();
	}

	

	protected abstract void buyGoodStart();
	
	protected abstract void buyCardRemainder();
	
	protected abstract void payWhileFirstLose();
	
	protected abstract void pay10Yuan();
	
	
	protected void buyCardRemainderSuccess(){
		GameConfig.getInstance().payedUser = true;
		GameConfig.getInstance().cardRemainderBuyed = true;
		GameConfig.getInstance().save(this);
		GameEngine.getInstance().showCardRemainder();
	}
	
	protected void buyCardRemainderFail(){
		GameConfig.getInstance().clearCardRemainderNotPayCount();
		GameConfig.getInstance().save(this);
	}

	protected void payWhileFirstLoseSuccess(){
		GameConfig.getInstance().payedUser = true;
		GameConfig.getInstance().save(GameActivity.this);
		IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)this.getApplication();
		futonDdzApplication.addCoin2Hero(50000);
		GameConfig.getInstance().changeGameRoom(futonDdzApplication.getPlayerInfo().getPoint());
	}

	protected void payForBegSuccess(){

		handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
		GameConfig.getInstance().payedUser = true;
		GameConfig.getInstance().save(GameActivity.this);
		IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)this.getApplication();
		futonDdzApplication.addCoin2Hero(50000);
		GameConfig.getInstance().changeGameRoom(futonDdzApplication.getPlayerInfo().getPoint());
	}
	
	protected void payWhileFirstLoseFailed(){
		
	}

	protected void buyGoodStartSuccess(){
		handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
		GameConfig.getInstance().buyGoodStart = true;
		goodStartBuyed(50);
	}

	protected void goodStartBuyed(int count) {
		
		GameConfig.getInstance().setGoodStartCount(GameConfig.getInstance().getRemaindGoodStartCount() + count);
		GameConfig.getInstance().payedUser = true;
		GameConfig.getInstance().save(this);
		GameEngine.getInstance().updateGoodStartNumber();
	}
	
	protected void buyGoodStartFail(){
		handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
	}

	
	

	private void initTimeAndBattery() {
		ProgressBar progressBar = (ProgressBar) this.findViewById(R.id.progress_bettery);
		currentTimeWidget = new CurrentTimeTextViewWidget((TextView)findViewById(R.id.text_view_current_time));
		currentTimeWidget.updateTime();
		batteryReceiver = new BatteryReceiver(progressBar);
		IntentFilter batteryLevelFilter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		batteryLevelFilter.addAction(Intent.ACTION_POWER_CONNECTED);
		batteryLevelFilter.addAction(Intent.ACTION_POWER_DISCONNECTED);
		
        registerReceiver(batteryReceiver, batteryLevelFilter);
        handler.sendEmptyMessageDelayed(MSG_UPDATE_TIME, MSG_UPDATE_INTERNAL);
	}
	
	
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		if(mGameView != null){
			mGameView.getViewRoot().destroy();
		}
		if(batteryReceiver != null){
			unregisterReceiver(batteryReceiver);
		}
		if(receiver != null){
			LocalBroadcastManager.getInstance(getApplicationContext()).unregisterReceiver(receiver);
		}
		if(handler!= null){
			handler.removeMessages(MSG_UPDATE_TIME);
		}
	}
	
	
	@Override
	public void onBackPressed() {
		GameEngine.getInstance().onBack2Lobby();
	}
	
	@Override
	public Object onRetainCustomNonConfigurationInstance() {
		
		return dialogMap;
	}
	
	@Override
	protected void onPause() {
		isResumed = false;
		super.onPause();
		sendBroadcast(new Intent(MusicService.MUSIC_DISABLED));
		
		handler.removeMessages(MSG_CHECK_USE_PAUSE_TOO_LONG);
	}

	protected void checkPayDialogs() {
		if(GameConfig.getInstance().payDialogIds == null || GameConfig.getInstance().payDialogIds.isEmpty()){
			return;
		}
		handler.sendEmptyMessage(GameConfig.getInstance().payDialogIds.remove(0));
	}
	
	public static GameActivity getInstance() {
		return instance;
	}
	
}
