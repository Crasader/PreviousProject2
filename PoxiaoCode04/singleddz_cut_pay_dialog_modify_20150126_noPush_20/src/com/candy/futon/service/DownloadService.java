package com.candy.futon.service;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;

import com.andy.canvasgame.service.GameConstantsService;
import com.candy.futon.GamePackageInfo;
import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.domain.AppUpdateInfo;

public class DownloadService extends Service {

	private final static String TAG = "DownloadService";
	
	private static DownloadService instance;
	
	public final static GamePackageInfo[] PROMOTE_GAMES = new GamePackageInfo[]{
		GamePackageInfo.DDZ, GamePackageInfo.ERMJ
	};
	
	
	
	private UpgradeService upgradeServices[] = new UpgradeService[PROMOTE_GAMES.length];
	
	private AppUpdateInfo appInfos[] = new AppUpdateInfo[PROMOTE_GAMES.length];
	
	private DownloadEventListener listeners[] = new DownloadEventListener[PROMOTE_GAMES.length];
	
	public static String BROADCAST_NOT_AVALIABLE = "com.wei.andy.futonddz.service.download_not_avaliable";
	
	public static String BROADCAST_DOWNLOAD_PROGRESS = "com.wei.andy.futonddz.service.download_progress";
	
	public static String BROADCAST_DOWNLOAD_COMPLETE = "com.wei.andy.futonddz.service.download_complete";
	
	public static String BROADCAST_START_DOWNLOAD = "com.wei.andy.futonddz.service.download_start";
	
	public static String BROADCAST_DOWNLOAD_ERROR = "com.wei.andy.futonddz.service.download_error";
	
	public static String BUNDLE_EXTRA_PROGRESS_KEY = "progress_key";
	
	public static String BUNDLE_EXTRA_GAME_INDEX_KEY = "game_index_key";
	
	public static String BUNDLE_EXTRA_GAME_SAVE_TO = "game_save_to_key";
	
	private boolean quitWhenAllFinish = false;
	
	private int getUpgradeServiceIndexByGamePackageInfo(GamePackageInfo gamePackInfo){
		for(int i=0;i<PROMOTE_GAMES.length;i++){
			if(PROMOTE_GAMES[i] == gamePackInfo){
				return i;
			}
		}
		throw new IllegalArgumentException();
	}
	
	public class LocalDownloadServiceBinder extends Binder{
		public DownloadService getService(){
			instance = DownloadService.this;
			return DownloadService.this;
		}
	}
	
	public static DownloadService getInstance(){
		return instance;
	}
	
	private final IBinder mBinder = new LocalDownloadServiceBinder();
	
	@Override
	public IBinder onBind(Intent arg0) {
		return mBinder;
	}
	
	@Override
	public void onCreate() {
		super.onCreate();
		IFutonDdzApplication application = (IFutonDdzApplication)getApplication();
		BROADCAST_DOWNLOAD_COMPLETE = application.getPromoteDownloadCompleteString();
		BROADCAST_DOWNLOAD_PROGRESS = application.getPromoteDownloadProgressString();
		BROADCAST_NOT_AVALIABLE = application.getPromoteNotAvaliableString();
		BROADCAST_DOWNLOAD_ERROR = application.getPromoteDownloadErrorString();
		BROADCAST_START_DOWNLOAD = application.getPromoteDownloadStartString();
		Log.i(TAG,"start download service");
		
	}
	
	public boolean isInProgress(GamePackageInfo gameInfo){
		int index = getUpgradeServiceIndexByGamePackageInfo(gameInfo);
		return upgradeServices[index] != null;
	}
	
	public int getCurrentProgress(int index){
		if(listeners[index] != null){
			return listeners[index].getProgress();
		}
		return 0;
	}
	
	/**
	 * 是否还有后台下载
	 * @return
	 */
	public boolean isInProgress(){
		for(GamePackageInfo gameInfo: PROMOTE_GAMES){
			if(isInProgress(gameInfo)){
				return true;
			}
		}
		return false;
	}
	
	public void stopDownload(int index) {
		upgradeServices[index].stop();
	}
	
	private AppUpdateInfo buildAppUpdateInfo(int gameId, int version) {
		AppUpdateInfo tempInfo = new AppUpdateInfo();
		tempInfo.gameId = gameId;
		tempInfo.appVer = String.valueOf(version);
		tempInfo.url="http://111.1.17.140:8186/cr.do";
		tempInfo.entryId = GameConstantsService.getInstance().getEnterId();
		return tempInfo;
	}
	
	/**
	 * 
	 * @param info
	 * @return false if download is already started
	 */
	public boolean downloadGame(GamePackageInfo info) {
		int index = getUpgradeServiceIndexByGamePackageInfo(info);
		if(upgradeServices[index] != null){
			return false;
		}
		appInfos[index] = buildAppUpdateInfo(info.getGameId(), info.getVersion());
		listeners[index] = new DownloadEventListener(index);
		upgradeServices[index] = new UpgradeService(appInfos[index], "Android/data/poxiao_games/download/",  listeners[index]);
		upgradeServices[index].startCheck();
		return true;
	}

	public void setQuitWhenAllFinish(){
		this.quitWhenAllFinish = true;
	}
	
	public void cancelQuitWhenAllFinish(){
		this.quitWhenAllFinish = false;
	}
	
	class DownloadEventListener implements UpgradeEventListener{

		 private int progress; 
		 
		 private int serviceIndex;
		 
		 public DownloadEventListener(int serviceIndex){
			 this.serviceIndex = serviceIndex;
		 }
		 
			@Override
			public void onCheckResult(boolean haveUpgrade, String desc,
					boolean forceUpgrade, long size) {
				if(haveUpgrade){
					Log.i(TAG,appInfos[serviceIndex].gameId + "游戏可以下载");
					Intent intent = new Intent(BROADCAST_START_DOWNLOAD);
					intent.putExtra(BUNDLE_EXTRA_GAME_INDEX_KEY, serviceIndex);
					LocalBroadcastManager.getInstance(getApplicationContext()).sendBroadcast(intent);
					upgradeServices[serviceIndex].startDownload();
				}else{
					Log.i(TAG,appInfos[serviceIndex].gameId + "游戏不可用");
					Intent intent = new Intent(BROADCAST_NOT_AVALIABLE);
					intent.putExtra(BUNDLE_EXTRA_GAME_INDEX_KEY, serviceIndex);
					LocalBroadcastManager.getInstance(getApplicationContext()).sendBroadcast(intent);
					stopDownload(serviceIndex);
					upgradeServices[serviceIndex] = null;
					checkQuitWhenAllFinished();
				}
			}

			protected void checkQuitWhenAllFinished() {
				if(quitWhenAllFinish && !isInProgress()){
					Log.i(TAG, "后台下载完成，进程退出");
					System.exit(0);
				}
			}

			@Override
			public void onError(int errorCode, String errorMsg) {
				Intent intent = new Intent(BROADCAST_DOWNLOAD_ERROR);
				intent.putExtra(BUNDLE_EXTRA_GAME_INDEX_KEY, serviceIndex);
				LocalBroadcastManager.getInstance(getApplicationContext()).sendBroadcast(intent);
				stopDownload(serviceIndex);
				upgradeServices[serviceIndex] = null;
				checkQuitWhenAllFinished();
			}

			@Override
			public void onDownloading(int size) {
				int temp = (int)(size * 100/ (1.0f * appInfos[serviceIndex].size) );
				if(progress == temp){
					return;
				}
				Log.i(TAG,appInfos[serviceIndex].gameId +" 当前已下载"+size+"/"+appInfos[serviceIndex].size);	
				
				progress = temp;
				Intent intent = new Intent();
				intent.setAction(BROADCAST_DOWNLOAD_PROGRESS);
				intent.putExtra(BUNDLE_EXTRA_GAME_INDEX_KEY, serviceIndex);
				intent.putExtra(BUNDLE_EXTRA_PROGRESS_KEY, progress);
				LocalBroadcastManager.getInstance(getApplicationContext()).sendBroadcast(intent);
			}

			@Override
			public void onDownloadComplete() {
				Log.i(TAG,appInfos[serviceIndex].gameId +" 下载完成");
				Intent intent = new Intent(BROADCAST_DOWNLOAD_COMPLETE);
				intent.putExtra(BUNDLE_EXTRA_GAME_INDEX_KEY, serviceIndex);
				intent.putExtra(BUNDLE_EXTRA_GAME_SAVE_TO, appInfos[serviceIndex].saveTo);
				LocalBroadcastManager.getInstance(getApplicationContext()).sendBroadcast(intent);
				stopDownload(serviceIndex);
				upgradeServices[serviceIndex] = null;
				checkQuitWhenAllFinished();
			}

			@Override
			public void onMsg(String msgStr) {
				Log.i(TAG, msgStr);
			}

			@Override
			public void onDownloadInterupted() {
				Intent intent = new Intent(BROADCAST_DOWNLOAD_ERROR);
				intent.putExtra(BUNDLE_EXTRA_GAME_INDEX_KEY, serviceIndex);
				LocalBroadcastManager.getInstance(getApplicationContext()).sendBroadcast(intent);
				stopDownload(serviceIndex);
				upgradeServices[serviceIndex] = null;
				checkQuitWhenAllFinished();
			}
			
			public int getProgress(){
				return progress;
			}
			
		};
		
		
}
