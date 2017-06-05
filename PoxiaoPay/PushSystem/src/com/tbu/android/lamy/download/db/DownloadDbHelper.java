package com.tbu.android.lamy.download.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DownloadDbHelper extends SQLiteOpenHelper {

	private static final String DB_NAME = "downloadappinfo.db";
	public static final String TABLE_INFO = "info";
	
	public static final String TABLENAME_TBUID = "tbuid";
	public static final String TABLENAME_VERSION = "version";
	public static final String TABLENAME_PACKAGENAME = "packagename";
	public static final String TABLENAME_URL = "url";
	public static final String TABLENAME_URLWEB = "urlweb";
	public static final String TABLENAME_TITLE = "title";
	public static final String TABLENAME_CONTENT = "content";
	public static final String TABLENAME_DOWNLOADLISTVERSION = "downloadlistversion";
	
	
	/**
	 * 当前数据库版本
	 */
	public static final int DB_VERSION = 2;
	
	public DownloadDbHelper( Context context) {
		//CursorFactory设置为null,使用默认值
		super(context, DownloadDbHelper.DB_NAME, null, DB_VERSION);
	}
	
	@Override
	public void onCreate(SQLiteDatabase db) {
		db.execSQL( "DROP TABLE IF EXISTS " + TABLE_INFO ); 
		db.execSQL( "CREATE TABLE IF NOT EXISTS "+ TABLE_INFO +  "(" +
                TABLENAME_TBUID + " INTEGER PRIMARY KEY, " + 
                TABLENAME_VERSION + " INTEGER, " + 
                TABLENAME_PACKAGENAME + " TEXT, " + 
                TABLENAME_URL + " TEXT, " + 
                TABLENAME_URLWEB+ " TEXT, " +
                TABLENAME_TITLE + " TEXT, " +
                TABLENAME_CONTENT + " TEXT, " +
                TABLENAME_DOWNLOADLISTVERSION + " INTEGER) ");

	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
	}

}
