package com.taomee.adventure;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

public class Util {
	/**
	 * ������������������
	 * 
	 * @return
	 */
	public static String getVersionCode(Context context) {
		String versionName = "";
		try {
			PackageInfo info = context.getPackageManager()
					.getPackageInfo(context.getPackageName(), 0);
			versionName = info.versionName;
		} catch (Exception e) {

		}
		return versionName;
	}

	/**
	 * ���������������������������wifi
	 * @param context
	 * @return
	 */
    public static boolean isWifi(Context context) {  
 	   ConnectivityManager connectivityManager = 
 		   (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);  
 	   NetworkInfo activeNetInfo = connectivityManager.getActiveNetworkInfo();  
 	   if (activeNetInfo != null  && activeNetInfo.getType() == ConnectivityManager.TYPE_WIFI){  
     	        return true;  
     	 }  
     return false;  
    }

	
}
