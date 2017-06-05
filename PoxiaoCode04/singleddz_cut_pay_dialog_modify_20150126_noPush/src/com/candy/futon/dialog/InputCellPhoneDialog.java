package com.candy.futon.dialog;

import android.app.Dialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.EditText;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.util.ToastUtil;
import com.candy.futon.activitys.GameActivity;
import com.candy.futon.service.CellPhoneNumberUpdater;
import com.candy.futon.service.CellPhoneNumberUpdater.CellPhoneUploadListener;
import com.poxiao.ddz.standalone.R;

public class InputCellPhoneDialog extends BaseDialog {

	public final static String TAG = "InputCellPhoneDialog";
	
	private final static int MSG_RESET_CHARGE_SELECTION = 1;
	
	
	protected View view;
	
	protected EditText input;
	
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
	}
	
	
	
	
	
	
	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		final ActualDialog dialog = new ActualDialog(this.getActivityFailSafe()){
			
		};
		initView();
		setStyle(DialogFragment.STYLE_NORMAL, android.R.style.Theme_Black_NoTitleBar_Fullscreen);
		dialog.setContentView(view);
//      dialog.getWindow().setGravity(Gravity.CENTER_HORIZONTAL|Gravity.BOTTOM);
      dialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);
      dialog.setCanceledOnTouchOutside(false);
      
      WindowManager.LayoutParams lp = new WindowManager.LayoutParams();
      lp.copyFrom(dialog.getWindow().getAttributes());
      lp.width = GameConstantsService.getInstance().screenWidth;
      lp.height = GameConstantsService.getInstance().screenHeight;
      
      dialog.getWindow().setAttributes(lp);
      return dialog;
	}
	
	

	protected void initView() {
		LayoutInflater inflater = LayoutInflater.from(getActivityFailSafe()); 
		view = inflater.inflate(R.layout.game_dialog_input_cellphone, null);
		
		input = (EditText)view.findViewById(R.id.edit_text_cell_phone);
		
		this.view.findViewById(R.id.image_btn_submit).setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
				String regex=

				"^\\d{3}-?\\d{8}|\\d{4}-?\\d{8}$"

				; 
				String text = input.getText().toString();
				text = text.trim();
				if(text.matches(regex)){
					ToastUtil.resultNotify(getActivityFailSafe(), "请稍候，正在上传中...");
					if(CellPhoneNumberUpdater.getInstance().isInWorkProcess()){
						ToastUtil.resultNotify(getActivityFailSafe(), "请稍候，正在上传中...");
					}else{
						CellPhoneNumberUpdater.getInstance().setListener(new CellPhoneUploadListener() {
							
							@Override
							public void onUploadDone(final int result) {
								
								GameActivity.getInstance().runOnUiThread(new Runnable() {
									
									@Override
									public void run() {
										if(result == 0){
											InputCellPhoneDialog.this.dismiss();
											ToastUtil.resultNotify(GameActivity.getInstance(), "恭喜，手机号码上传成功");
										}else{
											ToastUtil.resultNotify(GameActivity.getInstance(), "上传失败，请检查网络后重试");
										}
										
									}
								});
							}
						});
						CellPhoneNumberUpdater.getInstance().upload(getActivityFailSafe(), text);
					}
				}else{
					ToastUtil.resultNotify(getActivityFailSafe(), "请输入正确的手机号码");
				}
			}
		});
		
		this.view.findViewById(R.id.image_view_dialog_close).setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				dismiss();
			}
		});
		
		
	}
	
	



	
}
