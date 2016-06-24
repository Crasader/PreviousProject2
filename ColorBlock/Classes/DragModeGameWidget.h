#pragma once

#include "cocos2d.h"
#include "Block/BlockGroup.h"
USING_NS_CC;
typedef struct _tagBlockGroupEntity
{
	BlockGroup*data; //方块数据
	cocos2d::Sprite*	sprite;	//集合精灵
} BlockGroupEntity;

struct BlockCutData
{
	int cutType;  //1: ROW  2: COL
	int index;
};

//方格大小
#define GridSide   43
//总行数
#define RowCount   10
//总列数
#define ColCount   10


class DragModeGameWidget : public cocos2d::Layer
{
public:
	DragModeGameWidget();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(DragModeGameWidget);


	//消去方块获取分数
	void AddScore( int cutLine);

	//获取分数
	int GetScore() const { return m_nScore; }

	//重设分数
	void ResetScore();

	//获取区域坐标、大小
	const cocos2d::Vec2& GetScorePosition() const { return m_posScore; }
	const cocos2d::Vec2& GetFirstBlockPosition() const { return m_posBlock; }
	const cocos2d::Size& GetScoreSize() const { return m_sizeScore; }
	const cocos2d::Rect& GetNextRect() const { return m_rectNext; }



	// 触摸开始事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// 触摸滑动
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// 触摸结束事件
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:


	//刷新分数
	void RefreshScore();
	//刷新行数
	void RefreshLine();

	//重置准备的方块
	void RestReadGroup();

	void CheckIsFailed();
	//网格函数
	//根据屏幕坐标获取网格行列
	void  getGridxy(Vec2 in_Pos,int &out_Row,int &out_Col);

	bool isExistBlock(int row, int col);
	bool isOutofGrid(int row, int col);

	void removeBlock(int row, int col);
	void addBlock(int row, int col, BlockObject& block);
	void refreshBlocks();

	//判断当前网格是否可以容纳参数图形
	bool isCouldPutTheBlockgroup(BlockGroup*group);
private:
	//分数
	cocos2d::LabelAtlas*	m_scoreLabel;	//分数标签
	int				m_nScore;		//分数
	cocos2d::LabelAtlas* m_labelLine;  //行数标签
	int m_nLine;  //行数

	//下一个图形
	BlockGroup*		m_nextGroup;	//下一个图形组合
	

	//坐标区域
	cocos2d::Vec2	m_posScore;		//分数区域图片坐标
	cocos2d::Vec2	m_posBlock;		//方块区域左上角坐标
	cocos2d::Size	m_sizeScore;	//分数区域图片大小
	cocos2d::Rect	m_rectNext;		//下一个区域图片的坐标区域
	
	cocos2d::Vec2 GridZeroPos;
	//正在滑动的方块集合
	BlockGroupEntity* m_nowTouchBlock = nullptr;
	cocos2d::Vec2              m_nowTouchBlockStartPos;
	//方块集合
	vector<BlockObject>	m_vecBlocks;
	vector<BlockGroupEntity*> m_vecReadBlocks;

	//网格尺寸大小
	const int _boxMaxRow = 10;
	const int _boxMaxCol = 10;
};
