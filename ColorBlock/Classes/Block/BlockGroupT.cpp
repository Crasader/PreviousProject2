#include "BlockGroupT.h"
#include "GameField.h"


BlockGroupT::BlockGroupT(void)
{
	//��������
	m_type = BlockGroupType::BlockGroupType_T;
}


BlockGroupT::~BlockGroupT(void)
{
}

//��ʼ��ͼ��
bool BlockGroupT::Init()
{
	return true;
}

//��תͼ��(˳ʱ��)
bool BlockGroupT::Rotate(const vector<BlockObject>& blocks)
{
	switch (m_direction)
	{
	case BlockGroupDirection::BGD_0:	//T�� - �⳯�� --> �⳯��
		{
			//����Ǳ�ڳ�ͻλ�õķ���
			vector<int> vecRow;
			vector<int> vecCol;

			//��ȡ���κ�ķ���
			int first_row = m_blocks[0].row - 1;
			int first_col = m_blocks[0].col;
			int rows[] = {first_row, first_row + 1, first_row + 1, first_row + 2};
			int cols[] = {first_col + 1, first_col, first_col + 1, first_col + 1};
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

			//�޸ķ��� - ����
			m_direction = BlockGroupDirection::BGD_3;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_3:	//�⳯�� --> �⳯��
		{
			//����Ǳ��λ�õķ���
			vector<int> vecRow;
			vector<int> vecCol;

			//��ȡ��һ������
			int first_row = m_blocks[0].row;
			int first_col = m_blocks[1].col;
			if (m_blocks[0].col == GameField::GetInstance()->GetBlockColCount() - 1)
			{
				first_col -= 1;
			}

			//��ȡ���κ�ķ���
			int rows[] = {first_row, first_row + 1, first_row + 1, first_row + 1};
			int cols[] = {first_col + 1, first_col, first_col + 1, first_col + 2};
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

			//�޸ķ��� - �⳯��
			m_direction = BlockGroupDirection::BGD_2;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_2:	//�⳯�� --> �⳯��
		{
			//���һ�в��ܱ���
			if (m_blocks[1].row == GameField::GetInstance()->GetBlockRowCount() - 1)
			{
				return false;
			}

			//����Ǳ�ڳ�ͻλ�õķ���
			vector<int> vecRow;
			vector<int> vecCol;

			//��ȡ���κ�ķ���
			int first_row = m_blocks[0].row;
			int first_col = m_blocks[0].col;
			int rows[] = {first_row, first_row + 1, first_row + 1, first_row + 2};
			int cols[] = {first_col, first_col, first_col + 1, first_col};
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

			//�޸ķ��� - �⳯��
			m_direction = BlockGroupDirection::BGD_1;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_1:	//�⳯�� --> �⳯��
		{
			//����Ǳ��λ�õķ���
			vector<int> vecRow;
			vector<int> vecCol;

			//��ȡ��һ������
			int first_row = m_blocks[1].row;
			int first_col = m_blocks[0].col - 1;
			if (m_blocks[0].col == 0)
			{
				first_col += 1;
			}

			//��ȡ���κ�ķ���
			int rows[] = {first_row, first_row, first_row, first_row + 1};
			int cols[] = {first_col, first_col + 1, first_col + 2, first_col + 1};
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

			//�޸ķ��� - �⳯��
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
void BlockGroupT::SpeedUp()
{

}

//����ͼ������
void BlockGroupT::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_T;
}