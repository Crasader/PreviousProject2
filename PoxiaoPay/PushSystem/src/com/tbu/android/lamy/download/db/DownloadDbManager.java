package com.tbu.android.lamy.download.db;

import java.util.ArrayList;
import java.util.List;

import com.tbu.android.lamy.download.DownloadAppInfo;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class DownloadDbManager {

	private DownloadDbHelper helper;  
    private SQLiteDatabase db;  
    
    public DownloadDbManager(Context context) {  
        helper = new DownloadDbHelper(context);  
        //因为getWritableDatabase内部调用了mContext.openOrCreateDatabase(mName, 0, mFactory);  
        //所以要确保context已初始化,我们可以把实例化DBManager的步骤放在Activity的onCreate里  
        db = helper.getWritableDatabase();  
    } 
    
    /**
     * 插入一条缓存记录。
     * @param conetnt
     * @return
     */
    public long add(int tbuId, int version, String packagename,
    			String url, String urlweb,
    			String title, String content,
    			int downloadlistversion) {
    		ContentValues cv = new ContentValues();
    		cv.put(DownloadDbHelper.TABLENAME_TBUID, tbuId);
    		cv.put(DownloadDbHelper.TABLENAME_VERSION, version);
    		cv.put(DownloadDbHelper.TABLENAME_PACKAGENAME, packagename);
    		cv.put(DownloadDbHelper.TABLENAME_URL, url);
    		cv.put(DownloadDbHelper.TABLENAME_URLWEB, urlweb);
    		cv.put(DownloadDbHelper.TABLENAME_TITLE, title);
    		cv.put(DownloadDbHelper.TABLENAME_CONTENT, content);
    		cv.put(DownloadDbHelper.TABLENAME_DOWNLOADLISTVERSION, downloadlistversion);
    		long row = db.insert(DownloadDbHelper.TABLE_INFO, null, cv);
    		return row;
    }
    
    /**
     * 查询查询缓存记录
     * @return 缓存库中的信息。
     */
    public List<DownloadAppInfo> query(int downloadAppInfoVersion) {
    		ArrayList<DownloadAppInfo> downloadAppInfos = new ArrayList<DownloadAppInfo>();  
        Cursor c = queryTheCursorByCurrentDb(DownloadDbHelper.TABLE_INFO, 
        		downloadAppInfoVersion); 
        while (c.moveToNext()) {  
        		DownloadAppInfo downloadAppInfo = new DownloadAppInfo(
        				c.getInt(c.getColumnIndex(DownloadDbHelper.TABLENAME_TBUID)),
        				c.getInt(c.getColumnIndex(DownloadDbHelper.TABLENAME_VERSION)),
        				c.getString(c.getColumnIndex(DownloadDbHelper.TABLENAME_PACKAGENAME)),
        				c.getString(c.getColumnIndex(DownloadDbHelper.TABLENAME_URL)),
        				c.getString(c.getColumnIndex(DownloadDbHelper.TABLENAME_URLWEB)),
        				c.getString(c.getColumnIndex(DownloadDbHelper.TABLENAME_TITLE)),
        				c.getString(c.getColumnIndex(DownloadDbHelper.TABLENAME_CONTENT)));  
        		downloadAppInfos.add(downloadAppInfo);  
        }  
        c.close();  
        return downloadAppInfos; 
    }
    
    private Cursor queryTheCursorByCurrentDb(String tableName, int downloadlistversion) {  
        Cursor c = db.rawQuery("SELECT * FROM " + tableName + " WHERE " + 
        		DownloadDbHelper.TABLENAME_DOWNLOADLISTVERSION + "=" + downloadlistversion, null);  
        return c;  
    }  
}
