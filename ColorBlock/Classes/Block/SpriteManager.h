#pragma once
#include "cocos2d.h"

/************************************************************************/
/* 精灵管理单例类                                                       */
/************************************************************************/
#define SHADESPRITEBLOCK 7
class SpriteManager
{
public:
	static SpriteManager* GetInstance();
	~SpriteManager(void);

	bool Init();
	void UnInit();

public:
	//获取方块种类个数
	int GetBlockTypeNumber() { return BLOCK_TYPE_NUMBER; }

	//获取精灵尺寸
	const cocos2d::Size& GetBlockSize();

	//初始化精灵
	cocos2d::Sprite* GetBlockSprite(int block_type_index,bool isBig = false);

public:
	//初始化
	bool InitSpriteFramesWithFile(const std::string& plist);
	void UnInitSpriteFramesWithFile(const std::string& plist);

	//获取精灵
	cocos2d::Sprite* GetGameFieldSprite();				//游戏活动区域
	cocos2d::Sprite* GetScoreSprite();					//分数
	cocos2d::Sprite* GetNextSprite();					//下一个
	cocos2d::Sprite* GetButtonRotateSprite();			//旋转
	cocos2d::Sprite* GetButtonRotatePressedSprite();
	cocos2d::Sprite* GetButtonTopSprite();				//上
	cocos2d::Sprite* GetButtonTopPressedSprite();
	cocos2d::Sprite* GetButtonDownSprite();				//下
	cocos2d::Sprite* GetButtonDownPressedSprite();
	cocos2d::Sprite* GetButtonLeftSprite();				//左
	cocos2d::Sprite* GetButtonLeftPressedSprite();
	cocos2d::Sprite* GetButtonRightSprite();			//右
	cocos2d::Sprite* GetButtonRightPressedSprite();

private:
	SpriteManager(void);

private:
	//方块种类数
	enum { BLOCK_TYPE_NUMBER = 7};

	//初始化标记
	bool m_bInitialized;

	//方块尺寸
	cocos2d::Size	m_sizeBlock;
};

