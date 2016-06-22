#include "SpriteManager.h"

USING_NS_CC;

SpriteManager::SpriteManager(void)
	: m_bInitialized(false)
	, m_sizeBlock(cocos2d::Size::ZERO)
{

}

SpriteManager::~SpriteManager(void)
{
	UnInit();
}

SpriteManager* SpriteManager::GetInstance()
{
	static SpriteManager s_manager;
	return &s_manager;
}

bool SpriteManager::Init()
{
	if (!m_bInitialized)
	{
		//加载plist文件到缓存
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("blocks.plist");

		m_bInitialized = true;
	}

	return m_bInitialized;
}

void SpriteManager::UnInit()
{
	if (m_bInitialized)
	{
		//从缓存移除plist文件
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("blocks.plist");

		m_bInitialized = false;
	}
}

//获取精灵尺寸
const cocos2d::Size& SpriteManager::GetBlockSize()
{
	if (m_sizeBlock.equals(Size::ZERO))
	{
		if (!Init())
		{
			return m_sizeBlock;
		}

		//获取精灵
		auto block = Sprite::createWithSpriteFrameName("block01.png");
		m_sizeBlock = block->getContentSize();
	}
	return m_sizeBlock;
}

//初始化精灵
cocos2d::Sprite* SpriteManager::GetBlockSprite(int block_type_index)
{
	if (!Init())
	{
		return NULL;
	}

	//检测索引是否越界
	if (block_type_index < 0 || block_type_index >= SpriteManager::GetBlockTypeNumber())
	{
		return NULL;
	}

	//获取精灵文件名
	std::string filename = StringUtils::format("block%02d.png", block_type_index + 1);

	//获取精灵
	auto block = Sprite::createWithSpriteFrameName(filename);
	return block;
}

//初始化
bool SpriteManager::InitSpriteFramesWithFile(const std::string& plist)
{
	//加载plist文件到缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	return true;
}

void SpriteManager::UnInitSpriteFramesWithFile(const std::string& plist)
{
	//从缓存移除plist文件
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
}

//游戏活动区域
cocos2d::Sprite* SpriteManager::GetGameFieldSprite()
{
	return Sprite::createWithSpriteFrameName("girdBoxes.png");
}

//分数
cocos2d::Sprite* SpriteManager::GetScoreSprite()
{
	return Sprite::createWithSpriteFrameName("score.png");
}

//下一个
cocos2d::Sprite* SpriteManager::GetNextSprite()
{
	return Sprite::createWithSpriteFrameName("next.png");
}

//旋转
cocos2d::Sprite* SpriteManager::GetButtonRotateSprite()
{
	return Sprite::createWithSpriteFrameName("rotate.png");
}

//旋转按下
cocos2d::Sprite* SpriteManager::GetButtonRotatePressedSprite()
{
	return Sprite::createWithSpriteFrameName("rotate_pressed.png");
}

//上
cocos2d::Sprite* SpriteManager::GetButtonTopSprite()
{
	return Sprite::createWithSpriteFrameName("direction_top.png");
}

//上按下
cocos2d::Sprite* SpriteManager::GetButtonTopPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_top_pressed.png");
}

//下
cocos2d::Sprite* SpriteManager::GetButtonDownSprite()
{
	return Sprite::createWithSpriteFrameName("direction_bottom.png");
}

//下按下
cocos2d::Sprite* SpriteManager::GetButtonDownPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_bottom_pressed.png");
}

//左
cocos2d::Sprite* SpriteManager::GetButtonLeftSprite()
{
	return Sprite::createWithSpriteFrameName("direction_left.png");
}

//左按下
cocos2d::Sprite* SpriteManager::GetButtonLeftPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_left_pressed.png");
}

//右
cocos2d::Sprite* SpriteManager::GetButtonRightSprite()
{
	return Sprite::createWithSpriteFrameName("direction_right.png");
}

//右按下
cocos2d::Sprite* SpriteManager::GetButtonRightPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_right_pressed.png");
}