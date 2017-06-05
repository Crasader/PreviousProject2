package com.candy.futon.view;

import android.content.Context;
import android.graphics.Rect;

import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.util.AViewUtil;
import com.andy.canvasgame.util.BitmapSpliter;
import com.andy.canvasgame.util.MyGravity;
import com.andy.canvasgame.view.BlankView;
import com.poxiao.ddz.standalone.R;

public class RoomChangeView extends BlankView{

	private int from;
	
	private int to;
	
	private int width;
	
	private int contentWidth;
	
	private boolean roomUp;
	
	private static int HEIGHT = 40;
	
	private static int PREFER_WIDTH = 372;

	private static boolean inited = false;
	
	
	private NinePatchAView bgView;
	
	private ImageAView gongxiView, beijuView;
	
	private ImageAView pointView;
	
	private ImageNumberAView fromNumberView;
	
	private ImageNumberAView toNumberView;
	
	private ImageAView roomUpView, roomDownView;
	
	public RoomChangeView(Context context, int width){
		if(!inited){
			inited = true;
			HEIGHT *= GameConstantsService.getInstance().getDensityScale();
			PREFER_WIDTH *= GameConstantsService.getInstance().getDensityScale();
		}
		this.width = width;
		bgView = new NinePatchAView(context, R.drawable.room_change_tip_bg);
		gongxiView = new ImageAView(context, R.drawable.room_change_gongxi);
		beijuView = new ImageAView(context, R.drawable.room_change_beiju);
		
		pointView = new ImageAView(context, R.drawable.room_change_point_from_to);
		
		fromNumberView = new ImageNumberAView(context, R.drawable.room_change_num, 10, BitmapSpliter.HORIZONTAL);
		toNumberView = new ImageNumberAView(context, R.drawable.room_change_num, 10, BitmapSpliter.HORIZONTAL);
		
		roomUpView = new ImageAView(context, R.drawable.room_change_upgrade);
		roomDownView = new ImageAView(context, R.drawable.room_change_downgrade);
		
		this.addChild(bgView);
		this.addChild(gongxiView);
		this.addChild(beijuView);
		this.addChild(pointView);
		
		this.addChild(fromNumberView);
		this.addChild(toNumberView);
		
		this.addChild(roomUpView);
		this.addChild(roomDownView);
		this.setBounds(new Rect(0,0,PREFER_WIDTH,HEIGHT));
	}
	
	public void setParam(boolean roomUp, int from, int to){
		this.roomUp = roomUp;
		this.from = from;
		this.to = to;
		
		this.fromNumberView.setNumber(from);
		this.toNumberView.setNumber(to);
		
		ImageAView gongxiOrBeiju = roomUp? gongxiView:beijuView;
		ImageAView roomUpOrDownView = roomUp? roomUpView: roomDownView;
		
		contentWidth = gongxiOrBeiju.getBounds().width() + pointView.getBounds().width() + 
				fromNumberView.getBounds().width() +
				roomUpOrDownView.getBounds().width() + 
				toNumberView.getBounds().width();
		
		width = Math.max(PREFER_WIDTH, this.width);
		this.getBounds().set(0, 0, width, HEIGHT);
		
	}
	
	@Override
	public void updateBounds() {
		
		bgView.setBounds(this.getBounds());
		
		gongxiView.setAlpha(0);
		beijuView.setAlpha(0);
		roomUpView.setAlpha(0);
		roomDownView.setAlpha(0);
		
		ImageAView gongxiOrBeiju = roomUp? gongxiView:beijuView;
		ImageAView roomUpOrDownView = roomUp? roomUpView: roomDownView;
		
		gongxiOrBeiju.setAlpha(AView.FULL_OPAQUE);
		roomUpOrDownView.setAlpha(AView.FULL_OPAQUE);
		
		AView[] views = new AView[]{
				gongxiOrBeiju, pointView, fromNumberView, roomUpOrDownView, toNumberView
		};
		
		int left = getBounds().left + (width - contentWidth)/2;
		
		for(AView view:views){
			int top = getBounds().top + (getBounds().height() - view.getBounds().height())/2;
			view.getBounds().set(left, top, left+view.getBounds().width(), top+view.getBounds().height());
			left = view.getBounds().right;
		}
	}
	
	@Override
	public void startAnimation(android.view.animation.Animation animation) {
		synchronized (childLock) {
			int childLen = mChilds.size();
			for(int i=0;i<childLen;i++){
				AView child = mChilds.get(i);
				child.startAnimation(animation);
			}
		}
	}
}
