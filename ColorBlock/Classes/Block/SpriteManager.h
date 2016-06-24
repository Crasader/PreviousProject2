#pragma once
#include "cocos2d.h"

/************************************************************************/
/* �����������                                                       */
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
	//��ȡ�����������
	int GetBlockTypeNumber() { return BLOCK_TYPE_NUMBER; }

	//��ȡ����ߴ�
	const cocos2d::Size& GetBlockSize();

	//��ʼ������
	cocos2d::Sprite* GetBlockSprite(int block_type_index,bool isBig = false);

public:
	//��ʼ��
	bool InitSpriteFramesWithFile(const std::string& plist);
	void UnInitSpriteFramesWithFile(const std::string& plist);

	//��ȡ����
	cocos2d::Sprite* GetGameFieldSprite();				//��Ϸ�����
	cocos2d::Sprite* GetScoreSprite();					//����
	cocos2d::Sprite* GetNextSprite();					//��һ��
	cocos2d::Sprite* GetButtonRotateSprite();			//��ת
	cocos2d::Sprite* GetButtonRotatePressedSprite();
	cocos2d::Sprite* GetButtonTopSprite();				//��
	cocos2d::Sprite* GetButtonTopPressedSprite();
	cocos2d::Sprite* GetButtonDownSprite();				//��
	cocos2d::Sprite* GetButtonDownPressedSprite();
	cocos2d::Sprite* GetButtonLeftSprite();				//��
	cocos2d::Sprite* GetButtonLeftPressedSprite();
	cocos2d::Sprite* GetButtonRightSprite();			//��
	cocos2d::Sprite* GetButtonRightPressedSprite();

private:
	SpriteManager(void);

private:
	//����������
	enum { BLOCK_TYPE_NUMBER = 7};

	//��ʼ�����
	bool m_bInitialized;

	//����ߴ�
	cocos2d::Size	m_sizeBlock;
};

