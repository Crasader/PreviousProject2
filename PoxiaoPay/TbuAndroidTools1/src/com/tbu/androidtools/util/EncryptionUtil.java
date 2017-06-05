package com.tbu.androidtools.util;

import java.security.MessageDigest;
import java.security.spec.AlgorithmParameterSpec;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class EncryptionUtil {
	public static String IvString = "abcdefgh12345678";
	public static String KeyString = "poxiaopassword";
	/**
	 * AES-128-CBC对称加密
	 * 
	 * @param content
	 *            加密的明文
	 * @param secretKey
	 *            密钥
	 * @param iv
	 *            CBC向量，长度为16的byte数组
	 * @return
	 * @throws Exception
	 */
	public static String cbcEncrypt(String content, String secretKey, byte[] iv) throws Exception {
		MessageDigest md = MessageDigest.getInstance("MD5");
		byte[] thedigest = md.digest(secretKey.getBytes("UTF-8"));
		SecretKeySpec skc = new SecretKeySpec(thedigest, "AES");
		Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
		// 算法参数
		AlgorithmParameterSpec paramSpec = new IvParameterSpec(iv);
		cipher.init(Cipher.ENCRYPT_MODE, skc, paramSpec);
		byte[] input = content.getBytes("UTF-8");
		int len = input.length;
		byte[] cipherText = new byte[cipher.getOutputSize(len)];
		int ctLength = cipher.update(input, 0, len, cipherText, 0);
		ctLength += cipher.doFinal(cipherText, ctLength);
		return byte2hex(cipherText);
	}

	/**
	 * AES-128-CBC对称解密
	 * 
	 * @param encrypted
	 *            解密的密文
	 * @param secretKey
	 *            密钥
	 * @param iv
	 *            CBC向量，长度为16的byte数组
	 * @return 明文
	 * @throws Exception
	 */
	public static String cbcDecrypt(String encrypted, String secretKey, byte[] iv) throws Exception {
		MessageDigest md = MessageDigest.getInstance("MD5");
		byte[] thedigest = md.digest(secretKey.getBytes("UTF-8"));
		SecretKeySpec skey = new SecretKeySpec(thedigest, "AES");
		Cipher dcipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
		// 算法参数
		AlgorithmParameterSpec paramSpec = new IvParameterSpec(iv);
		dcipher.init(Cipher.DECRYPT_MODE, skey, paramSpec);
		byte[] clearbyte = dcipher.doFinal(toByte(encrypted));
		return new String(clearbyte);
	}

	/**
	 * 将十六进制字符串转换成字节数组
	 * 
	 * @param hex
	 *            十六进制字符串
	 * @return byte数组
	 */
	public static byte[] toByte(String hex) {
		byte[] binary = new byte[hex.length() / 2];
		for (int i = 0, l = binary.length; i < l; i++) {
			binary[i] = (byte) Integer.parseInt(hex.substring(2 * i, 2 * i + 2), 16);
		}
		return binary;
	}

	/**
	 * 字节数组转换为二行制表示
	 * 
	 * @param inStr
	 *            需要转换字节数组
	 * @return 字节数组的二进制表示
	 */
	public static String byte2hex(byte[] inStr) {
		StringBuilder out = new StringBuilder(inStr.length * 2);
		for (int i = 0, l = inStr.length; i < l; i++) {
			// 字节做"与"运算，去除高位置字节 11111111
			if (((int) inStr[i] & 0xff) < 0x10) {
				// 小于十前面补零
				out.append("0");
			}
			out.append(Long.toString((int) inStr[i] & 0xff, 16));
		}
		return out.toString();
	}
	
	//和服务端约定好的,加密后的新字段
	public static String getNewParameter(String old){	
		return "poxiao_req_data="+old;
	}

	//测试代码
	public static void main(String[] args) {
		try {
			byte[] iv = "abcdefgh12345678".getBytes("UTF-8");
			String key = "我是密钥";
			String enc = cbcEncrypt("hello，我来自java", key, iv);
			System.out.println("1__" + enc);
			System.out.println("2__" + cbcDecrypt(enc, key, iv));
			// 解密来自nodejs的密文
			String node_enc = "a35e0e7ed17002ae620f3c879fcbbe7cf6bde7a542869d46ecdb0997c674562c";
			System.out.println("3__" + cbcDecrypt(node_enc, key, iv));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	 
}
