package com.candy.futon.widget;

import java.text.SimpleDateFormat;
import java.util.Date;

import android.widget.TextView;

public class CurrentTimeTextViewWidget {

	private TextView currentTimeView;
	
	private SimpleDateFormat df = new SimpleDateFormat("HH:mm");
	
	public CurrentTimeTextViewWidget(TextView textView){
		this.currentTimeView = textView;
	}
	
	public void updateTime(){
		Date date = new Date();
		this.currentTimeView.setText(df.format(date));
	}
}
