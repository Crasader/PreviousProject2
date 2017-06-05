package com.candy.futon.ai.log;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import android.util.Log;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.pokergames.ddz.ai.ddzai.log.ILog;
import com.candy.futon.FutonDdzApplication;

public class AIFileLog implements ILog {

	private StringBuilder buffer = new StringBuilder();
	
	private final static String TAG = "AILOG";
	
	private final static String LOG_FILE = "ai.log";
	
	@Override
	public void d(String msg) {
		buffer.append(msg);
		buffer.append("\r\n");
		Log.d(TAG, msg);
	}

	@Override
	public void i(String msg) {
		buffer.append(msg);
		buffer.append("\r\n");
		Log.i(TAG, msg);
	}

	@Override
	public void w(String msg) {
		buffer.append(msg);
		buffer.append("\r\n");
		Log.w(TAG, msg);
	}

	@Override
	public void e(String msg) {
		buffer.append(msg);
		buffer.append("\r\n");
		Log.e(TAG, msg);
	}

	@Override
	public void f(String msg) {
		buffer.append(msg);
		buffer.append("\r\n");
		Log.e(TAG, msg);
	}

	public void flush2File(){
		String logFlag = (String) GameConstantsService.getInstance().getProperties().get(FutonDdzApplication.AI_LOG_KEY);
		if(logFlag == null || !logFlag.trim().equalsIgnoreCase("true")){
			buffer = new StringBuilder();
			return;
		}
		
		FileWriter fw = null;
		try {
			fw = new FileWriter(GameConstantsService.getInstance().getGameFolderPath() + File.separator + LOG_FILE, true);
			fw.write(buffer.toString());
			fw.write("\r\n");
			fw.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally{
			buffer = new StringBuilder();
			if(fw != null){
				try {
					fw.close();
				} catch (IOException e) {
				}
			}
		}
		
	}
	
	@Override
	public boolean isDebugEnabled() {
		//TODO
		return true;
	}

	@Override
	public boolean isInfoEnabled() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean isWarnEnabled() {
		// TODO Auto-generated method stub
		return true;
	}

}
