#include "BlockGroupI.h"
#include "GameField.h"

BlockGroupI::BlockGroupI(void)
{
	//��������
	m_type = BlockGroupType::BlockGroupType_I;
}


BlockGroupI::~BlockGroupI(void)
{
}

//��ʼ��ͼ��
bool BlockGroupI::Init()
{
	return true;
}

//��תͼ��
bool BlockGroupI::Rotate(const vector<BlockObject>& blocks)
{
	switch (m_direction)
	{
	case BlockGroupDirection::BGD_0:	//I�� - ����
		{
			//����Ǳ��λ�õķ���
			vector<int> vecRow;
			vector<int> vecCol;

			//��ȡ��һ������
			int first_row = m_blocks[2].row;
			int first_col = m_blocks[0].col;
			if (m_blocks[0].col == 0)
			{
				first_col = first_col;

				//����Ҳ෽��
				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
				int cols[] = {m_blocks[0].col + 1, m_blocks[1].col + 1, m_blocks[2].col + 1};
				vecRow.assign(rows, rows + 3);
				vecCol.assign(cols, cols + 3);
			}
			else if (m_blocks[0].col == GameField::GetInstance()->GetBlockColCount() - 1)
			{
				first_col -= 3;

				//�����෽��
				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
				int cols[] = {m_blocks[0].col - 1, m_blocks[1].col - 1, m_blocks[2].col - 1};
				vecRow.assign(rows, rows + 3);
				vecCol.assign(cols, cols + 3);
			}
			else
			{
				first_col -= (m_blocks[0].col == GameField::GetInstance()->GetBlockColCount() - 2) ? 2 : 1;

				//������෽��
				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0,
							  m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
				int cols[] = {m_blocks[0].col - 1, m_blocks[1].col - 1, m_blocks[2].col - 1,
							  m_blocks[0].col + 1, m_blocks[1].col + 1, m_blocks[2].col + 1};
				vecRow.assign(rows, rows + 6);
				vecCol.assign(cols, cols + 6);
			}

			//��ȡ���κ�ķ���
			int rows[] = {first_row, first_row, first_row, first_row};
			int cols[] = {first_col, first_col + 1, first_col + 2, first_col + 3};
			for (int i=0; i<4; i++)
			{
				vecRow.push_back(rows[i]);
				vecCol.push_back(cols[i]);
			}

			//�г�ͻ�ķ����Ƿ����
			vector<BlockObject>::const_iterator cit;
			for (vector<int>::size_type i=0; i<vecRow.size(); i++)
			{
				for (cit=blocks.begin(); cit!=blocks.end(); ++cit)
				{
					if (cit->row == vecRow.at(i) && cit->col == vecCol.at(i))
					{
						return false;
					}
				}
			}

			//����
			for (int i=0; i<4; i++)
			{
				m_blocks[i].row = rows[i];
				m_blocks[i].col = cols[i];
				ResetBlockPosition(m_blocks[i]);
			}

			//�޸ķ���
			m_direction = BlockGroupDirection::BGD_1;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_1:	//����
		{
			//���һ�в��ܱ���
			if (m_blocks[0].row == GameField::GetInstance()->GetBlockRowCount() - 1)
			{
				return false;
			}

			//����Ǳ��λ�õķ���
			vector<int> vecRow;
			vector<int> vecCol;

// 				//������෽��
// 				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0,
// 					m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
// 				int cols[] = {m_blocks[0].col - 1, m_blocks[1].col - 1, m_blocks[2].col - 1,
// 					m_blocks[0].col + 1, m_blocks[1].col + 1, m_blocks[2].col + 1};
// 				vecRow.assign(rows, rows + 6);
// 				vecRow.assign(cols, cols + 6);

			//��ȡ���κ�ķ���
			int first_row = m_blocks[0].row - 2;
			int col = m_blocks[1].col;
			int rows[] = {first_row, first_row + 1, first_row + 2, first_row + 3};
			int cols[] = {col, col, col, col};
			for (int i=0; i<4; i++)
			{
				vecRow.push_back(rows[i]);
				vecCol.push_back(cols[i]);
			}

			//�г�ͻ�ķ����Ƿ����
			vector<BlockObject>::const_iterator cit;
			for (vector<int>::size_type i=0; i<vecRow.size(); i++)
			{
				for (cit=blocks.begin(); cit!=blocks.end(); ++cit)
				{
					if (cit->row == vecRow.at(i) && cit->col == vecCol.at(i))
					{
						return false;
					}
				}
			}

			//����
			for (int i=0; i<4; i++)
			{
				m_blocks[i].row = rows[i];
				m_blocks[i].col = cols[i];
				ResetBlockPosition(m_blocks[i]);
			}

			//�޸ķ���
			m_direction = BlockGroupDirection::BGD_0;

			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

//��������ͼ��
void BlockGroupI::SpeedUp()
{

}

//����ͼ������
void BlockGroupI::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_I;
}

void BlockGroupI::initBlockGroupInDropMode(int colorIndex)
{
	m_blocks.clear();
	switch (m_direction)
	{
	case BGD_0:
	{
		BlockObject ob;
		ob.col = 1;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);


		ob.col = 2;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);

		ob.col = -2;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);

		ob.col = -1;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);
	}
		break;
	case BGD_1:
	{
		BlockObject ob;
		ob.col = 0;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);


		ob.col = 0;
		ob.row = 2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);

		ob.col = 0;
		ob.row = -2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);

		ob.col = 0;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);
	}
		break;
	}



}