package com.tbu.androidtools.util;

import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;

import android.content.Context;

import com.tbu.androidtools.TbuAndroidTools;

public class ReadJsonUtil {
	public static String KEY = "p_k";

	public static String decoderByDES(Context context,String secretText, String key) {
		if(TbuAndroidTools.isDebugModel()){
			return secretText;
		}
		try {
			byte[] result = coderByDES(hexStr2ByteArr(secretText), key,
					Cipher.DECRYPT_MODE);
			return new String(result, "UTF-8");
		} catch (Exception ex) {
			ex.printStackTrace();
			return "";
		}
	}
	
	public static String decoderByDES(String secretText, String key) {
		try {
			byte[] result = coderByDES(hexStr2ByteArr(secretText), key,
					Cipher.DECRYPT_MODE);
			return new String(result, "UTF-8");
		} catch (Exception ex) {
			ex.printStackTrace();
			return "";
		}
	}

	private static byte[] hexStr2ByteArr(String strIn)
			throws NumberFormatException {
		byte[] arrB = strIn.getBytes();
		int iLen = arrB.length;
		// 两个字符表示一个字节，所以字节数组长度是字符串长度除以2
		byte[] arrOut = new byte[iLen / 2];
		for (int i = 0; i < iLen; i = i + 2) {
			String strTmp = new String(arrB, i, 2);
			arrOut[i / 2] = (byte) Integer.parseInt(strTmp, 16);
		}
		return arrOut;
	}

	private static byte[] coderByDES(byte[] plainText, String key, int mode)
			throws InvalidKeyException, InvalidKeySpecException,
			NoSuchAlgorithmException, NoSuchPaddingException,
			BadPaddingException, IllegalBlockSizeException,
			UnsupportedEncodingException {
		SecureRandom sr = new SecureRandom();
		byte[] resultKey = makeKey(key);
		DESKeySpec desSpec = new DESKeySpec(resultKey);
		SecretKey secretKey = SecretKeyFactory.getInstance("DES")
				.generateSecret(desSpec);
		Cipher cipher = Cipher.getInstance("DES");
		cipher.init(mode, secretKey, sr);
		return cipher.doFinal(plainText);
	}

	private static byte[] makeKey(String key)
			throws UnsupportedEncodingException {
		byte[] keyByte = new byte[8];
		byte[] keyResult = key.getBytes("UTF-8");
		for (int i = 0; i < keyResult.length && i < keyByte.length; i++) {
			keyByte[i] = keyResult[i];
		}
		return keyByte;
	}

}
