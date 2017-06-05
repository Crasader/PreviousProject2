短信注册工具类
=======



VERSION = "2"
==============
添加客户端注册行为统计：
用户不需要注册 －3
用户已经注册过了-2
多次注册请求注册失败，不允许注册了 -7
还在注册间隔内-8
没有该注册类型-9
用户开始请求注册0

添加短信mo情况统计
发送第几条短信

添加获取信息情况统计
统计是第几次去服务端获取到的信息

接入注册时在进入第一个activity时调用
	/**
	 * 请求注册接口，请求参数需要更新［判断是否需要注册的逻辑中可能需要］
	 * @param context
	 * @param imsi
	 * @param register_type :注册类型
	 * @param paramStr ：注册调用接口传递参数
	 * @param min ：注册间隔，单位分钟
	 * @param callback ：注册结构回调
	 * 检测是否无效imsi
	 * 检测是否需要注册 
	 * 检测是否本地已经有注册信息了
	 * 检测是否超过注册次数了
	 * 检测是否在注册间隔内
	 * 根据不同type去注册
	 * （同时记录请求的处理方式）
	 */
RegisterManager.getInstance().reqRigster方法

/**
	 * 实施注册逻辑:去服务端请求信息post
	 * @param register_type
	 * @param context
	 * @param imsi
	 * @param url
	 * @param paramStr
	 * @param callback
	 * 发送成功后，等待延迟时间后执行一次查询逻辑，结束返回callback信息（是否处理查询根据需要来）
	 * 说明：客户端使用时，一个注册结束的callback中才能开始下一个注册，否则不执行
	 */
	private void doRigister(final String register_type,final Context context,final String imsi,final String url,final String paramStr,final RegisterCallback callback)
 
	 
/**
	 * 成功发送过注册但没有获取到信息
	 * 主动去获取用户注册信息
	 * @param context
	 * @param register_type
	 * @param imsi
	 * @param query_interval ：注册结果查询间隔，单位秒
	 * @param query_times ：注册结果查询次数
	 * @param callback
	 */
	public void getUserRegisterInfo(final Context context ,String register_type,final String imsi,
			final int query_interval,final int query_times,final RegisterCallback callback)	 

VERSION = "1"
==============
初始版本
接入注册时在进入第一个activity时调用
RegisterManager.getInstance().reqRigster方法
	/**
	 * 请求注册接口，请求参数需要更新［判断是否需要注册的逻辑中可能需要］
	 * @param context
	 * @param imsi
	 * @param register_type :注册类型
	 * @param paramStr ：注册调用接口传递参数
	 * @param min ：注册间隔，单位分钟
	 * @param callback ：注册结构回调
	 */
	 
获取用户的注册信息	 
getUserRegisterInfo
	/**
	 * 获取用户注册信息
	 * @param context
	 * @param register_type
	 * @param imsi
	 * @param callback
	 */