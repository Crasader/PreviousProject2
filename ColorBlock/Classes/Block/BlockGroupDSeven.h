#pragma once
#include "BlockGroup.h"

class BlockGroupDSeven : public BlockGroup
{
public:
	BlockGroupDSeven(void);
	virtual ~BlockGroupDSeven(void);

	//公共接口
public:
	/************************************************************************/
	/* 初始化图形                                                           */
	/************************************************************************/
	virtual bool Init();
	/************************************************************************/
	/* 旋转图形(顺时针)                                                     */
	/************************************************************************/
	virtual bool Rotate(const vector<BlockObject>& blocks) { return false; };

	/************************************************************************/
	/* 加速下落图形                                                         */
	/************************************************************************/
	virtual void SpeedUp(){};

	virtual void initBlockGroupInDropMode(int colorIndex);
protected:
	/************************************************************************/
	/* 设置图形类型                                                         */
	/************************************************************************/
	virtual void SetBlockGroupType();
};

