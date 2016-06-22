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
		//����plist�ļ�������
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("blocks.plist");

		m_bInitialized = true;
	}

	return m_bInitialized;
}

void SpriteManager::UnInit()
{
	if (m_bInitialized)
	{
		//�ӻ����Ƴ�plist�ļ�
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("blocks.plist");

		m_bInitialized = false;
	}
}

//��ȡ����ߴ�
const cocos2d::Size& SpriteManager::GetBlockSize()
{
	if (m_sizeBlock.equals(Size::ZERO))
	{
		if (!Init())
		{
			return m_sizeBlock;
		}

		//��ȡ����
		auto block = Sprite::createWithSpriteFrameName("block01.png");
		m_sizeBlock = block->getContentSize();
	}
	return m_sizeBlock;
}

//��ʼ������
cocos2d::Sprite* SpriteManager::GetBlockSprite(int block_type_index)
{
	if (!Init())
	{
		return NULL;
	}

	//��������Ƿ�Խ��
	if (block_type_index < 0 || block_type_index >= SpriteManager::GetBlockTypeNumber())
	{
		return NULL;
	}

	//��ȡ�����ļ���
	std::string filename = StringUtils::format("block%02d.png", block_type_index + 1);

	//��ȡ����
	auto block = Sprite::createWithSpriteFrameName(filename);
	return block;
}

//��ʼ��
bool SpriteManager::InitSpriteFramesWithFile(const std::string& plist)
{
	//����plist�ļ�������
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	return true;
}

void SpriteManager::UnInitSpriteFramesWithFile(const std::string& plist)
{
	//�ӻ����Ƴ�plist�ļ�
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
}

//��Ϸ�����
cocos2d::Sprite* SpriteManager::GetGameFieldSprite()
{
	return Sprite::createWithSpriteFrameName("girdBoxes.png");
}

//����
cocos2d::Sprite* SpriteManager::GetScoreSprite()
{
	return Sprite::createWithSpriteFrameName("score.png");
}

//��һ��
cocos2d::Sprite* SpriteManager::GetNextSprite()
{
	return Sprite::createWithSpriteFrameName("next.png");
}

//��ת
cocos2d::Sprite* SpriteManager::GetButtonRotateSprite()
{
	return Sprite::createWithSpriteFrameName("rotate.png");
}

//��ת����
cocos2d::Sprite* SpriteManager::GetButtonRotatePressedSprite()
{
	return Sprite::createWithSpriteFrameName("rotate_pressed.png");
}

//��
cocos2d::Sprite* SpriteManager::GetButtonTopSprite()
{
	return Sprite::createWithSpriteFrameName("direction_top.png");
}

//�ϰ���
cocos2d::Sprite* SpriteManager::GetButtonTopPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_top_pressed.png");
}

//��
cocos2d::Sprite* SpriteManager::GetButtonDownSprite()
{
	return Sprite::createWithSpriteFrameName("direction_bottom.png");
}

//�°���
cocos2d::Sprite* SpriteManager::GetButtonDownPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_bottom_pressed.png");
}

//��
cocos2d::Sprite* SpriteManager::GetButtonLeftSprite()
{
	return Sprite::createWithSpriteFrameName("direction_left.png");
}

//����
cocos2d::Sprite* SpriteManager::GetButtonLeftPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_left_pressed.png");
}

//��
cocos2d::Sprite* SpriteManager::GetButtonRightSprite()
{
	return Sprite::createWithSpriteFrameName("direction_right.png");
}

//�Ұ���
cocos2d::Sprite* SpriteManager::GetButtonRightPressedSprite()
{
	return Sprite::createWithSpriteFrameName("direction_right_pressed.png");
}