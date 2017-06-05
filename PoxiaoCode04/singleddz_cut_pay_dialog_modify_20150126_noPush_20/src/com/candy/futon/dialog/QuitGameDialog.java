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
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.andy.canvasgame.util.MessageUtil;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.service.DownloadService;
import com.poxiao.ddz.standalone.R;

public class QuitGameDialog extends BaseDialog {

	private View view;
	
	private LinearLayout quitBtnLayout;
	
	private ImageButton mustQuitBtn;
	
	private ImageButton cancelQuitBtn;
	
	private ImageButton normalQuitBtn;
	
	private ImageButton closeBtn;
	
	private ImageView [] gameBtns = new ImageView[DownloadService.PROMOTE_GAMES.length];
	
	private ImageView[] gameTextBtns = new ImageView[DownloadService.PROMOTE_GAMES.length];
	
	private ProgressBar[] gameProgress = new ProgressBar[DownloadService.PROMOTE_GAMES.length];
	
	private TextView textViewTip;
	
	private Message quitMsg;
	
	private Message cancelMsg;
	
	private String tipString;
	
	private Message downloadMsg;
	
	public QuitGameDialog(){
		super();
		
	}
	
	public void setMsgs(Message quitMsg, Message cancelMsg, Message downloadMsg){
		this.quitMsg = quitMsg;
		this.cancelMsg = cancelMsg;
		this.downloadMsg = downloadMsg;
	}
	
	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		 
		final ActualDialog dialog = new ActualDialog(this.getActivityFailSafe());
		 
		initView();
		dialog.setContentView(view);
//        dialog.getWindow().setGravity(Gravity.CENTER_HORIZONTAL|Gravity.BOTTOM);
        dialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);
        
        dialog.setCanceledOnTouchOutside(true);
        dialog.setCancelable(true);
        WindowManager.LayoutParams lp = new WindowManager.LayoutParams();
        lp.copyFrom(dialog.getWindow().getAttributes());
        Resources r = getActivityFailSafe().getResources();
        float width = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 380, r.getDisplayMetrics());
        float height = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 200, r.getDisplayMetrics());
        
        lp.width = (int) width;
        
        lp.height = (int) height;
        dialog.getWindow().setAttributes(lp);

        
        return dialog;
	}

	private void initView() {
		LayoutInflater inflater = LayoutInflater.from(getActivityFailSafe()); 
		view = inflater.inflate(R.layout.game_dialog_quit_game_a, null);
		mustQuitBtn = (ImageButton)view.findViewById(R.id.image_btn_must_quit);
		cancelQuitBtn = (ImageButton)view.findViewById(R.id.image_btn_cancel_quit);
		textViewTip = (TextView)view.findViewById(R.id.text_view_quit_game_tip);
		mustQuitBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if(quitMsg != null){
					MessageUtil.cloneMsg(quitMsg).sendToTarget();
				}
				QuitGameDialog.this.dismiss();
			}
		});
		
		OnClickListener quitListener = new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if(cancelMsg != null){
					MessageUtil.cloneMsg(cancelMsg).sendToTarget();
				}
				QuitGameDialog.this.dismiss();
			}
		};
		cancelQuitBtn.setOnClickListener(quitListener);
		
		
		closeBtn = (ImageButton)view.findViewById(R.id.image_close_dialog);
		closeBtn.setOnClickListener(quitListener);
		
		quitBtnLayout = (LinearLayout)view.findViewById(R.id.layout_quit_and_Lose_money);
		normalQuitBtn = (ImageButton)view.findViewById(R.id.image_btn_normal_quit);
		
		normalQuitBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if(quitMsg != null){
					MessageUtil.cloneMsg(quitMsg).sendToTarget();
				}
				QuitGameDialog.this.dismiss();
			}
		});
		
		int gameBtnIds[] = new int[]{R.id.image_view_ddz_btn_big, R.id.image_view_qbsk_btn_big};
		int gameTextBtnIds[] = new int[]{R.id.image_view_ddz_text, R.id.image_view_qbsk_text};
		int gameProgressIds[] = new int[]{R.id.progress_bar_download_ddz, R.id.progress_bar_download_qbsk};
		
		for(int i=0;i<gameBtnIds.length;i++){
			gameBtns[i] = (ImageView)view.findViewById(gameBtnIds[i]);
			gameTextBtns[i] =(ImageView)view.findViewById(gameTextBtnIds[i]);
			gameProgress[i] = (ProgressBar)view.findViewById(gameProgressIds[i]);
			updateGameProgress(i);
			final int index  = i;
			if(GameConfig.getInstance().noPromote){
				gameBtns[i].setVisibility(View.INVISIBLE);
				gameTextBtns[i].setVisibility(View.INVISIBLE);
			}
			gameBtns[i].setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View v) {
					Message msg = Message.obtain(downloadMsg);
					msg.arg1 = index;
					msg.sendToTarget();
				}
			});
			
			gameTextBtns[i].setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View v) {
					Message msg = Message.obtain(downloadMsg);
					msg.arg1 = index;
					msg.sendToTarget();
				}
			});
		}
		updateByTipString();
	}

	protected void updateGameProgress(int i) {
		if(DownloadService.getInstance().isInProgress(DownloadService.PROMOTE_GAMES[i])){
			gameProgress[i].setProgress(DownloadService.getInstance().getCurrentProgress(i));
			gameProgress[i].setVisibility(View.VISIBLE);
		}else{
			gameProgress[i].setVisibility(View.INVISIBLE);
		}
	}
	
	public void setTipString(String tip){
		this.tipString = tip;
		updateByTipString();
	}

	protected void updateByTipString() {
		if(textViewTip == null){
			return;
		}
		if(tipString == null){
			quitBtnLayout.setVisibility(View.INVISIBLE);
			normalQuitBtn.setVisibility(View.VISIBLE);
		}else{
			textViewTip.setText(tipString);
			quitBtnLayout.setVisibility(View.VISIBLE);
			textViewTip.setVisibility(View.VISIBLE);
			normalQuitBtn.setVisibility(View.INVISIBLE);
		}
	}
	
	public void updateDownloadProgress(int index, int progress){
		if(gameProgress[index] == null){
			return;
		}
		this.gameProgress[index].setVisibility(View.VISIBLE);
		this.gameProgress[index].setProgress(progress);
	}
	
	@Override
	public void onResume() {
		super.onResume();
		for(int i=0;i<gameProgress.length;i++){
			updateGameProgress(i);
		}
	}
	
	public void hideDownloadProgress(int index){
		if(gameProgress[index] == null){
			return;
		}
		this.gameProgress[index].setVisibility(View.INVISIBLE);
	}
	
}
