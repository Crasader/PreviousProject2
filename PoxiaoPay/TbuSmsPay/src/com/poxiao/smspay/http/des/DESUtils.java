package com.poxiao.smspay.http.des;

import java.lang.reflect.Array;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;

/**
 * @author Archibald.Wang
 */
public class DESUtils {

    public static final String PASSWORD_CRYPT_KEY = "__jDlog_";

    private final static String algorithm = "DES/ECB/NoPadding";

    /**
     * 加密
     * 
     * @param src
     *            长度为8的倍数
     * @param key
     *            长度为8的倍数
     * @return
     * @throws Exception
     */
    public static byte[] encrypt(byte[] src, byte[] key) throws Exception {

        // 创建一个密匙工厂，然后用它把DESKeySpec转换成 一个SecretKey对象
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");

        // 从原始密匙数据创建DESKeySpec对象
        DESKeySpec dks = new DESKeySpec(key);
        SecretKey securekey = keyFactory.generateSecret(dks);

        // Cipher对象实际完成加密操作
        Cipher cipher = Cipher.getInstance(algorithm);

        // 用密匙初始化Cipher对象
        cipher.init(Cipher.ENCRYPT_MODE, securekey);

        // 获取数据并加密正式执行加密操作
        return cipher.doFinal(src);

    }

    /**
     * 解密
     * 
     * @param src
     *            长度为8的倍数
     * @param key
     *            长度为8的倍数
     * @return
     * @throws Exception
     */
    public static byte[] decrypt(byte[] src, byte[] key) throws Exception {

        // 从原始密匙数据创建一个DESKeySpec对象
        DESKeySpec dks = new DESKeySpec(key);

        // 创建一个密匙工厂，然后用它把DESKeySpec对象转换成 一个SecretKey对象
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        SecretKey securekey = keyFactory.generateSecret(dks);

        // Cipher对象实际完成解密操作
        Cipher cipher = Cipher.getInstance(algorithm);

        // 用密匙初始化Cipher对象
        cipher.init(Cipher.DECRYPT_MODE, securekey);

        // 正式执行解密操作
        return cipher.doFinal(src);

    }

    public final static byte[] encrypt(String source, byte[] key) {

        try {

            //补足8位
            byte[] sourceBytes = source.getBytes();
            int paddingSize = 8 - (sourceBytes.length % 8);
            byte[] paddingBytes = new byte[paddingSize];
            for (int i = 0; i < paddingBytes.length; i++) {
                paddingBytes[i] = (byte) 0x0;
            }
            sourceBytes = addAll(sourceBytes, paddingBytes);

            return encrypt(sourceBytes, key);
        }
        catch (Exception e) {
        	e.printStackTrace();
            return null;
        }
    }

    public final static byte[] decrypt(String data, byte[] key) {
        try {
            return decrypt(hex2byte(data.getBytes()), key);
        }
        catch (Exception e) {
        	e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] argv) throws Exception {
        String source = "Don't tell anybody!";
        byte[] encrypted = DESUtils.encrypt(source, PASSWORD_CRYPT_KEY.getBytes());
        byte[] decrypted = DESUtils.decrypt(encrypted, PASSWORD_CRYPT_KEY.getBytes());

        System.out.println("source:" + source);
        System.out.println("encrypted:" + byte2Hex(encrypted));
        System.out.println("decrypted:" + new String(decrypted));
    }
  
    public static byte[] hex2byte(byte[] b) {

        if ((b.length % 2) != 0)
            throw new IllegalArgumentException("长度不是偶数");

        byte[] b2 = new byte[b.length / 2];
        for (int n = 0; n < b.length; n += 2) {
            String item = new String(b, n, 2);
            b2[n / 2] = (byte) Integer.parseInt(item, 16);
        }
        return b2;
    }
    
    public static String byte2Hex(byte hash[]) {
        StringBuffer buf = new StringBuffer(hash.length * 2);
        int i;

        for (i = 0; i < hash.length; i++) {
            if (((int) hash[i] & 0xff) < 0x10) {
                buf.append("0");
            }
            buf.append(Long.toString((int) hash[i] & 0xff, 16));
        }
        return buf.toString();
    }
    
    public static byte[] clone(final byte[] array) {
        if (array == null) {
            return null;
        }
        return (byte[]) array.clone();
    }
    
    public static byte[] addAll(final byte[] array1, final byte[] array2) {
        if (array1 == null) {
            return clone(array2);
        }
        else if (array2 == null) {
            return clone(array1);
        }
        else {
            byte[] joinedArray = (byte[]) Array.newInstance(array1.getClass().getComponentType(), array1.length + array2.length);
            System.arraycopy(array1, 0, joinedArray, 0, array1.length);
            System.arraycopy(array2, 0, joinedArray, array1.length, array2.length);
            return joinedArray;
        }
    }
}

