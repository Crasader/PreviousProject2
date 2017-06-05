package com.candy.futon.domain;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Build;

import com.poxiao.ddz.standalone.R;

public class PlayerInfo {

	public final static int DEFAULT_POINT = 3000;
	
	public final static int ROBOT_DEFAULT_POINT = 10000;
	
	private final static String PREF_NAME = "playerinfo";
	
	private final static String WIN_KEY = "win";
	
	private final static String LOSE_KEY = "lose";
	
	private final static String POINT_KEY = "point";
	
	private final static String GENDER_KEY = "gender";
	
	private final static String HERO_NICKNAME_KEY = "heronickname";
	
	private String nickName;
	
	private int win;
	
	private int lose;
	
	private boolean gender;
	
	private int point;
	
	private int headDrawId;

	public String getNickName() {
		return nickName;
	}

	public void setNickName(String nickName) {
		this.nickName = nickName;
	}

	public int getWin() {
		return win;
	}

	public void setWin(int win) {
		this.win = win;
	}

	public int getLose() {
		return lose;
	}

	public void setLose(int lose) {
		this.lose = lose;
	}

	public int getPoint() {
		return point;
	}

	public void setPoint(int point) {
		this.point = point;
	}

	public void setGender(boolean gender) {
		this.gender = gender;
	}
	
	public boolean isMale(){
		return this.gender == true;
	}
	
	public static String getHeroNickName(Context context){
		SharedPreferences settings = context.getSharedPreferences(PREF_NAME, 0);
		String nickName = settings.getString(HERO_NICKNAME_KEY, null);
		if(nickName ==  null){
			nickName = Build.MODEL.substring(0, 
					Build.MODEL.length()>=6?6:Build.MODEL.length());
			getPlayerInfoByNickName(context, nickName);
			doSaveHeroNickName(settings.edit(), nickName);
		}
		return nickName;
	}
	
	public static void saveHeroNickName(Context context, String nickName){
		SharedPreferences settings = context.getSharedPreferences(PREF_NAME, 0);
		doSaveHeroNickName(settings.edit(), nickName);
	}
	
	private static void doSaveHeroNickName(Editor editor, String nickName){
		editor.putString(HERO_NICKNAME_KEY, nickName);
		editor.commit();
	}
	
	public static PlayerInfo getPlayerInfoByNickName(Context context, String nickName) {
		return getPlayerInfoByNickName(context, nickName, DEFAULT_POINT);
	}
	
	public static PlayerInfo getRobotPlayerInfoByNickName(Context context, String nickName){
		return getPlayerInfoByNickName(context, nickName, ROBOT_DEFAULT_POINT);
	}
	
	private static PlayerInfo getPlayerInfoByNickName(Context context, String nickName, int defaultPoint){
		SharedPreferences settings = context.getSharedPreferences(PREF_NAME, 0);
		PlayerInfo info = new PlayerInfo();
		info.setNickName(nickName);
		info.setGender(settings.getBoolean(nickName + GENDER_KEY, true));
		info.setLose(settings.getInt(nickName + LOSE_KEY, 0));
		info.setWin(settings.getInt(nickName + WIN_KEY, 0));
		info.setPoint(settings.getInt(nickName + POINT_KEY, defaultPoint));
		if(!settings.contains(nickName + GENDER_KEY)){
			doSavePlayInfo(settings.edit(), info);
		}
		return info;
	}
	
	public static PlayerInfo getHeroPlayer(Context context){
		PlayerInfo hero = getPlayerInfoByNickName(context, getHeroNickName(context));
		hero.setHeadDrawId(R.drawable.head_hero);
		return hero;
	}

	private static void doSavePlayInfo(Editor edit, PlayerInfo info) {
		edit.putBoolean(info.getNickName() + GENDER_KEY, info.isMale());
		edit.putInt(info.getNickName() + LOSE_KEY, info.getLose());
		edit.putInt(info.getNickName() + WIN_KEY, info.getWin());
		edit.putInt(info.getNickName() + POINT_KEY, info.getPoint());
		edit.commit();
	} 
	
	public static void savePlayerInfo(Context context, PlayerInfo info){
		SharedPreferences settings = context.getSharedPreferences(PREF_NAME, 0);
		doSavePlayInfo(settings.edit(), info);
	}
	
	@Override
	public String toString() {
		return this.nickName + (this.isMale()?"男":"女") + " win:" + this.win + " lose:" + this.lose + " point:"+ this.point;
	}

	public int getHeadDrawId() {
		return headDrawId;
	}

	public void setHeadDrawId(int headDrawId) {
		this.headDrawId = headDrawId;
	}
	
	
}
