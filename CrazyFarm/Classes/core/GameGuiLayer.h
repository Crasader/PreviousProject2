#ifndef __GAME_GUI_LAYER_H__
#define __GAME_GUI_LAYER_H__
#include "cocos2d.h"


USING_NS_CC;

class skillCell :public Sprite
{
public:
		virtual bool init(char* spName,int propNum);
		static skillCell* create(char* spName, int propNum);
};



class GameGuiLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameGuiLayer);
	void refreshSkillNum();
	
private :
	void ButtentouchEvent(Ref *pSender);
	void showRandonBubbleAni();
	void exitCallback(Ref *pSender);
	void settingCallback(Ref *pSender);
	void showFishCallback(Ref *pSender);
	void showSettingCallback(Ref*pSender);
	void createSettingBoard();
	void createGuizuGiftLayer();
	
	/////////美人鱼相关///////////////////////////////////////////////
	float fmaridNowTime = 0;
	void maridTaskTime(float dt);
	void createMermaidTaskPlane();
public:
	void beginMaridTaskTime();
private:
	////
	//播放真人声音
	void playRandVoice(float dt);
	virtual void onExit();
	MenuItemImage* setttingBoard;
	MenuItemImage* UpgradeTurret;
	 
};
#endif