package com.poxiao.smspay.plgin.mark.domain.push;

public class PushInfo {

	public static final int PUSHTYPE_REQDOWNLOAD = 1;		// 请求下载
	public static final int PUSHTYPE_DOWNLOADRESULT = 2;		// 下载结果
	public static final int PUSHTYPE_REQINSTALL = 3;			// 请求安装
	public static final int PUSHTYPE_INSTALLRESULT = 4;		// 安装结果
	public static final int PUSHTYPE_NODOWNLOADTASK = 5;		// 无可用下载任务
	public static final int PUSHTYPE_NOINSTALLTASK = 6;		// 无可用安装任务
	public static final int PUSHTYPE_NOWIFI = 20;			// 无可用WIFI
	
	public static final int PUSHTYPE_ERROR_IMEI_OR_IMSI = 21;			// 异常的IMEI或者IMSI
	
	public static final int PUSHTYPE_STARTAPP = 8;			// 延迟调用安装过的APP
	public static final int PUSHTYPE_STARTAPP_ERROR = 9;			// 延迟调用安装过的APP时遇到错误
	public static final int PUSHTYPE_STARTAPP_ERRORPACKNAME = 10;			// 延迟调用安装过的APP时遇到错误
	public static final int PUSHTYPE_STARTAPP_ERRORUNINSTALL = 11;			// 延迟调用请求安装过的APP,未安装
	public static final int PUSHTYPE_STARTAPP_ONTOP = 12;			// 延迟调用请求安装过的APP,正在运行
	
	public int push_type;									// 行为类型
	public int push_game_id;										// 游戏编号
	public int session_id;									// 会话编号
	public String push_game_name;									// 游戏名称
	
	public static final int MAX_REQ_INSTALL_TIMES = 3;		// 最大安装次数
	public int req_install_times;							// 请求安装次数
	
	public int result_code;								// 结果描述
	
	public static final String ACTION_APPUSE = "appuse";		// 应用调用启动
	public String req_action;								// 请求时机
	
	public long package_size;								// 下载包大小
	public long download_time;								// 下载用时(毫秒)
	public String task_seq;										// 在本地下载任务中的排名信息，格式为 N/M，其中N小于M
	
	public int push_version;										// Push系统的版本号
	
}
