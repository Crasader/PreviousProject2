#pragma once
#include "BlockGroup.h"

class BlockGroupDOne : public BlockGroup
{
public:
	BlockGroupDOne(void);
	virtual ~BlockGroupDOne(void);

	//�����ӿ�
public:
	/************************************************************************/
	/* ��ʼ��ͼ��                                                           */
	/************************************************************************/
	virtual bool Init();

	/************************************************************************/
	/* ��תͼ��(˳ʱ��)                                                     */
	/************************************************************************/
	virtual bool Rotate(const vector<BlockObject>& blocks) { return false; };;

	/************************************************************************/
	/* ��������ͼ��                                                         */
	/************************************************************************/
	virtual void SpeedUp(){};


	virtual void initBlockGroupInDropMode(int colorIndex);
protected:
	/************************************************************************/
	/* ����ͼ������                                                         */
	/************************************************************************/
	virtual void SetBlockGroupType();


};
