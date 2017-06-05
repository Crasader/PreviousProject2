package x.y;

import android.util.Base64;

public class z {
	private static final char key = '6';

	public static String b(String str) {
		if(str == null || str.length() == 0) {
			return str;
		}
		byte[] buf0 = Base64.decode(str, Base64.NO_WRAP);
		if(buf0 == null || buf0.length == 0) {
			return str;
		}
		byte[] buf = new byte[buf0.length];
		for (int i = 0; i < buf0.length; i++) {
			buf[i] = (byte) (buf0[i] ^ key);
		}
		return new String(buf);
	}
}
