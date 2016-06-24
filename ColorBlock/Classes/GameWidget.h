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

	//获取下一个图形
	void GetNextBlockGroup(BlockGroup*& curGroup, cocos2d::Node* parent);

	//图形接触下面的方块(加10分)
	void BlockGroupLanding();

	//消去方块获取分数
	void AddScore(const vector<int>& vecFullRow);

	//获取分数
	int GetScore() const { return m_nScore; }

	//重设分数
	void ResetScore();

	//获取区域坐标、大小
	const cocos2d::Vec2& GetScorePosition() const { return m_posScore; }
	const cocos2d::Vec2& GetFirstBlockPosition() const { return m_posBlock; }
	const cocos2d::Size& GetScoreSize() const { return m_sizeScore; }
	const cocos2d::Rect& GetNextRect() const { return m_rectNext; }
	//根据坐标获取网格位置
	void GetRowAndColByPos(cocos2d::Vec2 pos,int &row,int &col);

private:
	//重置图形
	void ResetNextGroup();

	//刷新分数
	void RefreshScore();

private:
	//分数
	cocos2d::LabelAtlas*	m_scoreLabel;	//分数标签
	int				m_nScore;		//分数

	//下一个图形
	BlockGroup*		m_nextGroup;	//下一个图形组合
	

	//坐标区域
	cocos2d::Vec2	m_posScore;		//分数区域图片坐标
	cocos2d::Vec2	m_posBlock;		//方块区域左上角坐标
	cocos2d::Size	m_sizeScore;	//分数区域图片大小
	cocos2d::Rect	m_rectNext;		//下一个区域图片的坐标区域
};

#endif // __GAME_WIDGET_H__
