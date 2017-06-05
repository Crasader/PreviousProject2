package com.candy.futon.dialog;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.Window;

import com.poxiao.ddz.standalone.R;

public class BaseDialog extends DialogFragment {
	
	protected FragmentActivity activityFailSafe;
	
	@Override
	public void show(FragmentManager manager, String tag) {
		FragmentTransaction ft = manager.beginTransaction();
		ft.remove(this);
		ft.add(this, tag);
		ft.commitAllowingStateLoss();
	}


	
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setStyle(DialogFragment.STYLE_NO_TITLE|DialogFragment.STYLE_NO_FRAME, android.R.style.Theme_Black_NoTitleBar_Fullscreen);
		
	}
	
	public class ActualDialog extends Dialog{

		public ActualDialog(Context context) {
			super(context, R.style.publicDialogNotifyStyle);
			setStyle(R.style.publicDialogNotifyStyle, android.R.style.Theme_Black_NoTitleBar_Fullscreen);
			this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		}
		
		
		
		
	}
	
	
	public FragmentActivity getActivityFailSafe() {
		FragmentActivity a = getActivity();
		if(a != null){
			return a;
		}
		return activityFailSafe;
	}
	
	public void setActivityFailSafe(FragmentActivity activityFailSafe) {
		this.activityFailSafe = activityFailSafe;
	}

}
