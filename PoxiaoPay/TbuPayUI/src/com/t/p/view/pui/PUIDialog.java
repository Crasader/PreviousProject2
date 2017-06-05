package com.t.p.view.pui;

import android.app.Dialog;
import android.content.Context;
import android.util.Log;

import com.t.p.ca.PUICallBack;
import com.t.p.view.PLayoutUtil;

public class PUIDialog extends Dialog {

	private PUICallBack callback;

	/**
	 * 
	 * @param context
	 * @param ppoint
	 *            计费点编号
	 * @param special
	 * @param callback
	 *            UI界面的操作结果
	 */
	public PUIDialog(Context context, int ppoint, String pluginName,
			PUICallBack callback) {
		super(context,PLayoutUtil.getPUiLayoutResId());
		this.callback = callback;
		setContentView(new PUIView(context, PUIDialog.this, ppoint,
				pluginName, callback));
	}

	@Override
	public void onBackPressed() {
		super.onBackPressed();
		if (callback != null) {
			callback.pCancel();
		} else {
			Log.e("TBU_DEBUG",
					"PUIDialog onBackPressed, but callback is null");
		}
	}
}
