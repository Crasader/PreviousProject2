package com.candy.futon.domain;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.UUID;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.candy.futon.GameEngine;
import com.candy.futon.IFutonDdzApplication;

public class GameConfig {

	/**
	 * 是否到达过最大底分房间
	 */
	public boolean exceedMaxRoom = false;
	
	/**
	 * 玩家探索过的房间下标
	 */
	public int exploredRoomIndex = 1;
	
	/**
	 * 是否给用户弹出过第一次失败的计费点
	 */
	public boolean firstLoseRevivePayShowed = false;
	
	public boolean firstWin = false;
	
	public boolean firstTimePrize = false;
	
	/**
	 * 上一把弹出过一个礼包，这把就弹付费礼包
	 */
	private boolean oneTimePrizeShowed = false;
	
	/**
	 * 连续弹礼包模式，目前弹出的礼包下标
	 */
	private int prizeIndex = 0;
	
	private final static int MAX_CONTINUS_PRIZE_INDEX = 3;
	
	/**
	 * 发好牌之后，玩家如果胜利的话，弹出的礼包次数
	 */
	public int currentPrizePackageIndex = 0;
	
	
	
	public long currentStartupLogId = 0;
	
	public boolean uploadingStartupLogs = false;
	
	
	
	private String totalRamSize = null;
	
	
	
	public final static String ONLINE_DDZ_PACKAGE_NAME = "com.poxiao.ddz.net";
	
	
	private final static String PREF_TITLE = "GameConfig";
	
	
	
	private final static String KEY_RAM_SIZE = "key_ram_size";
	
	private final static String KEY_CARD_REMAINDER_BUYED = "key_card_remainder_buyed";
	
	private final static String KEY_EXCEED_MAX_ROOM = "key_exceed_max_room";
	
	private final static String KEY_SHOW_FIRST_LOSE_REVIVE_PAY = "key_show_first_lose_revive_pay";
	
	private final static String KEY_SHOW_BUY_PRIZE_PACKAGE = "key_show_buy_prize_package";
	
	private final static String KEY_CURRENT_PRIZE_PACKAGE_INDEX = "key_current_prize_package_index";
	
	private final static String KEY_SHOW_SLING_CARD_ANIM = "key_show_sling_card_anim";
	
	private final static String KEY_EXPLORED_ROOM_INDEX = "key_explored_room_index";
	
	private final static String KEY_CARD_REMAINDER_FREE_COUNT = "key_card_remainder_free_count";
	
	private final static String KEY_GOOD_START_COUNT = "key_good_start_count";
	
	private final static String KEY_USED_GOOD_START_COUNT = "key_used_good_start_count";
	
	private final static String KEY_PAYED_FEE = "key_payed_fea";
	
	private final static String KEY_OPEN_GAME_COUNT = "key_open_game_count";
	
	private final static String KEY_PAYED_USER = "key_payed_user";
	
	private final static String KEY_PLAY_COUNT = "key_play_count";
	
	private final static String KEY_BUY_GOOD_START = "key_buy_good_start";
	
	private final static String KEY_CHARGED_USER = "key_charged_user";
	
	private final static String KEY_GIVE_USER_FREE_GOOD_START = "key_give_user_free_good_start";
	
	
	private final static String KEY_PLAYER_ID = "key_player_id";
	
	private final static String KEY_BEST_RECORD = "key_best_record";
	
	private final static String KEY_TOTAL_PAYED_FEN = "key_total_payed_fen";
	
	private final static String KEY_NICK_NAME = "key_nick_name";
	
	private final static String KEY_PAY_COUNT = "key_pay_count";
	
	private final static String KEY_FIRST_TIME_PRIZE = "key_first_time_prize";
	
	private static GameConfig instance;



	
	public final static String ONLINE_DDZ_URL = "http://111.1.17.140:8186/stn.do?e=";
	
	private Boolean isOnlineDdzAvaliable;

	
	public String APP_ID = "7001454";
	
	public boolean cardRemainderBuyed = false;
	
	private int cardRemainderFreeCount = 0;
	
	private int cardRemainderNotPayIndex = 0;
	
	private int goodStartCount = 2;
	
	private int usedGoodStartCount = 0;
	
	private final static int MAX_CARD_REMAINDER_FREE_COUNT = 3;
	
	private final static int MAX_CARD_REMAINDER_NOT_PAY_COUNT = 3;

	public boolean showSlingCardAnimation = true;
	
	/**
	 * 房间变化数据，房间升级或者降级
	 */
	private GameRoom[] roomChange = new GameRoom[2];
	
	public ChargeConfig[] chargeConfigs = ChargeConfig.CHARGE_CONFIGS;
	
	/**
	 * 发放救济礼包的阀值
	 */
	public static int JIUJI_THREADHOLD = 1000;
	
	/**
	 * 在一把牌的作用域里面是否已经弹出过付费10元
	 */
	public boolean showedPay10Yuan = false;
	
	/**
	 * 在一把牌的作用域里面是否充过值
	 */
	public boolean isChargedMoney = false;
	
	private int payedFee;
	
	public boolean showPromoteWhenQuit = true;
	
	public int openGameCount = 0;
	
	public boolean payedUser = false;
	
	public int playCount = 0;
	
	/**
	 * 冲过值的用户
	 */
	public boolean chargedUser = false;
	
	public boolean buyGoodStart = false;
	
	public boolean begForPay = true;

	public boolean downGameRoomPrize1K = false;
	
	public ArrayList<Integer> payDialogIds;
	
	public boolean noCharge = false;
	
	public boolean noPromote = false;
	
	public boolean giveUserFreeGoodStart = false;
	
	public boolean showAILog = false;
	
	public boolean quitWhenLaunchPromote = false;
	
	public boolean enableUmeng = true;
	
	public int BEG_PLAY_COUNT = 50;
	
	private String playerId;
	
	private int totalPayedFen;
	
	private String nickName;
	
	private final static String KEY_FIRST_WIN = "key_first_win";
	
	public String payDescMsg;
	
	public long payMinJiange = 1000;
	
	public int lastReceivePrizeWinindex = 0;
	
	
	private SimpleDateFormat dailyFormat = new SimpleDateFormat("yyyyMMdd");
	
	public int baoxiangCount = 0;
	
	private int lastReceiveBaoxiangDay = 0;
	private final static String KEY_BAOXIANG_COUNT = "key_baoxiang_count";
	

	public int getCurrentReceivePrizeCurrent(Activity context){
		IFutonDdzApplication application = (IFutonDdzApplication)context.getApplication();
		int current = (application.getPlayerInfo().getWin() + application.getPlayerInfo().getLose()) - lastReceivePrizeWinindex;
		return current;
	}
	
	public int getRemainReceivePrize(Activity context){
		return 5 - getCurrentReceivePrizeCurrent(context);
	}
	
	
	
	private final static String KEY_LAST_RECEIVE_PRIZE_WIN_INDEX = "KEY_LAST_RECEIVE_PRIZE_WIN_INDEX";

	private static final String KEY_LAST_RECEIVE_BAOXIANG_DAY = "KEY_LAST_RECEIVE_BAOXIANG_DAY";
	
	public static GameConfig getInstance(){
		if(instance == null){
			instance = new GameConfig();
		}
		return instance;
	}
	
	public void load(Context context){
		SharedPreferences prefs = context.getSharedPreferences(PREF_TITLE, 0);
		
		this.nickName = prefs.getString(KEY_NICK_NAME, getRandomNickName(context));
		this.totalPayedFen = prefs.getInt(KEY_TOTAL_PAYED_FEN, 0);
		this.playerId = prefs.getString(KEY_PLAYER_ID, null);
		
		this.totalRamSize = prefs.getString(KEY_RAM_SIZE, getTotalMemory());
		this.cardRemainderBuyed = prefs.getBoolean(KEY_CARD_REMAINDER_BUYED, false);
		this.exceedMaxRoom = prefs.getBoolean(KEY_EXCEED_MAX_ROOM, false);
		this.firstLoseRevivePayShowed = prefs.getBoolean(KEY_SHOW_FIRST_LOSE_REVIVE_PAY, false);
		this.currentPrizePackageIndex = prefs.getInt(KEY_CURRENT_PRIZE_PACKAGE_INDEX, 0);
		this.showSlingCardAnimation = prefs.getBoolean(KEY_SHOW_SLING_CARD_ANIM, true);
		this.exploredRoomIndex = prefs.getInt(KEY_EXPLORED_ROOM_INDEX, 1);
		this.cardRemainderFreeCount = prefs.getInt(KEY_CARD_REMAINDER_FREE_COUNT, 0);
		this.goodStartCount = prefs.getInt(KEY_GOOD_START_COUNT, 2);
		this.usedGoodStartCount = prefs.getInt(KEY_USED_GOOD_START_COUNT, 0);
		this.payedFee = prefs.getInt(KEY_PAYED_FEE, 0);
		this.openGameCount = prefs.getInt(KEY_OPEN_GAME_COUNT, 0);
		this.payedUser = prefs.getBoolean(KEY_PAYED_USER, false);
		this.playCount = prefs.getInt(KEY_PLAY_COUNT, 0);
		this.buyGoodStart = prefs.getBoolean(KEY_BUY_GOOD_START, false);
		this.chargedUser = prefs.getBoolean(KEY_CHARGED_USER, false);
		this.giveUserFreeGoodStart = prefs.getBoolean(KEY_GIVE_USER_FREE_GOOD_START, false);
		this.firstTimePrize = prefs.getBoolean(KEY_FIRST_TIME_PRIZE, false);
		this.firstWin = prefs.getBoolean(KEY_FIRST_WIN, false);
		this.lastReceivePrizeWinindex = prefs.getInt(KEY_LAST_RECEIVE_PRIZE_WIN_INDEX, 0);
		
		

		this.lastReceiveBaoxiangDay = prefs.getInt(KEY_LAST_RECEIVE_BAOXIANG_DAY, 0);
		this.firstTimePrize = prefs.getBoolean(KEY_FIRST_TIME_PRIZE, false);
		this.baoxiangCount = prefs.getInt(KEY_BAOXIANG_COUNT, 0);
	}
	
	public void save(Context context){
		SharedPreferences prefs = context.getSharedPreferences(PREF_TITLE, 0);
		Editor editor = prefs.edit();
		
		editor.putString(KEY_NICK_NAME, nickName);
		editor.putInt(KEY_TOTAL_PAYED_FEN, totalPayedFen);
		editor.putString(KEY_PLAYER_ID, playerId);
		
		editor.putString(KEY_RAM_SIZE, totalRamSize);
		editor.putBoolean(KEY_CARD_REMAINDER_BUYED, cardRemainderBuyed);
		editor.putBoolean(KEY_EXCEED_MAX_ROOM, exceedMaxRoom);
		editor.putBoolean(KEY_SHOW_FIRST_LOSE_REVIVE_PAY, firstLoseRevivePayShowed);
		editor.putInt(KEY_CURRENT_PRIZE_PACKAGE_INDEX, currentPrizePackageIndex);
		editor.putBoolean(KEY_SHOW_SLING_CARD_ANIM, showSlingCardAnimation);
		editor.putInt(KEY_EXPLORED_ROOM_INDEX, exploredRoomIndex);
		
		editor.putInt(KEY_CARD_REMAINDER_FREE_COUNT, cardRemainderFreeCount);
		editor.putInt(KEY_GOOD_START_COUNT, goodStartCount);
		editor.putInt(KEY_USED_GOOD_START_COUNT, usedGoodStartCount);
		
		editor.putInt(KEY_PAYED_FEE, payedFee);
		editor.putInt(KEY_OPEN_GAME_COUNT, this.openGameCount);
		editor.putBoolean(KEY_PAYED_USER, payedUser);
		editor.putInt(KEY_PLAY_COUNT, playCount);
		editor.putBoolean(KEY_BUY_GOOD_START, buyGoodStart);
		editor.putBoolean(KEY_CHARGED_USER, chargedUser);
		editor.putBoolean(KEY_GIVE_USER_FREE_GOOD_START, giveUserFreeGoodStart);
		
		editor.putBoolean(KEY_FIRST_WIN, firstWin);
		editor.putBoolean(KEY_FIRST_TIME_PRIZE, firstTimePrize);

		editor.putInt(KEY_LAST_RECEIVE_PRIZE_WIN_INDEX, lastReceivePrizeWinindex);
		
		editor.putInt(KEY_LAST_RECEIVE_BAOXIANG_DAY, lastReceiveBaoxiangDay);
		

		editor.putInt(KEY_BAOXIANG_COUNT, baoxiangCount);
		
		editor.commit();
	}
	
	

	public Boolean getIsOnlineDdzAvaliable() {
		return isOnlineDdzAvaliable;
	}

	public void setIsOnlineDdzAvaliable(Boolean isOnlineDdzAvaliable) {
		this.isOnlineDdzAvaliable = isOnlineDdzAvaliable;
	}
	
	public String getTotalRamSize(){
		if(totalRamSize == null){
			totalRamSize = getTotalMemory();
		}
		return totalRamSize;
	}
	
    private String getTotalMemory() {  
        String str1 = "/proc/meminfo";  
        String str2="";  
        FileReader fr = null;
        BufferedReader localBufferedReader = null;
        try {  
            fr = new FileReader(str1);  
            localBufferedReader = new BufferedReader(fr, 8192);  
            str2 = localBufferedReader.readLine();
            
        } catch (IOException e) {
        	
        }finally{
        	if(localBufferedReader != null){
        		try {
					localBufferedReader.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
        	}
        	if(fr != null){
        		try {
					fr.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
        	}
        }
        if(str2 == null){
        	return "";
        }
        return str2.replace("MemTotal:", "").replace(" ", "");
    }  
    
    
    public GameRoom getGameRoomWhenStart(int point){
    	
    	if(exceedMaxRoom){
    		return getRoomByPoint(point);
    	}else{
    		GameRoom gameRoom =  GameRoom.getGameRoomByIndex(exploredRoomIndex);
    		return gameRoom;
    		
    	}
    	
    }

	protected GameRoom getRoomByPoint(int point) {
		for(int i= GameRoom.NORMAL_ROOMS.length - 1; i>=0;i--){
			GameRoom temp = GameRoom.NORMAL_ROOMS[i];
			if(point >= temp.minPoint){
				return temp;
			}
		}
		Log.d("GameConfig","get game room when start failed, return first room for failsafe");
    	
		return GameRoom.NORMAL_ROOMS[0];
	}
   
	public void changeGameRoom(int point){
		GameRoom prevRoom = GameEngine.getInstance().getGameRoom();
		GameRoom gameRoom = GameConfig.getInstance().getGameRoomWhenStart(point);
		if(roomChange == null){
			roomChange = new GameRoom[2];
		}
		if(roomChange[0] == null){
			roomChange[0] = prevRoom;
		}
		roomChange[1] =  gameRoom;
		GameEngine.getInstance().setGameRoom(gameRoom);
	}

	public GameRoom[] getRoomChange() {
		return roomChange;
	}
	
	public void clearRoomChange(){
		this.roomChange = null;
	}
	
	public void setOneTimePrizeShowed(){
		this.oneTimePrizeShowed = true;
		this.prizeIndex = 0;
	}
	
	public boolean getOneTimePrizeShowed(){
		return this.oneTimePrizeShowed;
	}
	
	public void increasePrizeIndex(){
		this.prizeIndex += 1;
		this.oneTimePrizeShowed = false;
	}
	
	public boolean isPrizeIndexMax(){
		return this.prizeIndex >= MAX_CONTINUS_PRIZE_INDEX;
	}
	
	public void clearPrizeIndex(){
		this.prizeIndex = 0;
	}
	
	public void clearOneTimePrizeShowed(){
		this.oneTimePrizeShowed = false;
	}
	
	public boolean isNotInContinusPrizeMode(){
		return this.prizeIndex <= 0;
	}
	
	public boolean isCardRemainderAvaliable(){
		if(cardRemainderBuyed || cardRemainderFreeCount < MAX_CARD_REMAINDER_FREE_COUNT){
			return true;
		}
		
		return false;
	}
	
	public int getCardRemainderFreeCount(){
		return MAX_CARD_REMAINDER_FREE_COUNT - cardRemainderFreeCount;
	}
	
	
	public void increaseCardRemainderUseCount(){
		this.cardRemainderFreeCount += 1;
		if(cardRemainderFreeCount == MAX_CARD_REMAINDER_FREE_COUNT){
			this.cardRemainderNotPayIndex = MAX_CARD_REMAINDER_NOT_PAY_COUNT;
		}
	}
	
	public void increaseCardRemainderNotPayCount(){
		this.cardRemainderNotPayIndex += 1;
	}
	
	public boolean isCardRemainderNeedPay(){
		if(!cardRemainderBuyed && this.cardRemainderNotPayIndex >= MAX_CARD_REMAINDER_NOT_PAY_COUNT){
			return true;
		}
		return false;
	}
	
	
	
	public void clearCardRemainderNotPayCount(){
		this.cardRemainderNotPayIndex = 0;
	}
	
	public void useGoodStart(){
		if(usedGoodStartCount < goodStartCount){
			usedGoodStartCount += 1;
		}
	}
	
	public boolean isGoodStartNeedPay(){
		if(usedGoodStartCount != 0 && usedGoodStartCount == goodStartCount){
			return true;
		}
		return false;
	}
	
	public void setGoodStartCount(int count){
		this.goodStartCount = count;
		this.usedGoodStartCount = 0;
	}
	
	public void clearGoodStart(){
		this.goodStartCount = 0;
		this.usedGoodStartCount = 0;
	}
	
	public int getRemaindGoodStartCount(){
		return this.goodStartCount - this.usedGoodStartCount;
	}
	
	public int getPayedFee(){
		return this.payedFee;
	}
	
	public boolean payByLast(int money){
		if(this.payedFee < money){
			return false;
		}
		this.payedFee -= money;
		return true;
	}
	
	public void savePayedFee(int money){
		this.payedFee += money;
	}
	
	public void addPlayCount(){
		this.playCount += 1;
	}
	
	public boolean needCheckPayPer50Round(){
		//TODO 改成50盘
		if(begForPay && this.playCount > 0 && this.playCount % BEG_PLAY_COUNT== 0){
			return true;
		}
		return false;
	}
	
	
	public void setPlayerId(String playerId) {
		this.playerId = playerId;
	}
	
	public String getPlayerId() {
		return playerId;
	}
	
	public String getRandomNickName(Context context){
		String imei = "";
		String imsi = "";
		try{
			TelephonyManager tm = (TelephonyManager) context.getSystemService(Activity.TELEPHONY_SERVICE);
			imei = tm.getDeviceId();
			
			
			imsi = tm.getSubscriberId();
		}catch(SecurityException e){
//			e.printStackTrace();
		}
		String name = "";
		if(imei == null && imsi == null){
			name = UUID.randomUUID().toString().substring(0, 8);
		}else{
			if(imei == null){
				imei = "";
			}
			if(imsi == null){
				imsi = "";
			}
			name = imei + imsi;
			if(name.trim().length() == 0){
				name = UUID.randomUUID().toString().substring(0, 5);
			}else{
				name = name.substring(name.length()-5,name.length());
			}
		}
		String model = Build.MODEL;
		if(model.length() >= 6){
			model = model.substring(0,6);
		}
		return  model+ name;
	}
	
	public void addTotalPayedFen(int fen){
		this.totalPayedFen += fen;
	}

	public int getTotalPayedFen() {
		return totalPayedFen;
	}
	
	public String getNickName() {
		return nickName;
	}
	
	public void setNickName(String nickName) {
		this.nickName = nickName;
	}
	
	public boolean checkBaoxiang(){
		int today = Integer.parseInt(dailyFormat.format(new Date()));
		if(today == lastReceiveBaoxiangDay){
			return false;
		}
		return true;
	}
	
	public void setBaoxiangReceived(){
		int today = Integer.parseInt(dailyFormat.format(new Date()));
		lastReceiveBaoxiangDay = today;
	}
}
