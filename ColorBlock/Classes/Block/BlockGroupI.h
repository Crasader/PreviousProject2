#pragma once
#include "BlockGroup.h"

class BlockGroupI : public BlockGroup
{
public:
	BlockGroupI(void);
	virtual ~BlockGroupI(void);

	//�����ӿ�
public:
	/************************************************************************/
	/* ��ʼ��ͼ��                                                           */
	/************************************************************************/
	virtual bool Init();

	/************************************************************************/
	/* ��תͼ��                                                             */
	/************************************************************************/
	virtual bool Rotate(const vector<BlockObject>& blocks);

	/************************************************************************/
	/* ��������ͼ��                                                         */
	/************************************************************************/
	virtual void SpeedUp();

	virtual void initBlockGroupInDropMode(int colorIndex);
protected:
	/************************************************************************/
	/* ����ͼ������                                                         */
	/************************************************************************/
	virtual void SetBlockGroupType();
};
