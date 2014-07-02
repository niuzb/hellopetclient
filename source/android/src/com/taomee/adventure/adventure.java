/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.taomee.adventure;

import java.io.File;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RelativeLayout;


public class adventure extends Cocos2dxActivity 
{
	RelativeLayout relativeLayout ;
	
	protected void onCreate(Bundle savedInstanceState){
		
		super.onCreate(savedInstanceState);
		 Intent intent1 = getIntent();
	        
	    // ���intent1.getStringExtra()������������������ACTIVITY������������������������
	    String arg0 = intent1.getStringExtra("arg0");  
	    String arg1 = intent1.getStringExtra("arg1");
	    Login(arg0, arg1);
	    getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);	    
	    
	  //Replace android_imole with your app name.
	  UploadCrashInfo.upload(adventure.this, "android_imole");
	  File f = adventure.this.getCacheDir();
	  setDumpPathJNI(f.toString());
	}
	
	public native void setDumpPathJNI(String path);
	
    static {
         System.loadLibrary("gamelogic");
         System.loadLibrary("crashme");
    }

    public void Login(String arg0, String arg1)
    {
    	loginSuccess(arg1,arg0);
    }
	
	
	@Override  
	protected void onResume() {  
		 /** 
		  * ��������������� 
		  */  
		 if(getRequestedOrientation()!=ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE ){  
		    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);  
		 }  
		 super.onResume();  
	} 

	@Override
	public void onConfigurationChanged(Configuration newConfig){
		if (newConfig.orientation != Configuration.ORIENTATION_LANDSCAPE ){
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		}	
		
		super.onConfigurationChanged(newConfig);
	}
	
	private static native void loginSuccess(String session,String uuid);
	
	private void keepScreenOn(int lock){
		System.out.println("in keepScreenOn");
		//getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		if(lock == 0){
			//getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		}
		else{
			//getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		}
	}
}

