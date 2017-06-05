package com.tbu.androidtools.util;

import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

/**
 * 
* @author molo.xiao@gmail.com 
* @version 创建时间：2015-5-6 上午11:07:16
*
 */
public class StringUtils {
	static public List<String> line2list(String line) {
		List<String> ret = new ArrayList<String>();
		StringTokenizer st = new StringTokenizer(line, ",", false);
		while (st.hasMoreTokens()) {
			ret.add(st.nextToken().trim());
		}

		return ret;
	}

	static public String[] line2array(String line) {
		return line2list(line).toArray(new String[0]);
	}

	public static boolean isBlank(String str) {
		if (str == null || str.trim().length() == 0)
			return true;
		return false;
	}
}
