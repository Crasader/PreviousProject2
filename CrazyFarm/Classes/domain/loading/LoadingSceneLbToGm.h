#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "server/MsgObserver.h"
using namespace cocos2d;

USING_NS_CC_EXT;



class LoadingSceneLbToGm : public Layer, public MsgObserver
{
public:
	CREATE_FUNC(LoadingSceneLbToGm);
	static cocos2d::Scene* createScene();

	virtual bool init();

	void load();
	void loadRes();


	///�첽������ͨ����
	void loadAniWithPng(const char *filepath, const char *animatname, float time, int numOfpng);
	void imageAsyncCallback(Texture2D* texture, void*aniData);
	//�첽������Ķ���
	void loadFishAni(const char* PngName, const char* jsonName, const char* plistName);
	void imageFishAniAsyncCallback(Texture2D* texture, void*aniData);

	void update(float dt);

	void showTip();
	virtual void handle_event(const char* msgId, const char* msgBody);
private:

	ui::LoadingBar* loadingBar;
	int temp = 0;
	Scene*scene;
	bool _isConnetScuess = false;
};


