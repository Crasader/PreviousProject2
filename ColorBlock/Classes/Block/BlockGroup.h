#pragma once
#include "cocos2d.h"
#include "SpriteManager.h"
#include <vector>
using std::vector;

//�������
typedef struct _tagBlockObject
{
	int					row;	//�к�
	int					col;	//�к�
	int					index;	//��ɫ����
	cocos2d::Sprite*	sprite;	//ͼƬ����
} BlockObject;

//�����������
typedef enum
{
//��ͨģʽ
	BlockGroupType_S=0,		//S�η������(x2)
	BlockGroupType_Z,		//Z�η������(x2)
	BlockGroupType_T,		//T�η������(x4)
	BlockGroupType_L,		//L�η������(x4)
	BlockGroupType_J,		//J�η������(x4)
	BlockGroupType_O,	//O�������(x0)	
	BlockGroupType_I,		//I�η������(x2)
//�϶�ģʽ������I O�� 
	BlockGroupType_1,		//�����������(x1)
	BlockGroupType_2,		//�����������(x2)
	BlockGroupType_3,		//��������ͬ�����(x2)
	BlockGroupType_4,		//�������鲻ͬ�����(x4)
	BlockGroupType_5,		//�������ͬ�����(x2)
	BlockGroupType_6,		//������鲻ͬ�����(x4)
	BlockGroupType_7		//�Ÿ��������������(x1)
	
} BlockGroupType;

//���������9�����еķ�������
typedef enum
{
	BGD_0 = 0,	//����L�ͣ�ͻ�����ֳ�����0����ʱ�룩
	BGD_1,		//����L�ͣ�ͻ�����ֳ�����1����ʱ�룩
	BGD_2,		//����L�ͣ�ͻ�����ֳ�����2����ʱ�룩
	BGD_3		//����L�ͣ�ͻ�����ֳ�����3����ʱ�룩
} BlockGroupDirection;

class BlockGroup
{
public:
	BlockGroup(void);
	virtual ~BlockGroup(void);

	//�����ӿ�
public:
	/************************************************************************/
	/* ��ʼ��ͼ��                                                           */
	/************************************************************************/
	virtual bool Init()=0;

	//�����ƶ�ͼ��
	virtual bool MoveLeft(const vector<BlockObject>& blocks);

	//�����ƶ�ͼ��
	virtual bool MoveRight(const vector<BlockObject>& blocks);

	//�����ƶ�ͼ��
	virtual bool MoveDown(const vector<BlockObject>& blocks);

	//ֱ���ƶ����ײ�
	virtual bool MoveDownDirect(const vector<BlockObject>& blocks, int nReservedRowCount = 0);

	/************************************************************************/
	/* ��תͼ��(˳ʱ��)                                                     */
	/************************************************************************/
	virtual bool Rotate(const vector<BlockObject>& blocks) = 0;

	/************************************************************************/
	/* ��������ͼ��                                                         */
	/************************************************************************/
	virtual void SpeedUp() = 0;

	//���÷���
	void ResetBlockGroup(cocos2d::Node* parent, int color_index);

	//������һ������
	void ResetNextBlockGroup(cocos2d::Node* parent, const cocos2d::Rect& rect);

	//��ȡ���鼯��
	std::vector<BlockObject>& GetBlocks() { return m_blocks; }

	//��ʼ���϶�ģʽ����
	virtual void initBlockGroupInDropMode(int colorIndex){};




	void removeFromeParent();
protected:
	/************************************************************************/
	/* ����ͼ������                                                         */
	/************************************************************************/
	virtual void SetBlockGroupType() {}

public:
	//��ȡͼ���еķ������
	static int GetBlockGroupNumber() { return BLOCK_GROUP_NUMBER; }

	//��ȡͼ��������
	static int GetGroupTypeNumber() { return GROUP_TYPE_NUMBER; }

	//��ȡͼ������
	BlockGroupType GetBlockGroupType() const { return m_type; }

	//��ȡͼ�η���
	BlockGroupDirection GetBlockGroupDirection() const { return m_direction; }

	//����ͼ�η���
	void SetBlockGroupDirection(BlockGroupDirection dir) { m_direction = dir; }

	//�������÷��������
	void ResetBlockPosition(int block_index);

	//�������÷��������
	static void ResetBlockPosition(BlockObject& block);

private:
	//ͼ���еķ���������
	enum { BLOCK_GROUP_NUMBER = 4 };

	//ͼ��������
	enum { GROUP_TYPE_NUMBER = 7 };

protected:
	
	std::vector<BlockObject> m_blocks;
	//BlockObject			m_blocks[BLOCK_GROUP_NUMBER];	//4������
	BlockGroupType		m_type;							//ͼ������
	BlockGroupDirection	m_direction;					//ͼ���ھŹ����е���������
	int					m_nMoveDownSpeed;				//�����ٶ�
};

