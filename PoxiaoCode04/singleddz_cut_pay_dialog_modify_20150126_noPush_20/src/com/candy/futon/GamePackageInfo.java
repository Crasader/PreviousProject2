package com.candy.futon;


public enum GamePackageInfo {

	DDZ(9992,"com.poxiao.kxzsj.standalone",0,"开心炸三家"),
	ZJH(2,"com.poxiao.zjh.net",0,"联网札三家"),
	NIUNIU_100_REN(3,"com.poxiao.niuniu.net",0,"百人牛牛"),
	QBSK(4,"com.poxiao.qbsk.net",0,"千变双扣"),
	ERMJ(9988,"com.poxiao.doublemahjong.standalone",0,"二人麻将");
	
	public static GamePackageInfo getPackageInfo(int gameId2) {
		switch (gameId2) {
		case 1:
			return DDZ;
		case 2:
			return ZJH;
		case 3:
			return NIUNIU_100_REN;
		}
		return null;
	}
	
	private int gameId;
	private String packageName;
	private int version;
	private String gameName;
	
	private GamePackageInfo(int gameId, String packageName, int version, String gameName){
		this.gameId = gameId;
		this.packageName = packageName;
		this.version = version;
		this.gameName = gameName;
	}

	public int getGameId() {
		return gameId;
	}

	public String getPackageName() {
		return packageName;
	}

	public int getVersion() {
		return version;
	}

	public String getGameName() {
		return gameName;
	}

	
	
	
	
}
