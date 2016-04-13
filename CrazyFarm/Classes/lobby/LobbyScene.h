#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "config/ConfigRoom.h"
#include "network/HttpClient.h"
#include "domain/globalschedule/GlobalSchedule.h"
using namespace cocos2d::network;
USING_NS_CC;


enum AudioPopPage
{
	Page_sign,
	Page_vip,
	Page_guizu
};




class LobbyScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float delta);
	
    CREATE_FUNC(LobbyScene);
	void guizuCallback(Ref*psend);
	void refreshCoinLabel();
	void showVipCallBack(Ref*psend);
	void quickBeginCallback(Ref*psend);
	

	void  showPopPage();
private:
	void setValue();

	///主动弹出
	void showSign();
	void showGuizuGetRewards();
	void showGetVipCoins();


	virtual void onExit();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	virtual void onEnterTransitionDidFinish();

	void showMarquee(float dt);
	void createRoomLayer();
	///按钮回调
	void payCoinCallback(Ref*psend);
	void payDiamondCallback(Ref*psend);
	void bagButtonCallback(Ref*psend);
	void changeRewardCallback(Ref*psend);
	void WxShareCallback(Ref*psend);

	void RankListCallback(Ref*psend);
	void FirstPayCallback(Ref*psend);
	void onExitCallback(Ref*psend);
	void onAudioOnOffCallback(Ref*psend);
	void feedBackCallback(Ref*psend);

	void onExitSureCallback(Ref*psend);
	void endGameCallback(Ref*psend);
private:
	LabelTTF* userdiamond;
	LabelTTF* userCoin;
	MenuItemImage* fistPay;
	Sprite*lang;
	Sprite* spHead;
	
	Sprite*langspEmpty;
	LabelTTF* userName;
	LabelAtlas *viplevel;

	std::list<AudioPopPage> _pages;


	Sprite*testsp = nullptr;
};
#endif