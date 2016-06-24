#pragma once
#include "cocos2d.h"
#include "SpriteManager.h"
#include <vector>
using std::vector;

//方块参数
typedef struct _tagBlockObject
{
	int					row;	//行号
	int					col;	//列号
	int					index;	//颜色索引
	cocos2d::Sprite*	sprite;	//图片精灵
} BlockObject;

//方块组合类型
typedef enum
{
//普通模式
	BlockGroupType_S=0,		//S形方块组合(x2)
	BlockGroupType_Z,		//Z形方块组合(x2)
	BlockGroupType_T,		//T形方块组合(x4)
	BlockGroupType_L,		//L形方块组合(x4)
	BlockGroupType_J,		//J形方块组合(x4)
	BlockGroupType_O,	//O方块组合(x0)	
	BlockGroupType_I,		//I形方块组合(x2)
//拖动模式（包含I O） 
	BlockGroupType_1,		//单个方块组合(x1)
	BlockGroupType_2,		//两个方块组合(x2)
	BlockGroupType_3,		//三个方块同排组合(x2)
	BlockGroupType_4,		//三个方块不同排组合(x4)
	BlockGroupType_5,		//五个方块同排组合(x2)
	BlockGroupType_6,		//五个方块不同排组合(x4)
	BlockGroupType_7		//九个方块正方形组合(x1)
	
} BlockGroupType;

//方块组合在9宫格中的方向索引
typedef enum
{
	BGD_0 = 0,	//对于L型，突出部分朝右是0（逆时针）
	BGD_1,		//对于L型，突出部分朝上是1（逆时针）
	BGD_2,		//对于L型，突出部分朝左是2（逆时针）
	BGD_3		//对于L型，突出部分朝下是3（逆时针）
} BlockGroupDirection;

class BlockGroup
{
public:
	BlockGroup(void);
	virtual ~BlockGroup(void);

	//公共接口
public:
	/************************************************************************/
	/* 初始化图形                                                           */
	/************************************************************************/
	virtual bool Init()=0;

	//向左移动图形
	virtual bool MoveLeft(const vector<BlockObject>& blocks);

	//向右移动图形
	virtual bool MoveRight(const vector<BlockObject>& blocks);

	//向下移动图形
	virtual bool MoveDown(const vector<BlockObject>& blocks);

	//直接移动到底部
	virtual bool MoveDownDirect(const vector<BlockObject>& blocks, int nReservedRowCount = 0);

	/************************************************************************/
	/* 旋转图形(顺时针)                                                     */
	/************************************************************************/
	virtual bool Rotate(const vector<BlockObject>& blocks) = 0;

	/************************************************************************/
	/* 加速下落图形                                                         */
	/************************************************************************/
	virtual void SpeedUp() = 0;

	//重置方块
	void ResetBlockGroup(cocos2d::Node* parent, int color_index);

	//重置下一个方块
	void ResetNextBlockGroup(cocos2d::Node* parent, const cocos2d::Rect& rect);

	//获取方块集合
	std::vector<BlockObject>& GetBlocks() { return m_blocks; }

	//初始化拖动模式方块
	virtual void initBlockGroupInDropMode(int colorIndex){};




	void removeFromeParent();
protected:
	/************************************************************************/
	/* 设置图形类型                                                         */
	/************************************************************************/
	virtual void SetBlockGroupType() {}

public:
	//获取图形中的方块个数
	static int GetBlockGroupNumber() { return BLOCK_GROUP_NUMBER; }

	//获取图形种类数
	static int GetGroupTypeNumber() { return GROUP_TYPE_NUMBER; }

	//获取图形类型
	BlockGroupType GetBlockGroupType() const { return m_type; }

	//获取图形方向
	BlockGroupDirection GetBlockGroupDirection() const { return m_direction; }

	//设置图形方向
	void SetBlockGroupDirection(BlockGroupDirection dir) { m_direction = dir; }

	//重新设置方块的坐标
	void ResetBlockPosition(int block_index);

	//重新设置方块的坐标
	static void ResetBlockPosition(BlockObject& block);

private:
	//图形中的方块最大个数
	enum { BLOCK_GROUP_NUMBER = 4 };

	//图形种类数
	enum { GROUP_TYPE_NUMBER = 7 };

protected:
	
	std::vector<BlockObject> m_blocks;
	//BlockObject			m_blocks[BLOCK_GROUP_NUMBER];	//4个方块
	BlockGroupType		m_type;							//图形类型
	BlockGroupDirection	m_direction;					//图形在九宫格中的逆序索引
	int					m_nMoveDownSpeed;				//下落速度
};

