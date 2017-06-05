package com.tbu.android.lamy.cache.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class PhDbHelper extends SQLiteOpenHelper {

	private static final String DB_NAME = "push.db";
	public static final String TABLE_MARK = "mark";
	
	public static final String TABLENAME_CONTENT = "content";
	public static final String TABLENAME_ID = "id";
	
	/**
	 * 当前数据库版本
	 */
	public static final int DB_VERSION = 1;
	
	public PhDbHelper( Context context) {
		//CursorFactory设置为null,使用默认值
		super(context, PhDbHelper.DB_NAME, null, DB_VERSION);
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		db.execSQL( "DROP TABLE IF EXISTS " + PhDbHelper.TABLE_MARK ); 
		db.execSQL( "CREATE TABLE IF NOT EXISTS "+ PhDbHelper.TABLE_MARK +  
                "(" + TABLENAME_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " + TABLENAME_CONTENT + " TEXT)" );

	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
	}

}
