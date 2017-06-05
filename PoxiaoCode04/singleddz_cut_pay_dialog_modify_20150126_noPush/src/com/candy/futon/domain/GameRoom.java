package com.candy.futon.domain;

public class GameRoom {

	/**
	 * 底分
	 */
	public int basePoint;
	/**
	 * 基础倍数
	 */
	public int baseMag;
	/**
	 * 手续费
	 */
	public int teaFee;
	/**
	 * 进入最小分数
	 */
	public int minPoint;
	/**
	 * 房间封顶
	 */
	public int maxMag;
	
	
	public final static GameRoom[] NORMAL_ROOMS = new GameRoom[]{
		new GameRoom(200,1,0,1000,16),
		new GameRoom(400,1,0,3000,32),
		new GameRoom(800,1,0,12000,64),
		new GameRoom(1600,1,0,60000,64)};
	
	
	private GameRoom(int basePoint, int baseMag, int teaFee, int minPoint, int maxMag){
		this.baseMag = baseMag;
		this.basePoint = basePoint;
		this.teaFee = teaFee;
		this.minPoint = minPoint;
		this.maxMag = maxMag;
	}
	
	public static GameRoom getGameRoomByIndex(int index){
		int i = index - 1;
		if(i >= NORMAL_ROOMS.length){
			i = NORMAL_ROOMS.length - 1;
		}
		return NORMAL_ROOMS[i];
	}
	
	public static int getGameRoomIndex(GameRoom gameRoom){
		for(int i=0;i<NORMAL_ROOMS.length;i++){
			if(gameRoom == NORMAL_ROOMS[i]){
				return i + 1;
			}
		}
		throw new IllegalArgumentException("can not find the game room index");
	}
	
}
