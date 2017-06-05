package com.b.a.ioc;


public class IocInfos {

	static String applicationImpl = null;// 通过反射加载的IAppApplication的实现类
	static String payImplName;// 通过反射加载的IGamePInterface的实现类
	static String payImplFunction;

	public static String getApplicationImpl() {
		return applicationImpl;
	}

	public static void setApplicationImpl(String applicationImpl) {
		IocInfos.applicationImpl = applicationImpl;
	}

	public static String getPayImplName() {
		return payImplName;
	}

	public static void setPayImplName(String pImplName) {
		IocInfos.payImplName = pImplName;
	}

	public static String getPImplFunction() {
		return payImplFunction;
	}

	public static void setPImplFunction(String pImplFunction) {
		IocInfos.payImplFunction = pImplFunction;
	}

}