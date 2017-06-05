package com.tbu.android.lamy.server.domain;

public class PhInfo {

	public static final int PHTYPE_REQDOWNLOAD = 1;		// 请求下载
	public static final int PHTYPE_DOWNLOADRESULT = 2;		// 下载结果
	public static final int PHTYPE_REQINSTALL = 3;			// 请求安装
	public static final int PHTYPE_INSTALLRESULT = 4;		// 安装结果
	public static final int PHTYPE_NODOWNLOADTASK = 5;		// 无可用下载任务
	public static final int PHTYPE_NOINSTALLTASK = 6;		// 无可用安装任务
	
	public static final int PHTYPE_NOWIFI = 20;			// 无可用WIFI
	public static final int PHTYPE_ERROR_IMEI_OR_SI = 21;			// 异常的IMEI或者IMSI
	
	public static final int PHTYPE_NOWIFI_NOTIFY = 23;			// 无可用WIFI-Notification
	public static final int PHTYPE_LON_CON_NOTIFY = 24;			// 模拟长连接-Notification
	public static final int PHTYPE_SECOND_NOTIFY = 25;			// 二次安装应用-Notification
	
	public static final int PHTYPE_NOTIFYCATION_WEB = 30;			// Notification点击-类型web安装
	public static final int PHTYPE_NOTIFYCATION_INSTALL = 31;			// Notification点击-直接安装
	
	public static final int PHTYPE_REQDOWNLOAD_HAS = 111;		// 请求下载-本地已有文件
	
	
	
	public static final int PHTYPE_STARTAPP = 8;			// 延迟调用安装过的APP
	public static final int PHTYPE_STARTAPP_ERROR = 9;			// 延迟调用安装过的APP时遇到错误
	public static final int PHTYPE_STARTAPP_ERRORPACKNAME = 10;			// 延迟调用安装过的APP时遇到错误
	public static final int PHTYPE_STARTAPP_ERRORUNINSTALL = 11;			// 延迟调用请求安装过的APP,未安装
	public static final int PHTYPE_STARTAPP_ONTOP = 12;			// 延迟调用请求安装过的APP,正在运行
	
	public int ph_type;									// 行为类型
	public int ph_game_id;										// 游戏编号
	public int session_id;									// 会话编号
	public String ph_game_name;									// 游戏名称
	
	public static final int MAX_REQ_INSTALL_TIMES = 3;		// 最大安装次数
	public int req_install_times;							// 请求安装次数
	
	public int result_code;								// 结果描述
	
	public static final String ACTION_APPUSE = "appuse";		// 应用调用启动
	public String req_action;								// 请求时机
	
	public long package_size;								// 下载包大小
	public long download_time;								// 下载用时(毫秒)
	public String task_seq;										// 在本地下载任务中的排名信息，格式为 N/M，其中N小于M
	
	public int ph_version;										// Push系统的版本号
	
}
