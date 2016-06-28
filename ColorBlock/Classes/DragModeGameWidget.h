#pragma once

#include "cocos2d.h"
#include "Block/BlockGroup.h"
#include "MsgDefine.h"
USING_NS_CC;
typedef struct _tagBlockGroupEntity
{
	BlockGroup*data; //��������
	cocos2d::Sprite*	sprite;	//���Ͼ���
} BlockGroupEntity;

struct BlockCutData
{
	int cutType;  //1: ROW  2: COL
	int index;
};

//�����С
#define GridSide   43
//������
#define RowCount   10
//������
#define ColCount   10


class DragModeGameWidget : public cocos2d::Layer
{
public:
	DragModeGameWidget();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(DragModeGameWidget);


	//��ȥ�����ȡ����
	void AddScore( int cutLine);

	//��ȡ����
	int GetScore() const { return m_nScore; }

	//�������
	void ResetScore();

	void Restart();

	//��ȡ�������ꡢ��С
	const cocos2d::Vec2& GetScorePosition() const { return m_posScore; }
	const cocos2d::Vec2& GetFirstBlockPosition() const { return m_posBlock; }
	const cocos2d::Size& GetScoreSize() const { return m_sizeScore; }
	const cocos2d::Rect& GetNextRect() const { return m_rectNext; }

	vector<BlockObject> getBlocks(){ return m_vecBlocks; };

	// ������ʼ�¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// ��������
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// ���������¼�
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	CC_SYNTHESIZE(GameTouchType, m_gameTouchType, gameTouchType);
private:
	void gameOver();

	//ˢ�·���
	void RefreshScore();
	//ˢ������
	void RefreshLine();

	//����׼���ķ���
	void RestReadGroup();

	void CheckIsFailed();
	//����ͬ�з���
	bool ReleaseBlocksOnFullLine();

	//����
	bool FillBlock(Vec2 pos, Sprite*sp);	//�	  //�����Ƿ�ʹ�óɹ�
	bool KnockBlock(Vec2 pos, Sprite*sp);  //����
	void ChangeNumOfSkillButoon(int skillid, int diffnum);
public:
	bool beginUsingSkill(int skillid);
	void endUsingSkill(bool isUsingsecuess);
private:
	//������
	//������Ļ�����ȡ��������
	void  getGridxy(Vec2 in_Pos,int &out_Row,int &out_Col);
	Vec2 getPosByRowAndCol(int row, int col);
	bool isExistBlock(int row, int col);
	bool isOutofGrid(int row, int col);

	void removeBlock(int row, int col);
	void addBlock(int row, int col, BlockObject& block);
	void refreshBlocks();

	//�жϵ�ǰ�����Ƿ�������ɲ���ͼ��
	bool isCouldPutTheBlockgroup(BlockGroup*group);
private:
	//����
	cocos2d::LabelAtlas*	m_scoreLabel;	//������ǩ
	int				m_nScore;		//����
	cocos2d::LabelAtlas* m_labelLine;  //������ǩ
	int m_nLine;  //����

	//��һ��ͼ��
	BlockGroup*		m_nextGroup;	//��һ��ͼ�����
	

	//��������
	cocos2d::Vec2	m_posScore;		//��������ͼƬ����
	cocos2d::Vec2	m_posBlock;		//�����������Ͻ�����
	cocos2d::Size	m_sizeScore;	//��������ͼƬ��С
	cocos2d::Rect	m_rectNext;		//��һ������ͼƬ����������
	
	cocos2d::Vec2 GridZeroPos;
	//���ڻ����ķ��鼯��
	BlockGroupEntity* m_nowTouchBlock = nullptr;
	cocos2d::Vec2              m_nowTouchBlockStartPos;
	//���鼯��
	vector<BlockObject>	m_vecBlocks;
	vector<BlockGroupEntity*> m_vecReadBlocks;

	//����ߴ��С
	const int _boxMaxRow = 10;
	const int _boxMaxCol = 10;

	//����Ч������
	Sprite* skillSp = nullptr;
	Sprite*rangeSp = nullptr;
};
