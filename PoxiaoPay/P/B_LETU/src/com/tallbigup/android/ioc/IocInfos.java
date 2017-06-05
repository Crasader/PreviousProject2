package com.tallbigup.android.ioc;


public class IocInfos {

	static String applicationImpl = null;// 通过反射加载的IAppApplication的实现类
	static String payImplName;// 通过反射加载的IGamePayInterface的实现类
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

	public static void setPayImplName(String payImplName) {
		IocInfos.payImplName = payImplName;
	}

	public static String getPayImplFunction() {
		return payImplFunction;
	}

	public static void setPayImplFunction(String payImplFunction) {
		IocInfos.payImplFunction = payImplFunction;
	}

}
