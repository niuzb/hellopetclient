package com.taomee.adventure;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

import android.content.Context;
import android.util.Log;

public class UploadCrashInfo {
	public static void upload(Context context, String gameName) {
		try {
			File file = context.getCacheDir();
			////File file = Environment.getExternalStorageDirectory();
			File uploadfile = new File(file, "app.dmp");
			if (!uploadfile.exists() || !Util.isWifi(context)) {
				Log.e("e1", "������������������������wifi");
				return;
			}
			final File tempfile = new File(file, "temp.dmp");
			uploadfile.renameTo(tempfile);

			final String requestUrl = "http://10.1.1.5/cc/wareless/ser/dumpfile.php";
			// ������������������
			final Map<String, String> params = new HashMap<String, String>();
			params.put("gametype", gameName);
			params.put("version", Util.getVersionCode(context));
			// ������������
			final FormFile formfile = new FormFile(tempfile.getName(),
					tempfile, "crashInfo", "application/octet-stream");
			new Thread() {
				@Override
				public void run() {
					try {
						SocketHttpRequester.post(requestUrl, params, formfile);
						tempfile.delete();
						Log.e("suc", "������");
					} catch (Exception e) {
						Log.e("e2", "������������");
					}
				}

			}.start();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
