package com.candy.futon.dialog;

import android.app.Dialog;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;

import com.andy.canvasgame.settings.GameSetting;
import com.poxiao.ddz.standalone.R;

public class SettingDialog extends BaseDialog {

	private View view;
	
	private SeekBar volumeSeekBar;
	
	private CheckBox cbSoundEffect;
	
	private CheckBox cbBgMusic;
	
	private CheckBox cbViberate;
	
	private CheckBox cbSaveBattery;
	
	
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
        float width = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 388, r.getDisplayMetrics());
        float height = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 210, r.getDisplayMetrics());
        lp.width =(int) width;
        lp.height = (int) height;
        dialog.getWindow().setAttributes(lp);
        return dialog;
	}



	private void initView() {
		LayoutInflater inflater = LayoutInflater.from(getActivityFailSafe()); 
		view = inflater.inflate(R.layout.game_dialog_settings, null);
		volumeSeekBar = (SeekBar) view.findViewById(R.id.seek_bar_sound_volume);
		cbBgMusic = (CheckBox) view.findViewById(R.id.check_box_bg_music);
		cbSaveBattery = (CheckBox)view.findViewById(R.id.check_box_save_battery);
		cbSoundEffect = (CheckBox)view.findViewById(R.id.check_box_sound_effect);
		cbViberate = (CheckBox)view.findViewById(R.id.check_box_viberate);
		
		volumeSeekBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				GameSetting.getInstance().setSoundVolume(getActivityFailSafe(), progress);
				GameSetting.getInstance().setMusicVolume(getActivityFailSafe(), progress);
				
			}
		});
		
		cbBgMusic.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			
			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				GameSetting.getInstance().setEnableMusic(getActivityFailSafe(), isChecked);
			}
		});
		
		cbSaveBattery.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			
			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				cbBgMusic.setChecked(!isChecked);
				cbSoundEffect.setChecked(!isChecked);
				cbViberate.setChecked(!isChecked);
				GameSetting.getInstance().setEnableSaveBattery(getActivityFailSafe(), isChecked);
			}
		});
		
		cbSoundEffect.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			
			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				GameSetting.getInstance().setEnableSound(getActivityFailSafe(), isChecked);
			}
		});
		cbViberate.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			
			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				GameSetting.getInstance().setEnableVibrate(getActivityFailSafe(), isChecked);
			}
		});
		view.findViewById(R.id.image_view_dialog_close).setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				dismiss();
			}
		});
		updateView();
		
	}

	@Override
	public void onResume() {
		super.onResume();
		updateView();
	}

	public void updateView() {
		volumeSeekBar.setProgress(GameSetting.getInstance().getSoundVolume());
		cbBgMusic.setChecked(GameSetting.getInstance().isEnableMusic());
		cbSaveBattery.setChecked(GameSetting.getInstance().isEnableSaveBattery());
		cbSoundEffect.setChecked(GameSetting.getInstance().isEnableSound());
		cbViberate.setChecked(GameSetting.getInstance().isEnableVibrate());
	}
	
}
