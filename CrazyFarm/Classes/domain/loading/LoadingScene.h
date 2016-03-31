#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;

USING_NS_CC_EXT;

struct LoadAniData
{
	char filepath[50];
	char animatname[50];
	float time;
	int numOfpng;
	bool isSetRestoreOriginalFrame =true;

};

struct LoadFishAniData
{
	char plistName[50];
	char jsonName[50];
};


class LoadingScene : public Layer
{
public:
	static cocos2d::Scene* createScene(bool isFirstComingNeedRegister = false);
	
private:
	static LoadingScene*create(bool isFirstComingNeedRegister);

	virtual bool init(bool isFirstComingNeedRegister);

	void load();
	void loadRes();
	void toRegister();


	///异步加载普通动画
	void loadAniWithPng(const char *filepath, const char *animatname, float time, int numOfpng, bool isSetRestoreOriginalFrame = true);
	void imageAsyncCallback(Texture2D* texture, void*aniData);
	//异步加载鱼的动画
	void loadFishAni(const char* PngName, const char* jsonName, const char* plistName);
	void imageFishAniAsyncCallback(Texture2D* texture, void*aniData);

	void update(float dt);

	void showTip();
	bool isRegisterdialog = true;
private:
	void httpCallback(Ref*psend);
	ui::LoadingBar* loadingBar;
	int temp = 0;
	

};


