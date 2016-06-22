#include "BlockGroupS.h"
#include "GameField.h"

BlockGroupS::BlockGroupS(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_S;
}


BlockGroupS::~BlockGroupS(void)
{
}

//初始化图形
bool BlockGroupS::Init()
{
	return true;
}

//旋转图形
bool BlockGroupS::Rotate(const vector<BlockObject>& blocks)
{
	switch (m_direction)
	{
	case BlockGroupDirection::BGD_0:	//S形
		{
			//最后一行不能变形
			if (m_blocks[2].row == GameField::GetInstance()->GetBlockRowCount() - 1)
			{
				return false;
			}

			//所有潜在冲突位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

			//获取变形后的方块
			int first_row = m_blocks[0].row - 1;
			int first_col = m_blocks[2].col;
			int rows[] = {first_row, first_row + 1, first_row + 1, first_row + 2};
			int cols[] = {first_col, first_col, first_col + 1, first_col + 1};
			for (int i=0; i<4; i++)
			{
				vecRow.push_back(rows[i]);
				vecCol.push_back(cols[i]);
			}

			//有冲突的方块是否存在
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

			//变形
			for (int i=0; i<4; i++)
			{
				m_blocks[i].row = rows[i];
				m_blocks[i].col = cols[i];
				ResetBlockPosition(m_blocks[i]);
			}

			//修改方向
			m_direction = BlockGroupDirection::BGD_1;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_1:
		{
			//所有潜在位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

			//获取第一列索引
			int first_row = m_blocks[1].row;
			int first_col = m_blocks[0].col;
			if (m_blocks[2].col == GameField::GetInstance()->GetBlockColCount() - 1)
			{
				first_col -= 1;
			}

			//获取变形后的方块
			int rows[] = {first_row, first_row, first_row + 1, first_row + 1};
			int cols[] = {first_col + 1, first_col + 2, first_col, first_col + 1};
			for (int i=0; i<4; i++)
			{
				vecRow.push_back(rows[i]);
				vecCol.push_back(cols[i]);
			}

			//有冲突的方块是否存在
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

			//变形
			for (int i=0; i<4; i++)
			{
				m_blocks[i].row = rows[i];
				m_blocks[i].col = cols[i];
				ResetBlockPosition(m_blocks[i]);
			}

			//修改方向
			m_direction = BlockGroupDirection::BGD_0;

			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

//加速下落图形
void BlockGroupS::SpeedUp()
{

}

//设置图形类型
void BlockGroupS::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_S;
}