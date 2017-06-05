package com.tbu.hd.dialog;

import android.app.Dialog;
import android.content.Context;
import android.view.MotionEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;

import com.tbu.hd.HdUtils;
import com.tbu.hd.manage.HdConfig;
import com.tbu.hd.manage.HotCallback;

public class HdDialog extends Dialog {

	private ImageButton cancel;
	private ImageButton commit;
	private EditText text;
	private Context context;
	private HotCallback hotCallback;

	public HdDialog(Context context, HotCallback hotCallback) {
		super(context, HdDialogRes.getHdDialogStyleResId());
		this.context = context;
		this.hotCallback = hotCallback;
		setContentView(HdDialogRes.getHdDialogLayoutResId());
		initView();
	}

	private void initView() {
		text = (EditText) findViewById(HdDialogRes.getHdDialogTextResId());
		text.setOnTouchListener(new View.OnTouchListener() {

			@Override
			public boolean onTouch(View v, MotionEvent event) {
				if ("请输入手机号码".trim().equals(text.getText().toString().trim()))
					text.setText("");
				return false;
			}
		});
		cancel = (ImageButton) findViewById(HdDialogRes
				.getHdDialogCancelResId());
		cancel.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				hotCallback.update();
				dismiss();
			}
		});
		commit = (ImageButton) findViewById(HdDialogRes
				.getHdDialogConfirmResId());
		commit.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// 上传信息
				HdUtils.uploadHdInfo(text.getText().toString(),
						HdConfig.getHdContent());
				hotCallback.update();
				dismiss();
			}
		});
	}
}
