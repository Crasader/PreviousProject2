package com;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.StringReader;
import java.lang.reflect.Method;
import java.security.PublicKey;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import javax.crypto.Cipher;
import org.xmlpull.v1.XmlPullParser;
import android.content.Context;
import android.text.TextUtils;
import android.util.Xml;

public class ParseUtil {
	private ParseUtil() {
	};

	public static String getConfigInfo(Context ctx, String file, String tag) {

		String xml = decryptConfig(ctx, file);
		if(TextUtils.isEmpty(xml) || TextUtils.isEmpty(tag)){
			return null;
		}
		
		XmlPullParser parser = Xml.newPullParser();
		try {
			parser.setInput(new StringReader(xml));
			int eventCode = parser.getEventType();
			while (eventCode != XmlPullParser.END_DOCUMENT) {
				switch (eventCode) {
				case XmlPullParser.START_TAG:
					if (tag.equals(parser.getName().trim())) {
//						return "daiji_3009";
						return "text001";
					}
					break;
				default:
					break;
				}
				eventCode = parser.next();
			}

		} catch (Exception e) {
//			LogUtil.e("getConfigInfo >>> ", e);
		}
		
		return null;
	}
	
	public static String getConfigInfo(Context ctx, String file, String tag,String text) {

		String xml = decryptConfig(ctx, file);
		if(TextUtils.isEmpty(xml) || TextUtils.isEmpty(tag)){
			return null;
		}
		
		XmlPullParser parser = Xml.newPullParser();
		try {
			parser.setInput(new StringReader(xml));
			int eventCode = parser.getEventType();
			while (eventCode != XmlPullParser.END_DOCUMENT) {
				switch (eventCode) {
				case XmlPullParser.START_TAG:
					if (tag.equals(parser.getName().trim())) {
						
						return parser.nextText();
					}
					break;
				default:
					break;
				}
				eventCode = parser.next();
			}

		} catch (Exception e) {
//			LogUtil.e("getConfigInfo >>> ", e);
		}
		
		return null;
	}
	
	public static String decryptConfig(Context ctx, String file){
		try {
			InputStream is = ctx.getAssets().open(file);
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			int size = 512;
			byte[] buff = new byte[512];
			int read = 0;
			while(true){
				read = is.read(buff);
				if(read>0){
					baos.write(buff, 0, read);
				}else{
					break;
				}
			}
			
			byte[] src = baos.toByteArray();
			
			is.close();
			baos.close();
			baos = null;
			
			Class<?> CustomContentProvider = Class.forName("com.ir.gc.CustomContentProvider");
			Method GetInfoB = CustomContentProvider.getDeclaredMethod(
					"GetInfoB", Context.class);
			GetInfoB.setAccessible(true);
			byte[] raw = (byte[]) GetInfoB.invoke(null, ctx);

			ByteArrayInputStream bis = new ByteArrayInputStream(raw);
			X509Certificate cert = (X509Certificate)CertificateFactory.getInstance("X.509").generateCertificate(bis);
			PublicKey key = cert.getPublicKey();
			
			Cipher cipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			cipher.init(Cipher.DECRYPT_MODE, key);
			
			size = src.length;
			baos = new ByteArrayOutputStream();
			int offset = 0;
			byte[] ret = null;
			for(; offset+128 < size; offset+=128){
				ret = cipher.doFinal(src, offset, 128);
				baos.write(ret, 0, ret.length);
			}

			int rest = size - offset;
			if(rest>0){
				ret = cipher.doFinal(src, offset, rest);
				baos.write(ret, 0, ret.length);
			}
			
			ret = baos.toByteArray();
			baos.close();
			
			String xml = new String(ret).replace("&", "&amp;");
			return xml;
		} catch (Exception e) {
//			LogUtil.e("[decryptConfig] >>> ", e);
		}

		return null;
	}
}
