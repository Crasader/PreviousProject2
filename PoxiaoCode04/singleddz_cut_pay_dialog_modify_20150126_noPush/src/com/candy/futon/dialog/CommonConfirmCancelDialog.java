package com.candy.futon.dialog;

import android.app.Dialog;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.Message;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import com.andy.canvasgame.util.MessageUtil;
import com.poxiao.ddz.standalone.R;

public class CommonConfirmCancelDialog extends BaseDialog {

	private View view;
	
	private TextView textViewMessage;
	
	private ImageButton btnConfirm;
	
	private ImageButton btnCancel;
	
	private View btnClose;
	
	private ImageView imageViewTitle;
	
	private Message confirmMsg;
	
	private Message closeMsg;
	
	private int titleDrawId;
	
	private int confirmDrawId;
	
	private String message;
	
	private boolean isShowCancelBtn = false;
	
	private boolean isShowCloseBtn = true;
	
	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		 
		final ActualDialog dialog = new ActualDialog(this.getActivityFailSafe());
		 
		initView();
		dialog.setContentView(view);
//        dialog.getWindow().setGravity(Gravity.CENTER_HORIZONTAL|Gravity.BOTTOM);
        dialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);
        dialog.setCanceledOnTouchOutside(true);
        
        WindowManager.LayoutParams lp = new WindowManager.LayoutParams();
        lp.copyFrom(dialog.getWindow().getAttributes());
        Resources r = getActivityFailSafe().getResources();
        float width = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 340, r.getDisplayMetrics());
        float height = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 178, r.getDisplayMetrics());
        lp.width = (int) width;
        lp.height = (int)height;

        dialog.getWindow().setAttributes(lp);
        if(!this.isShowCancelBtn){
        	this.btnCancel.setVisibility(View.GONE);
        }else{
        	this.btnCancel.setVisibility(View.VISIBLE);
        }
        
        if(!this.isShowCloseBtn){
        	this.btnClose.setVisibility(View.GONE);
        }else{
        	this.btnClose.setVisibility(View.VISIBLE);
        }
        return dialog;
	}
	
	
	
	
	public void setShowCancelBtn(boolean isShowCancelBtn) {
		this.isShowCancelBtn = isShowCancelBtn;
	}




	private void initView() {
		LayoutInflater inflater = LayoutInflater.from(getActivityFailSafe()); 
		view = inflater.inflate(R.layout.game_dialog_confirm_cancel, null);
		textViewMessage = (TextView)view.findViewById(R.id.text_view_confirm_dialog_message);
		this.btnClose = view.findViewById(R.id.image_view_confirm_dialog_close);
		this.btnConfirm = (ImageButton)view.findViewById(R.id.image_btn_confirm_dialog_confirm);
		this.btnCancel = (ImageButton)view.findViewById(R.id.image_btn_confirm_dialog_cancel);
		this.imageViewTitle = (ImageView)view.findViewById(R.id.image_view_confirm_dialog_title);
		if(titleDrawId != 0){
			this.imageViewTitle.setImageResource(titleDrawId);
		}
		if(confirmDrawId != 0){
			this.btnConfirm.setImageResource(confirmDrawId);
		}
		if(message != null){
			this.textViewMessage.setText(message);
		}
		
		this.btnClose.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				onBtnClose();
			}
		});
		
		this.btnConfirm.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				onBtnConfirm();
			}
		});
		
		this.btnCancel.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				onBtnClose();
			}
		});
	}

	protected void onBtnConfirm() {
		if(confirmMsg != null){
			MessageUtil.cloneMsg(confirmMsg).sendToTarget();
		}
		this.dismiss();
	}

	protected void onBtnClose() {
		if(closeMsg != null){
			MessageUtil.cloneMsg(closeMsg).sendToTarget();
		}
		this.dismiss();
	}

	public void setConfirmMsg(Message confirmMsg) {
		this.confirmMsg = confirmMsg;
	}

	public void setCloseMsg(Message closeMsg) {
		this.closeMsg = closeMsg;
	}

	public void setTitleDrawId(int titleDrawId) {
		this.titleDrawId = titleDrawId;
		if(this.imageViewTitle != null){
			this.imageViewTitle.setImageResource(titleDrawId);
		}
	}

	public void setConfirmDrawId(int confirmDrawId) {
		this.confirmDrawId = confirmDrawId;
		if(this.btnConfirm != null){
			this.btnConfirm.setImageResource(confirmDrawId);
		}
	}

	public void setMessage(String message) {
		this.message = message;
		if(this.textViewMessage != null){
			this.textViewMessage.setText(message);
		}
	}
	
	public void setShowCloseBtn(boolean isShowCloseBtn) {
		this.isShowCloseBtn = isShowCloseBtn;
	}
	
	
}
