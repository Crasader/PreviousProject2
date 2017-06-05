package com.tbu.android.lamy.download.success;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.List;

import android.util.Base64;

import com.tbu.android.lamy.util.Debug;
import com.tbu.android.lamy.util.DownloadUtil;

public class SuccessFileManager {

	private static final String APK_SUBSTR = ".apk";
	
	/**
	 * 检查对应版本号和包名的应用是否有本地成功下载
	 * @param version
	 * @param packageName
	 * @return
	 */
	public static boolean hasDownloadFile(int version, String packageName) {
		List<SuccessDownload> sds =  SuccessFileManager.checkSuccessDir();
		Debug.w("SuccessFileManager->hasDownloadFile, sds.size=" + sds.size() + 
				"inputinfo, version:" +version + ";pn:" + packageName);
		if(sds != null && sds.size()>0){
			for(SuccessDownload sd : sds) {
				if(sd != null) {
					if(sd.version == version && sd.packageName.equals(packageName)) {
						Debug.w("SuccessFileManager->hasDownloadFile, equal!!!!, sd.version=" + sd.version+
								";sd.packageName=" + sd.packageName);
						return true;
					}else {
						Debug.w("SuccessFileManager->hasDownloadFile, not equal, sd.version=" + sd.version+
								";sd.packageName=" + sd.packageName);
					}
				}
			}
		}
		return false;
	}
	
	/**
	 * 根据版本号和报名获得编码的文件名。
	 * @param version
	 * @param packageName
	 * @return
	 */
	public static String getApkFileDir(String version, String packageName) {
		String bufferName = version+";"+packageName;
		String codeStr = SuccessFileManager.codeString(bufferName);
		return codeStr;
	}
	
	public static List<SuccessDownload> checkSuccessDir() {
		List<SuccessDownload> sds = new ArrayList<SuccessDownload>();
		File filepath = new File(DownloadUtil.getSdRootSuccessFilePath());
		File[] files = filepath.listFiles(); 
		if(files != null && files.length>0) {
			for ( File file : files )  {
				if( !file.isDirectory() ) {
					if(file.getName() != null && file.getName().length() > 4) {
//						Debug.i("SuccessFileManager->checkSuccessDir, filename[last_4] = " + file.getName().substring(
//								file.getName().length() - 4, file.getName().length()) );
						if(APK_SUBSTR.equals( file.getName().substring(
								file.getName().length() - APK_SUBSTR.length(), file.getName().length()) )) {
							String dirInfo = file.getName().substring(0, file.getName().length()-4);
//							Debug.i("SuccessFileManager->checkSuccessDir, filename[before_4] = " + dirInfo );
							String pgInfo = SuccessFileManager.decodeString(dirInfo);
							String[] pgInfos = pgInfo.split("\\;");
							if(pgInfos != null && pgInfos.length > 0) {
								SuccessDownload sd = new SuccessDownload();
								sd.version = Integer.parseInt(pgInfos[0]);
								sd.packageName = pgInfos[1];
								sds.add(sd);
//								Debug.i("SuccessFileManager->checkSuccessDir, version = " + sd.version );
//								Debug.i("SuccessFileManager->checkSuccessDir, packageName = " + sd.packageName );
							}
							
						}
					}
//					Debug.i("SuccessFileManager->checkSuccessDir, filename = " + file.getName());
				}
			}
		}
		
		return sds;
	}
	
	/**
	 * 拷贝文件，从路径A到B
	 * @param fromFile
	 * @param toFileName
	 * @return
	 */
	public static boolean copyFile(String fromFileDir, String toFileName) {
		Debug.w("SuccessFileManager->copyFile, coming ...");
		DownloadUtil.makeRootDirectory();	// 确保所在路径的完整性
		
		// TODO 考虑如果文件已经存在如何处理，目前默认覆盖
		
		File fromFile = new File(fromFileDir);
		File toFile = new File(DownloadUtil.getSdRootSuccessFilePath() + File.separator + toFileName);
		try {
			FileInputStream fisFrom = new FileInputStream(fromFile);
			FileOutputStream fosTo = new FileOutputStream(toFile);
			byte bt[] = new byte[1024];
			int readBtLength;
			while( (readBtLength = fisFrom.read(bt)) > 0 ) {
				fosTo.write(bt, 0, readBtLength);
			}
			fisFrom.close();
			fosTo.close();
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		Debug.w("SuccessFileManager->copyFile, success copy file, file name = " + toFileName);
		return true;
	}
	
	/**
	 * 对文件进行编码
	 * @param baseStr
	 * @return
	 */
	public static String codeString(String baseStr) {
		if(baseStr == null) {
			return null;
		}
		return Base64.encodeToString(baseStr.trim().getBytes(), Base64.DEFAULT).trim();
	}
	
	/**
	 * 对字符串进行解码
	 * @param baseStr
	 * @return
	 */
	public static String decodeString(String baseStr) {
		return new String(Base64.decode(baseStr, Base64.DEFAULT)).trim();
	}

}
