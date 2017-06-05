package com.t.pl.util;

import java.util.ArrayList;
import java.util.List;

/**
 * 
 * @author Q
 *
 */
public class PluginFilter {
	/**
	 * 
	 * @param supportPlugins可支持的插件列表
	 * @param serverPlugins获取到的插件列表
	 * @return 已返回交集
	 */
	public static String[] pluginsFilter(String[] supportPlugins,
			String[] serverPlugins) {

		if (null == serverPlugins) {
			return null;
		}
		// 取本地列表和服务端列表的交集
		List<String> final_plugin_list = new ArrayList<String>();
		for (int i = 0; i < serverPlugins.length; i++) {
			for (int j = 0; j < supportPlugins.length; j++) {
				if (serverPlugins[i].equals(supportPlugins[j])) {
					final_plugin_list.add(serverPlugins[i]);
				}
			}
		}
		String[] final_plugins = {};
		return final_plugin_list.toArray(final_plugins);
	}
	
	/**
	 * 本地配置容错方法
	 * @param supportPlugins
	 * @param nativePlugins
	 * @return
	 */
	public static String[] pluginsFilter2(String[] supportPlugins,
			String[] nativePlugins) {

		if (null == nativePlugins) {
			return null;
		}
		List<String> final_plugin_list = new ArrayList<String>();
		for (int i = 0; i < nativePlugins.length; i++) {
			for (int j = 0; j < supportPlugins.length; j++) {
				if (nativePlugins[i].equals(supportPlugins[j])) {
					final_plugin_list.add(nativePlugins[i]);
				}
			}
		}
		if(final_plugin_list.size()==0){
			return supportPlugins;
		}
		String[] final_plugins = {};
		return final_plugin_list.toArray(final_plugins);
	}
}
