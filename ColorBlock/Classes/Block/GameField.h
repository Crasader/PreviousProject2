#pragma once
#include "cocos2d.h"
#include "Block/BlockGroup.h"

/************************************************************************/
/* ��Ϸ���������                                                   */
/************************************************************************/

class GameField
{
public:
	static GameField* GetInstance();
	~GameField(void);

	bool Init(const cocos2d::Vec2& start);

	//��ȡ��������
	int GetBlockRowCount() const { return BLOCK_ROW; }

	//��ȡ��������
	int GetBlockColCount() const { return BLOCK_COL; }

	//��ȡ��������
	int GetBlockTotalCount() const { return BLOCK_NUMBER; }

	//����ͼ���з��������ֵ
	void GetBlockGroupRowCol(BlockGroup& group) const;

	/************************************************************************/
	/* ����ͼ���з��������ֵ                                               */
	/* blocks����������                                                     */
	/* row_i����i�������������                                             */
	/* ci����i�е��������0�е������ֵ                                     */
	/************************************************************************/
	void GetBlockGroupRowCol(std::vector<BlockObject>& blocks, int col_total,
		int row_1, int row_2, int row_3, int row_4,
		int c0, int c1, int c2, int c3
		) const;

	//��ȡ���кŶ�Ӧ������(�����anchorΪ(0.5,0.5))
	bool GetBlockPosition(int row, int col, cocos2d::Vec2& pos) const;

	//��ȡ��һ��ͼ���з��������(�����anchorΪ(0.5,0.5))
	void GetBlockPosition(BlockGroup& group, const cocos2d::Rect& rect) const;

	/************************************************************************/
	/* ��ȡ��һ��ͼ���з��������                                           */
	/* group����һ��ͼ��                                                    */
	/* width_number��ͼ���з������������                                 */
	/* height_number��ͼ���з�������������                                */
	/* x_index0������������ϽǸ���                                         */
	/* y_index0������������ϽǸ���                                         */
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
		BLOCK_ROW = 20,							//��������
		BLOCK_COL = 10,							//��������
		BLOCK_NUMBER = BLOCK_ROW * BLOCK_COL	//�������
	};

	//���з�������
	cocos2d::Vec2	m_posBlocks[BLOCK_NUMBER];
};

