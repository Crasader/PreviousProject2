package com.candy.futon.view;

import com.andy.canvasgame.service.GameConstantsService;

/**
 * 记录View的坐标
 * @author Andy
 *
 */
public class ViewPosition {

	public int SELF_PLAYER_BUTTONS_MARGIN_BOTTOM = 130;
	
	public int CALL_LOAD_BTNS_MARGIN_LEFT_IN_SMALL_SCREEN = 40;
	
	public int SELF_PLAYER_BUTTONS_PADDING = 18;
	
	public int START_BTN_MARGIN_BOTTOM = 130;
	
	public int ACTION_SHOW_MARGIN_LEFT = 8;
	
	public int PASS_VIEW_MARGIN_BOTTOM = 25;
	
	public int CALL_LOAD_MARGIN_BOTTOM = 28;
	
	public int HURDLE_IMAGE_MARGIN_TOP = 118;
	
	private static ViewPosition instance;
	
	public int SLING_POINTER_MOVE_X =400;
	
	public int CARD_REMAINDER_BTN_MARGINX = 2;
	
	public int CARD_REMAINDER_BTN_MARGINY = 2;
	
	public int CARD_REMAINDER_BG_PADDING_LEFT = 8;
	
	public int CARD_REMAINDER_BG_PADDING_TOP = 8;
	
	public int CARD_REMAINDER_BG_PADDING_RIGHT = 8;
	
	public int CARD_REMAINDER_BG_PADDING_BOTTOM = 8;
	
	public int CARD_REMAINDER_CARD_NUM_MARGIN_TOP = 8;
	
	public int CARD_REMAINDER_CARD_NUM_FG_EXPANDING_TOP = 2;
	
	public int CARD_REMAINDER_CARD_NUM_FG_EXPANDING_BOTTOM = 2;
	
	public int CARD_REMAINDER_BG_EXPANDING_HEIGHT = 4;
	
	public int START_BTN_GROUP_PADDING = 50;
	
public int MARQUEE_BG_PADDING_LEFT = 30;
	
	public int MARQUEE_BG_PADDING_RIGHT = 16;
	
	public static ViewPosition getInstance(){
		if(instance == null){
			instance = new ViewPosition();
			instance.MARQUEE_BG_PADDING_LEFT *= GameConstantsService.getInstance().getDensityScale();
			instance.MARQUEE_BG_PADDING_RIGHT *= GameConstantsService.getInstance().getDensityScale();
			instance.ACTION_SHOW_MARGIN_LEFT *= GameConstantsService.getInstance().getDensityScale();
			instance.PASS_VIEW_MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			instance.CALL_LOAD_MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			instance.START_BTN_MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			instance.SELF_PLAYER_BUTTONS_MARGIN_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			if(GameConstantsService.getInstance().getScreenHeight() < GameConstantsService.ST_HEIGHT && GameConstantsService.getInstance().getScreenWidth() <GameConstantsService.ST_WIDTH){
				instance.CALL_LOAD_BTNS_MARGIN_LEFT_IN_SMALL_SCREEN *= GameConstantsService.getInstance().getDensityScale();
			}else{
				instance.CALL_LOAD_BTNS_MARGIN_LEFT_IN_SMALL_SCREEN = 0;
			}
			instance.SELF_PLAYER_BUTTONS_PADDING *= GameConstantsService.getInstance().getDensityScale();
			instance.HURDLE_IMAGE_MARGIN_TOP *= GameConstantsService.getInstance().getDensityScale();
			instance.SLING_POINTER_MOVE_X *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_BTN_MARGINX *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_BTN_MARGINY *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_BG_PADDING_BOTTOM  *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_BG_PADDING_LEFT  *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_BG_PADDING_RIGHT *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_BG_PADDING_TOP  *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_CARD_NUM_MARGIN_TOP *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_CARD_NUM_FG_EXPANDING_BOTTOM *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_CARD_NUM_FG_EXPANDING_TOP *= GameConstantsService.getInstance().getDensityScale();
			instance.CARD_REMAINDER_BG_EXPANDING_HEIGHT *= GameConstantsService.getInstance().getDensityScale();
			instance.START_BTN_GROUP_PADDING *= GameConstantsService.getInstance().getDensityScale();
		}
		return instance;
	}
	
	private ViewPosition(){
		
	}
}
