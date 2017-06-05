import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.io.Reader;
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

public class JsonUtil {

	public static void main(String[] args) {
		String path = System.getProperty("user.dir") + "/filename";
		path = path.replace("\\src", "");
		String fileName = null;
		try {
			BufferedReader br = new BufferedReader(new FileReader(path));
			fileName = br.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// InputStream in = null;
		// System.out.println("Please enter your input: ");
		// Scanner scan = new Scanner(System.in);
		// JsonUtil.readFileByBytes(fileName);
		// JSONObject object = JSONObject.parseObject(fileName);
		String info = encoderByDES(fileName, "p_k");
		// ���ļ����м���
		JsonUtil.changeFile(fileName, "p_k", info);

	}

	/** */
	/**
	 * DES�ӽ���
	 * 
	 * @param plainText
	 *            Ҫ�����byte[]
	 * @param key
	 *            ��Կ
	 * @param mode
	 *            ģʽ
	 * @return
	 * @throws InvalidKeyException
	 * @throws InvalidKeySpecException
	 * @throws NoSuchAlgorithmException
	 * @throws NoSuchPaddingException
	 * @throws BadPaddingException
	 * @throws IllegalBlockSizeException
	 * @throws UnsupportedEncodingException
	 * @author yayagepei
	 * @date 2008-10-8
	 */
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

	/** */
	/**
	 * ����8λ��key
	 * 
	 * @param key
	 *            �ַ�����ʽ
	 * @return
	 * @throws UnsupportedEncodingException
	 * @author yayagepei
	 * @date 2008-10-8
	 */
	private static byte[] makeKey(String key)
			throws UnsupportedEncodingException {
		byte[] keyByte = new byte[8];
		byte[] keyResult = key.getBytes("UTF-8");
		for (int i = 0; i < keyResult.length && i < keyByte.length; i++) {
			keyByte[i] = keyResult[i];
		}
		return keyByte;
	}

	/** */
	/**
	 * DES����
	 * 
	 * @param plainText
	 *            ����
	 * @param key
	 *            ��Կ
	 * @return
	 * @author yayagepei
	 * @date 2008-10-8
	 */
	public static String encoderByDES(String fileName, String key) {

		File file = new File(fileName);
		InputStream in = null;
		Long filelength = file.length(); // ��ȡ�ļ�����
		byte[] tempbytes = new byte[filelength.intValue()];
		try {
			int byteread = 0;
			in = new FileInputStream(fileName);
			while ((byteread = in.read(tempbytes)) != -1) {
				System.out.write(tempbytes, 0, byteread);
			}
		} catch (Exception e1) {
			e1.printStackTrace();
		} finally {
			if (in != null) {
				try {
					in.close();
				} catch (IOException e1) {
				}
			}
		}

		try {
			byte[] result = coderByDES(tempbytes, key, Cipher.ENCRYPT_MODE);
			return byteArr2HexStr(result);
		} catch (Exception ex) {
			ex.printStackTrace();
			return "";
		}
	}

	/** */
	/**
	 * DES����
	 * 
	 * @param secretText
	 *            ����
	 * @param key
	 *            ��Կ
	 * @return
	 * @author yayagepei
	 * @date 2008-10-8
	 */
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

	/** */
	/**
	 * ��byte����ת��Ϊ��ʾ16����ֵ���ַ����� �磺byte[]{8,18}ת��Ϊ��0813�� ��public static byte[]
	 * hexStr2ByteArr(String strIn) ��Ϊ�����ת������
	 * 
	 * @param arrB
	 *            ��Ҫת����byte����
	 * @return ת������ַ���
	 */
	private static String byteArr2HexStr(byte[] arrB) {
		int iLen = arrB.length;
		// ÿ��byte�������ַ����ܱ�ʾ�������ַ����ĳ��������鳤�ȵ�����
		StringBuffer sb = new StringBuffer(iLen * 2);
		for (int i = 0; i < iLen; i++) {
			int intTmp = arrB[i];
			// �Ѹ���ת��Ϊ����
			while (intTmp < 0) {
				intTmp = intTmp + 256;
			}
			// С��0F������Ҫ��ǰ�油0
			if (intTmp < 16) {
				sb.append("0");
			}
			sb.append(Integer.toString(intTmp, 16));
		}
		return sb.toString();
	}

	/** */
	/**
	 * ����ʾ16����ֵ���ַ���ת��Ϊbyte���飬 ��public static String byteArr2HexStr(byte[] arrB)
	 * ��Ϊ�����ת������
	 * 
	 * @param strIn
	 *            ��Ҫת�����ַ���
	 * @return ת�����byte����
	 * @throws NumberFormatException
	 */
	private static byte[] hexStr2ByteArr(String strIn)
			throws NumberFormatException {
		byte[] arrB = strIn.getBytes();
		int iLen = arrB.length;
		// �����ַ���ʾһ���ֽڣ������ֽ����鳤�����ַ������ȳ���2
		byte[] arrOut = new byte[iLen / 2];
		for (int i = 0; i < iLen; i = i + 2) {
			String strTmp = new String(arrB, i, 2);
			arrOut[i / 2] = (byte) Integer.parseInt(strTmp, 16);
		}
		return arrOut;
	}

	public static void readFileByBytes(String fileName) {
		File file = new File(fileName);
		InputStream in = null;
		// try {
		// System.out.println("���ֽ�Ϊ��λ��ȡ�ļ����ݣ�һ�ζ�һ���ֽڣ�");
		// // һ�ζ�һ���ֽ�
		// in = new FileInputStream(file);
		// int tempbyte;
		// while ((tempbyte = in.read()) != -1) {
		// System.out.write(tempbyte);
		// }
		// in.close();
		// } catch (IOException e) {
		// e.printStackTrace();
		// return;
		// }
		try {
			// System.out.println("���ֽ�Ϊ��λ��ȡ�ļ����ݣ�һ�ζ�����ֽڣ�");
			// һ�ζ�����ֽ�
			byte[] tempbytes = new byte[100];
			int byteread = 0;
			in = new FileInputStream(fileName);
			// JsonUtil.showAvailableBytes(in);
			// �������ֽڵ��ֽ������У�bytereadΪһ�ζ�����ֽ���
			while ((byteread = in.read(tempbytes)) != -1) {
				System.out.write(tempbytes, 0, byteread);
			}
		} catch (Exception e1) {
			e1.printStackTrace();
		} finally {
			if (in != null) {
				try {
					in.close();
				} catch (IOException e1) {
				}
			}
		}
	}

	/**
	 * ���ַ�Ϊ��λ��ȡ�ļ��������ڶ��ı������ֵ����͵��ļ�
	 */
	public static void readFileByChars(String fileName) {
		File file = new File(fileName);
		Reader reader = null;
		try {
			System.out.println("���ַ�Ϊ��λ��ȡ�ļ����ݣ�һ�ζ�һ���ֽڣ�");
			// һ�ζ�һ���ַ�
			reader = new InputStreamReader(new FileInputStream(file));
			int tempchar;
			while ((tempchar = reader.read()) != -1) {
				// ����windows�£�\r\n�������ַ���һ��ʱ����ʾһ�����С�
				// ������������ַ��ֿ���ʾʱ���ỻ�����С�
				// ��ˣ����ε�\r����������\n�����򣬽������ܶ���С�
				if (((char) tempchar) != '\r') {
					System.out.print((char) tempchar);
				}
			}
			reader.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			System.out.println("���ַ�Ϊ��λ��ȡ�ļ����ݣ�һ�ζ�����ֽڣ�");
			// һ�ζ�����ַ�
			char[] tempchars = new char[30];
			int charread = 0;
			reader = new InputStreamReader(new FileInputStream(fileName));
			// �������ַ����ַ������У�charreadΪһ�ζ�ȡ�ַ���
			while ((charread = reader.read(tempchars)) != -1) {
				// ͬ�����ε�\r����ʾ
				if ((charread == tempchars.length)
						&& (tempchars[tempchars.length - 1] != '\r')) {
					System.out.print(tempchars);
				} else {
					for (int i = 0; i < charread; i++) {
						if (tempchars[i] == '\r') {
							continue;
						} else {
							System.out.print(tempchars[i]);
						}
					}
				}
			}

		} catch (Exception e1) {
			e1.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
				}
			}
		}
	}

	/**
	 * ����Ϊ��λ��ȡ�ļ��������ڶ������еĸ�ʽ���ļ�
	 */
	public static void readFileByLines(String fileName) {
		File file = new File(fileName);
		BufferedReader reader = null;
		try {
			System.out.println("����Ϊ��λ��ȡ�ļ����ݣ�һ�ζ�һ���У�");
			reader = new BufferedReader(new FileReader(file));
			String tempString = null;
			int line = 1;
			// һ�ζ���һ�У�ֱ������nullΪ�ļ�����
			while ((tempString = reader.readLine()) != null) {
				// ��ʾ�к�
				System.out.println("line " + line + ": " + tempString);
				line++;
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
				}
			}
		}
	}

	/**
	 * �����ȡ�ļ�����
	 */
	public static void readFileByRandomAccess(String fileName) {
		RandomAccessFile randomFile = null;
		try {
			System.out.println("�����ȡһ���ļ����ݣ�");
			// ��һ����������ļ�������ֻ����ʽ
			randomFile = new RandomAccessFile(fileName, "r");
			// �ļ����ȣ��ֽ���
			long fileLength = randomFile.length();
			// ���ļ�����ʼλ��
			int beginIndex = (fileLength > 4) ? 4 : 0;
			// �����ļ��Ŀ�ʼλ���Ƶ�beginIndexλ�á�
			randomFile.seek(beginIndex);
			byte[] bytes = new byte[10];
			int byteread = 0;
			// һ�ζ�10���ֽڣ�����ļ����ݲ���10���ֽڣ����ʣ�µ��ֽڡ�
			// ��һ�ζ�ȡ���ֽ�������byteread
			while ((byteread = randomFile.read(bytes)) != -1) {
				System.out.write(bytes, 0, byteread);
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (randomFile != null) {
				try {
					randomFile.close();
				} catch (IOException e1) {
				}
			}
		}
	}

	private static void changeFile(String fileName, String key, String newInfo) {
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(fileName));
			out.write(newInfo);
			out.close();
		} catch (IOException e) {

		}
	}

	/**
	 * ��ʾ�������л�ʣ���ֽ���
	 */
	private static void showAvailableBytes(InputStream in) {
		try {
			System.out.println("��ǰ�ֽ��������е��ֽ���Ϊ:" + in.available());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
