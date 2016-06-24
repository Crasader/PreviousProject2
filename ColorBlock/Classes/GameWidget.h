#ifndef __GAME_WIDGET_H__
#define __GAME_WIDGET_H__

#include "cocos2d.h"
#include "Block/BlockGroup.h"

class GameWidget : public cocos2d::Layer
{
public:
	GameWidget();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameWidget);

	//��ȡ��һ��ͼ��
	void GetNextBlockGroup(BlockGroup*& curGroup, cocos2d::Node* parent);

	//ͼ�νӴ�����ķ���(��10��)
	void BlockGroupLanding();

	//��ȥ�����ȡ����
	void AddScore(const vector<int>& vecFullRow);

	//��ȡ����
	int GetScore() const { return m_nScore; }

	//�������
	void ResetScore();

	//��ȡ�������ꡢ��С
	const cocos2d::Vec2& GetScorePosition() const { return m_posScore; }
	const cocos2d::Vec2& GetFirstBlockPosition() const { return m_posBlock; }
	const cocos2d::Size& GetScoreSize() const { return m_sizeScore; }
	const cocos2d::Rect& GetNextRect() const { return m_rectNext; }
	//���������ȡ����λ��
	void GetRowAndColByPos(cocos2d::Vec2 pos,int &row,int &col);

private:
	//����ͼ��
	void ResetNextGroup();

	//ˢ�·���
	void RefreshScore();

private:
	//����
	cocos2d::LabelAtlas*	m_scoreLabel;	//������ǩ
	int				m_nScore;		//����

	//��һ��ͼ��
	BlockGroup*		m_nextGroup;	//��һ��ͼ�����
	

	//��������
	cocos2d::Vec2	m_posScore;		//��������ͼƬ����
	cocos2d::Vec2	m_posBlock;		//�����������Ͻ�����
	cocos2d::Size	m_sizeScore;	//��������ͼƬ��С
	cocos2d::Rect	m_rectNext;		//��һ������ͼƬ����������
};

#endif // __GAME_WIDGET_H__
