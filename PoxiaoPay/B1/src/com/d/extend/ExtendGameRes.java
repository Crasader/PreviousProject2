package com.d.extend;

import com.d.extend.moreapp.LayoutUtil;
import com.poxiao.xbllpay.R;
import com.t.p.view.PLayoutUtil;

public class ExtendGameRes {
	public static void initResources() {
		// 支付dialog框的样式
		PLayoutUtil.setPUiLayoutResId(R.style.dialog_game_style);
		// 更多游戏的资源配置
		LayoutUtil.setMoreGameLayoutResId(R.layout.dialog_more_game);
		LayoutUtil.setMoreGamedialogStyleResId(R.style.dialog_game_style);
		LayoutUtil.setMoreGameNoDataTipResId(R.id.no_other_game_tip);
		LayoutUtil.setMoreGameCancelBtnResId(R.id.more_game_cancle);
		LayoutUtil.setMoreGameGridViewResId(R.id.more_game_view);
		LayoutUtil.setMoreGameViewItemLayoutResId(R.layout.more_game_view_item);
		LayoutUtil.setMoreGameViewItemGameIconResId(R.id.game_icon);
		LayoutUtil.setMoreGameViewItemGameNameResId(R.id.game_name);
		// 退出游戏Dialog
		LayoutUtil.setQuitGameLayoutResId(R.layout.dialog_quit_game);
		LayoutUtil.setQuitGameContinueBtnResId(R.id.quit_game_continue);
		LayoutUtil.setQuitGameCaccelBtnResId(R.id.qiut_game_cancel);
		LayoutUtil.setQuitGameQuitBtnResId(R.id.qiut_game_quit);

	}
}
