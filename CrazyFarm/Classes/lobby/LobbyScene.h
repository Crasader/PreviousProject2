#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "config/ConfigRoom.h"
#include "network/HttpClient.h"

using namespace cocos2d::network;
USING_NS_CC;


class  roomCell:public MenuItemImage
{
public:
	static roomCell * createCell(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback);
	CC_SYNTHESIZE(int, minEnterLevel, MinEnterLevel);
	CC_SYNTHESIZE(bool, isLock, Islock);
	CC_SYNTHESIZE(int, roomid, Roomid);
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
	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
private:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	void loadResource();
	void createRoomLayer();
	void lockTheRoom();
	void moveRoomRight();
	void moveRoomLeft();


	std::vector<Room> sortRoomByMaxlevel(int maxLevel);
	void showSign(float dt);
	void showMarquee(float dt);
	///°´Å¥»Øµ÷
	void payCoinCallback(Ref*psend);
	void payDiamondCallback(Ref*psend);
	void beginGameCallback(Ref*psend);
	void bagButtonCallback(Ref*psend);
	void changeRewardCallback(Ref*psend);
	void quickBeginCallback(Ref*psend);

private:
	LabelTTF* userdiamond;
	LabelTTF* userCoin;

	Vector<roomCell*> roomCells;
};
#endif