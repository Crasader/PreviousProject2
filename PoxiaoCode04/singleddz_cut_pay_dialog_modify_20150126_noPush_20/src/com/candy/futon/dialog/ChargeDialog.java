package com.candy.futon.dialog;

import android.app.Dialog;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.TextView;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.util.MessageUtil;
import com.andy.canvasgame.util.ToastUtil;
import com.candy.futon.GameEngine;
import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.domain.ChargeConfig;
import com.candy.futon.domain.GameConfig;
import com.poxiao.ddz.standalone.R;

public abstract class ChargeDialog extends BaseDialog {

	public final static String TAG = "ChargeDialog";
	
	private final static int MSG_RESET_CHARGE_SELECTION = 1;
	
	protected final static int MSG_CONFIRM_PAY = 2;
	
	protected View view;
	
	protected ChargeConfig currentChargeConfig;
	
	protected static Message chargeSuccessMsg;
	

	protected int currentSelectPosition = -1;
	
	private static Message onCancelMsg;
	
	protected final static String CONFIRM_CHARGE_DIALOG_TAG = "confirm_charge_dialog";
	
	protected String prefixString ;

	private boolean preSelectChargeConfig = false;
	
	private long lastConfirmPayTime = 0;
	
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
	}
	
	protected Handler mHandler = new Handler(){
		public void handleMessage(Message msg) {
			if(msg.what == MSG_RESET_CHARGE_SELECTION){
				currentSelectPosition = -1;
				gridViewAdapter.notifyDataSetChanged();
			}else if(msg.what == MSG_CONFIRM_PAY){
				long currentTime = System.currentTimeMillis();
				if(currentTime - lastConfirmPayTime < GameConfig.getInstance().payMinJiange){
					ToastUtil.resultNotify(getActivityFailSafe(), "您点击得太快了，休息一下吧");
					return;
				}
				lastConfirmPayTime = currentTime;
				onCharge();
			}
		};
	};
	
	
	
	private GridViewAdapter gridViewAdapter = new GridViewAdapter();
	
	
	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		preSelectChargeConfig = false;
		final ActualDialog dialog = new ActualDialog(this.getActivityFailSafe()){
			@Override
			public void onBackPressed() {
				super.onBackPressed();
				if(onCancelMsg != null){
					MessageUtil.cloneMsg(onCancelMsg).sendToTarget();
				}
			}
			
			@Override
			public void cancel() {
				// TODO Auto-generated method stub
				super.cancel();
				if(onCancelMsg != null){
					MessageUtil.cloneMsg(onCancelMsg).sendToTarget();
				}
			}
		};
		 
		initView();
		dialog.setContentView(view);
//        dialog.getWindow().setGravity(Gravity.CENTER_HORIZONTAL|Gravity.BOTTOM);
        dialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);
        dialog.setCanceledOnTouchOutside(true);
        
        WindowManager.LayoutParams lp = new WindowManager.LayoutParams();
        lp.copyFrom(dialog.getWindow().getAttributes());
        Resources r = GameEngine.getInstance().getContext().getResources();
        float width = getDialogWidth(r);
        float height = getDialogHeight(r);
        if(GameConstantsService.getInstance().getScreenWidth()>= GameConstantsService.ST_WIDTH){
        	lp.width = (int)width;
        }else{
        	lp.width = WindowManager.LayoutParams.FILL_PARENT;
        }
        lp.height = (int) height;
        dialog.getWindow().setAttributes(lp);
        if(currentChargeConfig != null){
        	preSelectChargeConfig = true;
        }
        return dialog;
	}



	protected float getDialogHeight(Resources r) {
		float height = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 214, r.getDisplayMetrics());
		return height;
	}



	protected float getDialogWidth(Resources r) {
		float width = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 388, r.getDisplayMetrics());
		return width;
	}
	
	

	protected void initView() {
		LayoutInflater inflater = LayoutInflater.from(getActivityFailSafe()); 
		view = inflater.inflate(R.layout.game_dialog_charge_single, null);
		GridView girdView = (GridView) view.findViewById(R.id.grid_view_charge);
		girdView.setAdapter(gridViewAdapter);
		girdView.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {
				currentSelectPosition = position;
				gridViewAdapter.notifyDataSetChanged();
				mHandler.removeMessages(MSG_RESET_CHARGE_SELECTION);
				mHandler.sendEmptyMessageDelayed(MSG_RESET_CHARGE_SELECTION, 100);
				ChargeConfig chargeConfig = (ChargeConfig)gridViewAdapter.getItem(position);
				currentChargeConfig = chargeConfig;
				beforeShowConfirmDialog();
				showConfirmChargeDialog();
				
			}
		});
		this.view.findViewById(R.id.image_view_dialog_close).setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				dismiss();
			}
		});
		
		
	}
	
	
	protected void beforeShowConfirmDialog() {
		// TODO Auto-generated method stub
		
	}



	protected void onChargeResult() {
		int coin = currentChargeConfig.mOriginalCoin + currentChargeConfig.mExtraCoin;
		IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)GameEngine.getInstance().getContext().getApplication();
		futonDdzApplication.addCoin2Hero(coin);
		ToastUtil.resultNotify(GameEngine.getInstance().getContext(), "您已成功充值 "+ coin +" 银币");
		if(chargeSuccessMsg != null){
			MessageUtil.cloneMsg(chargeSuccessMsg).sendToTarget();
		}
		GameConfig.getInstance().chargedUser = true;
		GameConfig.getInstance().isChargedMoney = true;
		GameConfig.getInstance().exceedMaxRoom = true;
		GameConfig.getInstance().payedUser = true;
		GameConfig.getInstance().save(GameEngine.getInstance().getContext());
		this.dismissAllowingStateLoss();
	}

	protected void showConfirmChargeDialog(){
		
	}



	
	



	class GridViewAdapter extends BaseAdapter {

		@Override
		public int getCount() {
			return GameConfig.getInstance().chargeConfigs.length;
		}

		@Override
		public Object getItem(int arg0) {
			return GameConfig.getInstance().chargeConfigs[arg0];
		}

		@Override
		public long getItemId(int arg0) {
			// TODO Auto-generated method stub
			return arg0;
		}

		
		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			View view = convertView;
			if(null == view) {
				view = GameEngine.getInstance().getContext().getLayoutInflater().inflate(R.layout.charge_item, parent, false);
				ViewHolder holder = new ViewHolder();
				holder.mTitle = (TextView)view.findViewById(R.id.text_view_charge_title);
				holder.mSubTitle = (TextView)view.findViewById(R.id.text_view_charge_sub_title);
				view.setTag(holder);
			}
			
			ViewHolder holder = (ViewHolder) view.getTag();
			ChargeConfig chargeConfig = GameConfig.getInstance().chargeConfigs[position];
			String title = getMainHintStr(chargeConfig);
			String subTitle = getSubTitleHintStr(chargeConfig);
			holder.mTitle.setText(title);
			holder.mSubTitle.setText(subTitle);
//			if(position == currentSelectPosition){
//				view.setBackgroundResource(R.drawable.charge_item_bg_pressed);
//			}else{
//				view.setBackgroundResource(R.drawable.charge_item_bg);
//			}
			//TODO
			return view;
		}

		

		

	}
	
	protected String getSubTitleHintStr(ChargeConfig chargeConfig) {
		String subTitle = "加送" + chargeConfig.mExtraCoin +"银币";
		return subTitle;
	}

	protected String getMainHintStr(ChargeConfig chargeConfig) {
		String title = "短信：" + chargeConfig.mPay +"元充"+ chargeConfig.mOriginalCoin +"银币";
		return title;
	}
	
	public class ViewHolder {
		
		public TextView mTitle;
		public TextView mSubTitle;

	}

	public void setChargeSuccessMsg(Message chargeSuccessMsg) {
		this.chargeSuccessMsg = chargeSuccessMsg;
		
	}

	
	protected abstract void onCharge();



	public static void setOnCancelMsg(Message onCancelMsg) {
		ChargeDialog.onCancelMsg = onCancelMsg;
	}



	public void setCurrentChargeConfig(ChargeConfig currentChargeConfig) {
		this.currentChargeConfig = currentChargeConfig;
	}



	public void setPrefixString(String prefixString) {
		this.prefixString = prefixString;
	}
	
	@Override
	public void onResume() {
		super.onResume();
		if(preSelectChargeConfig){
			preSelectChargeConfig = false;
			showConfirmChargeDialog();
		}
	}
	
}
