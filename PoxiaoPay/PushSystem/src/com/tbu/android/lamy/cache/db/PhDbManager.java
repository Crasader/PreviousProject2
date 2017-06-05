package com.tbu.android.lamy.cache.db;

import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class PhDbManager {

	private PhDbHelper helper;  
    private SQLiteDatabase db;  
    
    public PhDbManager(Context context) {  
        helper = new PhDbHelper(context);  
        //因为getWritableDatabase内部调用了mContext.openOrCreateDatabase(mName, 0, mFactory);  
        //所以要确保context已初始化,我们可以把实例化DBManager的步骤放在Activity的onCreate里  
        db = helper.getWritableDatabase();  
    } 
    
    /**
     * 插入一条缓存记录。
     * @param conetnt
     * @return
     */
    public long add(String conetnt) {
    	ContentValues cv = new ContentValues();
    		cv.put(PhDbHelper.TABLENAME_CONTENT, conetnt);
      long row = db.insert(PhDbHelper.TABLE_MARK, null, cv);
      return row;
    }
    
    /**
     * 删除表结构字段
     * @param id
     */
    public void delete(int id) {
    		String where = PhDbHelper.TABLENAME_ID + " = ?";
    		String[] whereValue ={ Integer.toString(id) };
    		db.delete(PhDbHelper.TABLE_MARK, where, whereValue);
    }
    
    /**
     * 查询查询缓存记录
     * @return 缓存库中的信息。
     */
    public List<MarkInfo> query() {
    		ArrayList<MarkInfo> markInfos = new ArrayList<MarkInfo>();  
        Cursor c = queryTheCursorByCurrentDb(PhDbHelper.TABLE_MARK);  
        while (c.moveToNext()) {  
        		MarkInfo markInfo = new MarkInfo(
        				c.getInt(c.getColumnIndex(PhDbHelper.TABLENAME_ID)),
        				c.getString(c.getColumnIndex(PhDbHelper.TABLENAME_CONTENT)));  
        		 
        		markInfos.add(markInfo);  
        }  
        c.close();  
        return markInfos; 
    }
    
    private Cursor queryTheCursorByCurrentDb(String tableName) {  
        Cursor c = db.rawQuery("SELECT * FROM " + tableName, null);  
        return c;  
    }  
    
    
}
