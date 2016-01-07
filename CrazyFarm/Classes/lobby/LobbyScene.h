#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"

using namespace cocos2d::network;
USING_NS_CC;

class LobbyScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	
    CREATE_FUNC(LobbyScene);


	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
private:
	void loadResource();
	void createRoomLayer();

	///°´Å¥»Øµ÷
	void payCoinCallback(Ref*psend);
	void payDiamondCallback(Ref*psend);
	void beginGameCallback(Ref*psend);
	void bagButtonCallback(Ref*psend);
	


private:
	LabelTTF* userdiamond;
	LabelTTF* userCoin;
};
#endif