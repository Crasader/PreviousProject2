package com.tbu.android.lamy.cache;

import java.util.List;

import com.tbu.android.lamy.LamyConfig;
import com.tbu.android.lamy.cache.db.MarkInfo;
import com.tbu.android.lamy.cache.db.PhDbManager;
import com.tbu.android.lamy.event.EventReceiver;
import com.tbu.android.lamy.server.ServerManager;
import com.tbu.android.lamy.server.domain.PhTable;
import com.tbu.android.lamy.util.Debug;
import com.tbu.android.lamy.util.SessionUtil;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;

public class CacheManager {

	/**
	 * 检查是否需要异步更新。
	 * 
	 * @param context
	 */
	public static void checkNeedSync ( final Context context ) {
		final PhDbManager pdm = new PhDbManager(context);
		List<MarkInfo> markInfos = pdm.query();
		Debug.i("CacheManager->checkNeedSync, markInfos.size()=" + markInfos.size());
		if(markInfos.size() > 0) {
			final MarkInfo markInfo = markInfos.get(0);
			new Thread(new Runnable() {
				@Override
				public void run() {
					// 拿返回值，判断是否需要进行下次任务。
					String serverResult = ServerManager.doPost(LamyConfig.POST_MAKR_UL, markInfo.getContent());
					Debug.i("CacheManager->checkNeedSync, serverResult=" + serverResult);
					if("0".equals(serverResult)) {
						pdm.delete(markInfo.getId());
						checkNeedSync(context);
					}else {
						setNext(context);
					}
				}
			}).start();
		}
	}
	
	public static void addNew(final Context context, final String result) {
		PhDbManager pdm = new PhDbManager(context);
		pdm.add(result);
		setNext(context);
	}
	
	private final static int DEFAULT_TIME = 30*1000;//10*60*1000;
	public static void setNext(Context context){
		AlarmManager am = (AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
        Intent alarmIntent = new Intent(context, EventReceiver.class);
        alarmIntent.setAction(EventReceiver.ACTION_SYNC);
        PendingIntent pIntent = PendingIntent.getBroadcast(context, SessionUtil.getAlarmId(context), alarmIntent, 0);
        
        am.set(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + DEFAULT_TIME, pIntent);
        Debug.i("CacheManager->setNextReqServerTime at(from now) : " + DEFAULT_TIME);
	}
}
