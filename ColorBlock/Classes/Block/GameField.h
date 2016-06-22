#pragma once
#include "cocos2d.h"
#include "Block/BlockGroup.h"

/************************************************************************/
/* 游戏活动区域单例类                                                   */
/************************************************************************/

class GameField
{
public:
	static GameField* GetInstance();
	~GameField(void);

	bool Init(const cocos2d::Vec2& start);

	//获取方块行数
	int GetBlockRowCount() const { return BLOCK_ROW; }

	//获取方块列数
	int GetBlockColCount() const { return BLOCK_COL; }

	//获取方块总数
	int GetBlockTotalCount() const { return BLOCK_NUMBER; }

	//设置图形中方块的行列值
	void GetBlockGroupRowCol(BlockGroup& group) const;

	/************************************************************************/
	/* 设置图形中方块的行列值                                               */
	/* blocks：方块数组                                                     */
	/* row_i：第i个方块的行坐标                                             */
	/* ci：第i列的坐标与第0列的坐标差值                                     */
	/************************************************************************/
	void GetBlockGroupRowCol(std::vector<BlockObject>& blocks, int col_total,
		int row_1, int row_2, int row_3, int row_4,
		int c0, int c1, int c2, int c3
		) const;

	//获取行列号对应的坐标(精灵的anchor为(0.5,0.5))
	bool GetBlockPosition(int row, int col, cocos2d::Vec2& pos) const;

	//获取下一个图形中方块的坐标(精灵的anchor为(0.5,0.5))
	void GetBlockPosition(BlockGroup& group, const cocos2d::Rect& rect) const;

	/************************************************************************/
	/* 获取下一个图形中方块的坐标                                           */
	/* group：下一个图形                                                    */
	/* width_number：图形中方块横向最大个数                                 */
	/* height_number：图形中方块纵向最大个数                                */
	/* x_index0：横向距离左上角个数                                         */
	/* y_index0：纵向距离左上角个数                                         */
	/************************************************************************/
	void GetBlockPosition(BlockGroup& group,
		const cocos2d::Rect& rect,
		int width_number, int height_number,
		int x_index0, int x_index1, int x_index2, int x_index3,
		int y_index0, int y_index1, int y_index2, int y_index3
		) const;

private:
	GameField(void);

private:
	enum
	{
		BLOCK_ROW = 20,							//方块行数
		BLOCK_COL = 10,							//方块列数
		BLOCK_NUMBER = BLOCK_ROW * BLOCK_COL	//方块个数
	};

	//所有方块坐标
	cocos2d::Vec2	m_posBlocks[BLOCK_NUMBER];
};

