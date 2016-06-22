#include "GameField.h"
#include "SpriteManager.h"

USING_NS_CC;

GameField::GameField(void)
{
}


GameField::~GameField(void)
{
}

GameField* GameField::GetInstance()
{
	static GameField s_field;
	return &s_field;
}

bool GameField::Init(const cocos2d::Vec2& start)
{
	//���鿪ʼ����
	int cx = start.x;//524;
	int cy = start.y;// 1080 - 35 - 3;

	//����ߴ�
	const cocos2d::Size& size = SpriteManager::GetInstance()->GetBlockSize();

	//���÷�������
	for (int i=0; i<BLOCK_ROW; i++)
	{
		for (int j=0; j<BLOCK_COL; j++)
		{
			m_posBlocks[i * BLOCK_COL + j].x = cx + j * size.width + size.width / 2;	//����anchor
			m_posBlocks[i * BLOCK_COL + j].y = cy - i * size.height - size.height / 2;	//����anchor
		}
	}

	return true;
}

//�����ȡͼ���з��������ֵ
void GameField::GetBlockGroupRowCol(std::vector<BlockObject>& blocks, int col_total,
									int row_0, int row_1, int row_2, int row_3,
									int c0, int c1, int c2, int c3
									) const
{
	int col = (BLOCK_COL - col_total) / 2;						//��ʼ�����������в����䣩
	int rows[] = {row_0, row_1, row_2, row_3};					//������
	int cols[] = {col + c0, col + c1, col + c2, col + c3};		//������
	for (int i=0; i<4; i++)
	{
		blocks[i].row = rows[i];
		blocks[i].col = cols[i];
	}
}

//�����ȡͼ���з��������ֵ
				
void GameField::GetBlockGroupRowCol(BlockGroup& group) const
{
	switch (group.GetBlockGroupType())
	{
	case BlockGroupType::BlockGroupType_O:
		GetBlockGroupRowCol(group.GetBlocks(), 2, -2, -2, -1, -1, 0, 1, 0, 1);
		break;
	case BlockGroupType::BlockGroupType_I:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:	//����
				GetBlockGroupRowCol(group.GetBlocks(), 1, -4, -3, -2, -1, 0, 0, 0, 0);
				break;
			case BlockGroupDirection::BGD_1:	//����
				GetBlockGroupRowCol(group.GetBlocks(), 4, -1, -1, -1, -1, 0, 1, 2, 3);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_S:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:	//S��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -2, -1, -1, 1, 2, 0, 1);
				break;
			case BlockGroupDirection::BGD_1:
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -2, -1, 0, 0, 1, 1);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_Z:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:	//Z��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -2, -1, -1, 0, 1, 1, 2);
				break;
			case BlockGroupDirection::BGD_1:
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -2, -1, 1, 0, 1, 0);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_T:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -2, -2, -1, 0, 1, 2, 1);
				break;
			case BlockGroupDirection::BGD_1:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -2, -1, 0, 0, 1, 0);
				break;
			case BlockGroupDirection::BGD_2:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -1, -1, -1, 1, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_3:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -2, -1, 1, 0, 1, 1);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_L:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -1, -1, 0, 0, 0, 1);
				break;
			case BlockGroupDirection::BGD_1:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -1, -1, -1, 2, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_2:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -3, -2, -1, 0, 1, 1, 1);
				break;
			case BlockGroupDirection::BGD_3:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -2, -2, -1, 0, 1, 2, 0);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_J:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -1, -1, 1, 1, 0, 1);
				break;
			case BlockGroupDirection::BGD_1:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -2, -2, -1, 0, 1, 2, 2);
				break;
			case BlockGroupDirection::BGD_2:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -3, -2, -1, 0, 1, 0, 0);
				break;
			case BlockGroupDirection::BGD_3:	//�⳯��
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -1, -1, -1, 0, 0, 1, 2);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

//��ȡ���кŶ�Ӧ������(�����anchorΪ(0.5,0.5))
bool GameField::GetBlockPosition(int row, int col, cocos2d::Vec2& pos) const
{
	bool res = row >= 0 && row < BLOCK_ROW && col >= 0 && col < BLOCK_COL;
	if (!res)
	{
		const Size& size = SpriteManager::GetInstance()->GetBlockSize();
		pos = Vec2(-size.width, -size.height);
	}
	else
	{
		pos = m_posBlocks[row * BLOCK_COL + col];
	}
	return res;
}

//��ȡ��һ��ͼ���з��������(�����anchorΪ(0.5,0.5))
void GameField::GetBlockPosition(BlockGroup& group, const cocos2d::Rect& rect) const
{
	//��ȡ4��С���鶥������
	switch (group.GetBlockGroupType())
	{
	case BlockGroupType::BlockGroupType_O:
		GetBlockPosition(group, rect, 2, 2, 0, 1, 0, 1, 0, 0, 1, 1);
		break;
	case BlockGroupType::BlockGroupType_I:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:		//����
				GetBlockPosition(group, rect, 1, 4, 0, 0, 0, 0, 0, 1, 2, 3);
				break;
			case BlockGroupDirection::BGD_1:		//����
				GetBlockPosition(group, rect, 4, 1, 0, 1, 2, 3, 0, 0, 0, 0);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_S:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:		//S��
				GetBlockPosition(group, rect, 3, 2, 1, 2, 0, 1, 0, 0, 1, 1);
				break;
			case BlockGroupDirection::BGD_1:
				GetBlockPosition(group, rect, 2, 3, 0, 0, 1, 1, 0, 1, 1, 2);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_Z:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:		//Z��
				GetBlockPosition(group, rect, 3, 2, 0, 1, 1, 2, 0, 0, 1, 1);
				break;
			case BlockGroupDirection::BGD_1:
				GetBlockPosition(group, rect, 2, 3, 1, 0, 1, 0, 0, 1, 1, 2);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_T:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:		//�⳯��
				GetBlockPosition(group, rect, 3, 2, 0, 1, 2, 1, 0, 0, 0, 1);
				break;
			case BlockGroupDirection::BGD_1:		//�⳯��
				GetBlockPosition(group, rect, 2, 3, 0, 0, 1, 0, 0, 1, 1, 2);
				break;
			case BlockGroupDirection::BGD_2:		//�⳯��
				GetBlockPosition(group, rect, 3, 2, 1, 0, 1, 2, 0, 1, 1, 1);
				break;
			case BlockGroupDirection::BGD_3:		//�⳯��
				GetBlockPosition(group, rect, 2, 3, 1, 0, 1, 1, 0, 1, 1, 2);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_L:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:		//�⳯��
				GetBlockPosition(group, rect, 2, 3, 0, 0, 0, 1, 0, 1, 2, 2);
				break;
			case BlockGroupDirection::BGD_1:		//�⳯��
				GetBlockPosition(group, rect, 3, 2, 2, 0, 1, 2, 0, 1, 1, 1);
				break;
			case BlockGroupDirection::BGD_2:		//�⳯��
				GetBlockPosition(group, rect, 2, 3, 0, 1, 1, 1, 0, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_3:		//�⳯��
				GetBlockPosition(group, rect, 3, 2, 0, 1, 2, 0, 0, 0, 0, 1);
				break;
			default:
				break;
			}
		}
		break;
	case BlockGroupType::BlockGroupType_J:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:		//�⳯��
				GetBlockPosition(group, rect, 2, 3, 1, 1, 0, 1, 0, 1,2, 2);
				break;
			case BlockGroupDirection::BGD_1:		//�⳯��
				GetBlockPosition(group, rect, 3, 2, 0, 1, 2, 2, 0, 0, 0, 1);
				break;
			case BlockGroupDirection::BGD_2:		//�⳯��
				GetBlockPosition(group, rect, 2, 3, 0, 1, 0, 0, 0, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_3:		//�⳯��
				GetBlockPosition(group, rect, 3, 2, 0, 0, 1, 2, 0, 1, 1, 1);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

//��ȡ��һ��ͼ���з��������
void GameField::GetBlockPosition(BlockGroup& group,
								 const cocos2d::Rect& rect,
								 int width_number, int height_number,
								 int x_index0, int x_index1, int x_index2, int x_index3,
								 int y_index0, int y_index1, int y_index2, int y_index3
								 ) const
{
	//������
	Vec2 start = rect.origin;
	Vec2 end = Vec2(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
	float width = (end.x - start.x > 0) ? (end.x - start.x) : (start.x - end.x);
	float height = (end.y - start.y > 0) ? (end.y - start.y) : (start.y - end.y);

	//�����С
	const Size& size = SpriteManager::GetInstance()->GetBlockSize();
	float widths[] = {0, size.width, size.width * 2, size.width * 3};
	float heights[] = {0, -size.height, -size.height * 2, -size.height * 3};

	//ͼ�ο��
	float group_width = size.width * width_number;
	float group_height = size.height * height_number;

	//��ͼ���Ͻ�����(����anchor)
	float cx = start.x + (width - group_width) / 2 + size.width / 2;
	float cy = start.y - (height - group_height) / 2 - size.height / 2;

	//����ÿ��С���������ֵ
	float cxs[] = {cx +  widths[x_index0], cx +  widths[x_index1], cx +  widths[x_index2], cx +  widths[x_index3]};
	float cys[] = {cy + heights[y_index0], cy + heights[y_index1], cy + heights[y_index2], cy + heights[y_index3]};

	//��ͼ����ÿ��С��������긳ֵ
	for (int i=0; i<4; i++)
	{
		group.GetBlocks()[i].sprite->setPosition(cxs[i], cys[i]);
	}
}