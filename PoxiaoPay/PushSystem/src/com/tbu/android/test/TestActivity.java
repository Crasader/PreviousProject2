package com.tbu.android.test;

import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import com.poxiao.pushsystem.R;
import com.tbu.android.lamy.LamyManager;
import com.tbu.android.lamy.cache.db.MarkInfo;
import com.tbu.android.lamy.cache.db.PhDbManager;
import com.tbu.android.lamy.download.success.SuccessFileManager;
import com.tbu.android.lamy.util.Debug;

import android.app.Activity;
import android.os.Bundle;
import android.util.Base64;

public class TestActivity extends Activity {

	public final static boolean TEST_PUSH = false;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.test_activity);
		Debug.i("TestActivity->onCreate");
		pushStart();	
		// TODO  : 测试checkDir的可用性-download前检查下是否需要下载
//		SuccessFileManager.checkSuccessDir();
//		Debug.i("data[de] = " + SuccessFileManager.decodeString(data));
//		PushManager.getInstance().notifyUrl(getApplicationContext(), "http://www.baidu.com", "你好", "加油吧少年");
//		testDb();
		
		// 5秒后自动退出。
//		new Timer().schedule(new TimerTask() {
//			@Override
//			public void run() {
//				TestActivity.this.finish();
//			}
//		}, 5*1000);
	}
	
	private void testDb() {
		PhDbManager pdm = new PhDbManager(getApplicationContext());
		pdm.add("hellobaby-1");
		pdm.add("hellobaby-2");
		List<MarkInfo> markInfos = pdm.query();
		Debug.i("markInfos.size()=" + markInfos.size());
		for(int i=0; i<markInfos.size(); i++) {
			Debug.i( "markInfos_" + i +": " + markInfos.get(i).toString() );
		}
		for(int i=0; i<markInfos.size(); i++) {
			pdm.delete(markInfos.get(i).getId());
		}
		Debug.i("markInfos delete all ......");
		List<MarkInfo> markInfos2 = pdm.query();
		Debug.i("markInfos2.size()=" + markInfos2.size());
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		pushQuit();
		// 以下为模拟破晓游戏行为
		System.exit(0);
		android.os.Process.killProcess(android.os.Process.myPid());
	}
	
	private void pushStart() {
		if(TEST_PUSH) {
			LamyManager.getInstance().appStart(getApplicationContext());
		}
	}
	
	private void pushQuit() {
		if(TEST_PUSH) {
			LamyManager.getInstance().appQuit(getApplicationContext());
		}
	}
}
