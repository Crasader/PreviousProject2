package com.tallbigup.android.load;

import java.util.Map;

public class PluginInfos {

	static Map<String, String> plugins;
	static Map<String, String> functions1;// onApplication
	static Map<String, String> functions2;// onActivity
	static Map<String, String> functions3;// quitActivity
	static String defaultPlufinName = null;
	static String debugModelName = null;
	
	public static Map<String, String> getPlugins() {
		return plugins;
	}

	public static void setPlugins(Map<String, String> plugins) {
		PluginInfos.plugins = plugins;
	}

	public static String getDefaultPlufinName() {
		return defaultPlufinName;
	}

	public static void setDefaultPlufinName(String defaultPlufinName) {
		PluginInfos.defaultPlufinName = defaultPlufinName;
	}

	public static Map<String, String> getFunctions1() {
		return functions1;
	}

	public static void setFunctions1(Map<String, String> functions) {
		PluginInfos.functions1 = functions;
	}

	public static Map<String, String> getFunctions2() {
		return functions2;
	}

	public static void setFunctions2(Map<String, String> functions2) {
		PluginInfos.functions2 = functions2;
	}

	public static Map<String, String> getFunctions3() {
		return functions3;
	}

	public static void setFunctions3(Map<String, String> functions3) {
		PluginInfos.functions3 = functions3;
	}

	public static String getDebugModelName() {
		return debugModelName;
	}

	public static void setDebugModelName(String debugModelName) {
		PluginInfos.debugModelName = debugModelName;
	}

	
	
}
