package com.mammoth.util;

import java.util.jar.JarFile;
import java.util.jar.Manifest;

public class TimeStamp {
	/**
	 * ��ӡ����������ʱ��
	 */
	private static String getBuildTime(String jarname) {
		try{
			JarFile jarFile = new JarFile(jarname);
			Manifest mf = jarFile.getManifest();
			return mf.getMainAttributes().getValue("tstamp");
		} catch(Exception e){
		}
		return "";
	}
	
	public static void log(String message){
		System.out.println(message);
	}

	public static String getTimeStampInformation() {
		String time = getBuildTime("LogViewer.jar");
		if(time == null) return "�޷�ȡ�ù���ʱ��";
		if(time.length() == 0) return "�޷�ȡ�ù���ʱ��";
		return "����ʱ��:" + time;
	}
}
