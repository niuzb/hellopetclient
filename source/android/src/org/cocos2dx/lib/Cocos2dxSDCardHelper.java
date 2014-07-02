package org.cocos2dx.lib;

import java.io.File;

import android.os.Environment;
import android.util.Log;

public class Cocos2dxSDCardHelper{
	public static boolean hasSDCard() {
		return Environment.getExternalStorageState().equals(android.os.Environment.MEDIA_MOUNTED);
	}
	
	public static String getSDCardPath() {
		if(hasSDCard()) {
			String SDCardPath = Environment.getExternalStorageDirectory().toString();
			String packageName = Cocos2dxActivity.getCocos2dxPackageName();
			String toCreate = SDCardPath.concat("/Android");
			File file = new File(toCreate); 
			if(!file.exists()) 
			{
				file.mkdir();
			}
			
			toCreate = toCreate.concat("/data");
			file = new File(toCreate);
			if(!file.exists()) {
				file.mkdir();
			}
			
			toCreate = toCreate.concat("/" + packageName);
			file = new File(toCreate);
			if(!file.exists()) {
				file.mkdir();
			}
			
			toCreate = toCreate.concat("/files");
			file = new File(toCreate);
			if(!file.exists()) {
				file.mkdir();
			}
			
			return toCreate;
		}
		
		return "";
	}
}