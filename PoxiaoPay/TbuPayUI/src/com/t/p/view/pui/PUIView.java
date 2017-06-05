package com.t.p.view.pui;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Dialog;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import com.t.p.ca.PUICallBack;
import com.t.p.co.PPointUIInfo;
import com.t.p.co.PPointUIManage;
import com.t.p.co.UIElementInfo;
import com.t.p.co.UIElementInfo.ELEMENTTYPE;
import com.t.p.util.BitmapUtil;

public class PUIView extends View {

	private Context context;
	private Dialog dialog;
	private PUICallBack pUICallBack;// UI返回值
	private PPointUIInfo ele_infos;// 计费点UI界面信息
	private List<UIElementInfo> buttons;// 所有可点击按钮
	private boolean touchEnable = false;

	public PUIView(Context context, Dialog dialog, int ppoint,
			String pluginName, PUICallBack callback) {
		super(context);
		this.context = context;
		this.dialog = dialog;
		this.pUICallBack = callback;
		int ui_point = PPointUIManage.getInstance().getPUIPointByPPoint(
				context, pluginName, ppoint);
		Log.i("TBU_DEBUG","PUIView--> constructor,ui_point = "+ui_point);
		ele_infos = PPointUIManage.getInstance().getPPointUIInfo(context,
				ui_point);
		buttons = checkUIInfo(ele_infos.getElementInfos());
	}

	private void doDelayTimer() {
		Timer myTimer = new Timer();
		TimerTask myTimerTask = new TimerTask() {
			@Override
			public void run() {
				touchEnable = true;
			}
		};
		myTimer.schedule(myTimerTask, 500);
	}

	@Override
	protected void onDraw(Canvas canvas) {
		for (UIElementInfo uiInfo : ele_infos.getElementInfos()) {
			// 获取默认图片
			Bitmap defaultBitmap = null;
			if (null != uiInfo.getDefaultName()) {
				try {
					defaultBitmap = BitmapUtil.loadBitmap(context,
							uiInfo.getSpecialName());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					defaultBitmap = BitmapUtil.loadBitmap(context.getAssets(),
							uiInfo.getDefaultName());
				} catch (Exception e) {
					defaultBitmap = BitmapUtil.loadBitmap(context.getAssets(),
							uiInfo.getDefaultName());				}

			} else {
				defaultBitmap = null;
			}
			// 获取二态图片
			Bitmap specialBitmap = null;
			if (null != uiInfo.getSpecialName()) {
				try {
					specialBitmap = BitmapUtil.loadBitmap(context,
							uiInfo.getSpecialName());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					specialBitmap = BitmapUtil.loadBitmap(context.getAssets(),
							uiInfo.getSpecialName());
				}catch (Exception e) {
					specialBitmap = BitmapUtil.loadBitmap(context.getAssets(),
							uiInfo.getSpecialName());
				}
				
			} else {
				specialBitmap = null;
			}
			// 按类型进行绘制
			if (uiInfo.getType() == ELEMENTTYPE.CONFIRMBUTTON
					|| uiInfo.getType() == ELEMENTTYPE.CANCELBUTTON) {
				if (uiInfo.isClicked()) {
					canvas.drawBitmap(specialBitmap, null, uiInfo.getRect(),
							null);
				} else {
					canvas.drawBitmap(defaultBitmap, null, uiInfo.getRect(),
							null);
				}
			} else if (uiInfo.getType() == ELEMENTTYPE.IMAGE) {
				// 图片类型只绘制默认的
				canvas.drawBitmap(defaultBitmap, null, uiInfo.getRect(), null);
			} else {
				Log.e("TBU_DEBUG", "元素类型错误，找不到此类元素 :" + uiInfo.getType());
			}
		}
		if (!touchEnable) {
			doDelayTimer();
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (touchEnable) {
			for (UIElementInfo button : buttons) {
				if (button.getRect().contains((int) event.getX(),
						(int) event.getY())) {
					if (event.getAction() == MotionEvent.ACTION_DOWN
							|| event.getAction() == MotionEvent.ACTION_MOVE) {
						button.setClicked(true);
						invalidate();
					} else if (event.getAction() == MotionEvent.ACTION_UP) {
						button.setClicked(false);
						invalidate();
						if (button.getType() == ELEMENTTYPE.CONFIRMBUTTON) {
							pUICallBack.pConfirm();
						} else {
							pUICallBack.pCancel();
						}
						touchEnable = false;
						dialog.dismiss();
					}
				} else {
					button.setClicked(false);
					invalidate();
				}
			}
		}
		return true;
	}

	/**
	 * 检查单个计费点中间可点击的部分
	 * 
	 * @param elems
	 * @return
	 */
	private List<UIElementInfo> checkUIInfo(List<UIElementInfo> elems) {
		List<UIElementInfo> list = new ArrayList<UIElementInfo>();
		for (UIElementInfo ele : elems) {
			if (ele.getType() == ELEMENTTYPE.CONFIRMBUTTON
					|| ele.getType() == ELEMENTTYPE.CANCELBUTTON) {
				list.add(ele);
			}
		}
		return list;
	}

}
