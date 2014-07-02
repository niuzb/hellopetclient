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


import com.taomee.outInterface.LoginModule;
import com.taomee.outInterface.LoginParams;
import com.taomee.outInterface.RedirectListener;


import android.app.ProgressDialog;
import android.app.Activity;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;

import android.util.Log;
import android.view.ViewGroup;
import android.widget.RelativeLayout;


public class loginactivity extends Activity implements RedirectListener
{

	RelativeLayout relativeLayout ;
	
	public Handler loadingViewHandler = null;
	public Handler loadingProgressHandler = null;
	
	public Handler exitHandler = null;
	
	
	protected void onCreate(Bundle savedInstanceState){
		
		super.onCreate(savedInstanceState);
        
		this.SetupLogin();
	}

    private void SetupLogin()
    {   	

		relativeLayout = new RelativeLayout(this);
        ViewGroup.LayoutParams framelayout_params =
                new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                           ViewGroup.LayoutParams.MATCH_PARENT);
		this.addContentView(relativeLayout, framelayout_params);

		LoginParams.gameId = 76; // 闁荤姵鍔х粻鎴ｃ亹閸ф宓侀柛鎰絻闁伴亶鏌涢幒鎴烆棶闁告ǜ鍊濋幆鍐礋椤掑倸鐓戦梺瑙勬綑缁�
		LoginParams.sinaAppKey = "4137517185"; // 闁荤姴娲弨鍗灻瑰☉銏犵闁靛繆锟芥禍鍫曟煕閿斿搫濡介柡灞斤工闇夋い蹇撳缁ㄦ娊鏌涘Δ浣藉缂佽鲸鍨垮銊╁箚瑜旈幐顒勬煕濞嗘劕顥楅柡浣烘暩閹风姵顦兼惔銏㈡殸appkey
		LoginParams.sinaAppSecret = "77f412fd9765e2ec31b1f9966af0891d"; // 闁荤姴娲弨鍗灻瑰☉銏犵闁靛繆锟芥禍鍫曟煕閿斿搫濡介柡灞斤工闇夋い蹇撳缁ㄦ娊鏌涘Δ浣藉缂佽鲸鍨垮銊╁箚瑜旈幐顒勬煕濞嗘劕顥楅柡浣烘暩閹风姵顦兼惔銏㈡殸appsecrect
		LoginParams.sinaRedirectUrl = "https://api.weibo.com/oauth2/default.html"; // 闁荤姴娲弨鍗灻瑰☉銏犵闁靛繆锟芥禍鍫曟煕閿斿搫濡介柡灞斤工闇夋い蹇撳缁ㄦ娊鏌涘Δ浣藉缂佽鲸鍨垮銊╁箚瑜旈幐顒勬煕濞嗘劕顥楅柡浣烘暩閹风姵顦兼惔銏㈡殸闂佹悶鍎抽崑鐘绘儍閻旂厧鎹堕柡澶嬪缁诧拷		LoginParams.tencentAppKey = "801262639";// 闁荤姴娲弨鍗灻瑰☉銏犵闁靛繆锟芥禍鍫曟煕閿斿搫濮�柛姘焽閹峰顢涘顐や亢闂佸憡顨濋懝鍓ф閹达箑缁╅柟顖嗗洦灏欓梺鍛婄懄婢瑰棝寮悽鍨珰濡炲瀛╅悾鐩縫pkey
		LoginParams.tencentAppSecret = "a099fedaa07c76b27d6055c130b32041";// 闁荤姴娲弨鍗灻瑰☉銏犵闁靛繆锟芥禍鍫曟煕閿斿搫濮�柛姘焽閹峰顢涘顐や亢闂佸憡顨濋懝鍓ф閹达箑缁╅柟顖嗗洦灏欓梺鍛婄懄婢瑰棝寮悽鍨珰濡炲瀛╅悾鐩縫psecrect
		LoginParams.tencentRedirectUrl = "https://itunes.apple.com/cn/app/mo-er-zhuang-yuan/id468988417?mt=8"; // 闁荤姴娲弨鍗灻瑰☉銏犵闁靛繆锟芥禍鍫曟煕閿斿搫濮�柛姘焽閹峰顢涘顐や亢闂佸憡顨濋懝鍓ф閹达箑缁╅柟顖嗗洦灏欓梺鍛婄懄婢瑰棝寮悽鍨珰濡炲瀛╅悾閬嶆煕閵壯冧哗闁汇劎鍠栧畷鐑藉级閹稿海绁�		//闂佽皫鍡╁殭缂傚秴绉归獮鎺楀Ψ閵夈儳绋�		
		LoginModule loginModule = new LoginModule(loginactivity.this,
				relativeLayout, (RedirectListener) loginactivity.this);
		LoginModule.doLogin();	
    }
    
	
	public void onComplete(String arg0, String arg1) {
		// TODO Auto-generated method stub
		//闂備浇鐨崱鈺佹缂傚倸绉寸粔褰掔嵁鐎ｎ喖绠涙い鎺炴嫹閻忓洦绻濋姀锝嗙【閻庢凹鍣ｉ獮鍐晸閿燂拷	relativeLayout.removeAllViews();
		Log.i("onComplete: ", arg0 + " , "+arg1);
		System.out.println("success");			
		
		Intent intent = new Intent();
	    intent.putExtra("arg0", arg0);
	    intent.putExtra("arg1", arg1);
		
		intent.setClass(loginactivity.this, adventure.class);			
		startActivity(intent);
		loginactivity.this.finish();		
	}

	@Override
	public void onConnectTimeout() {
		// TODO Auto-generated method stub
		Log.i("onConnectTimeout", "onConnectTimeout");
	}

	@Override
	public void onErro(int arg0) {
		// TODO Auto-generated method stub
		Log.i("onErro", arg0+"");
	}
	
	@Override  
	protected void onResume() {  
		 /** 
		  * 閻犱礁澧介悿鍡樼▔閻戞◤顓犱沪閿燂拷		  */  
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

	private static void logOut()
	{
		LoginModule.doLogout();
	}	
}

