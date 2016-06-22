#include "BlockGroupJ.h"
#include "GameField.h"

BlockGroupJ::BlockGroupJ(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_J;
}


BlockGroupJ::~BlockGroupJ(void)
{
}

//初始化图形
bool BlockGroupJ::Init()
{
	return true;
}

//旋转图形(顺时针)
bool BlockGroupJ::Rotate(const vector<BlockObject>& blocks)
{
	switch (m_direction)
	{
	case BlockGroupDirection::BGD_0:	//J形 - 尖朝左 --> 尖朝上
		{
			//所有潜在冲突位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

			//获取变形后的方块
			int first_row = m_blocks[0].row;
			int first_col = m_blocks[2].col;
			if (m_blocks[0].col == GameField::GetInstance()->GetBlockColCount() - 1)
			{
				first_col -= 1;
			}
			int rows[] = {first_row, first_row + 1, first_row + 1, first_row + 1};
			int cols[] = {first_col, first_col, first_col + 1, first_col + 2};
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

			//修改方向 - 向上
			m_direction = BlockGroupDirection::BGD_3;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_3:	//尖朝上 --> 尖朝右
		{
			//所有潜在位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

			//获取第一列索引
			int first_row = m_blocks[0].row;
			int first_col = m_blocks[2].col;
			if (m_blocks[1].row == GameField::GetInstance()->GetBlockRowCount() - 1)
			{
				first_row -= 1;
			}

			//获取变形后的方块
			int rows[] = {first_row, first_row, first_row + 1, first_row + 2};
			int cols[] = {first_col, first_col + 1, first_col, first_col};
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

			//修改方向 - 向右
			m_direction = BlockGroupDirection::BGD_2;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_2:	//尖朝右 --> 尖朝下
		{
			//所有潜在冲突位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

			//获取变形后的方块
			int first_row = m_blocks[0].row + 1;
			int first_col = m_blocks[0].col - 1;
			if (m_blocks[0].col == 0)
			{
				first_col += 1;
			}
			int rows[] = {first_row, first_row, first_row, first_row + 1};
			int cols[] = {first_col, first_col + 1, first_col + 2, first_col + 2};
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

			//修改方向 - 尖朝下
			m_direction = BlockGroupDirection::BGD_1;

			return true;
		}
		break;
	case BlockGroupDirection::BGD_1:	//尖朝下 --> 尖朝左
		{
			//所有潜在位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

			//获取第一列索引
			int first_row = m_blocks[0].row - 1;
			int first_col = m_blocks[0].col;

			//获取变形后的方块
			int rows[] = {first_row, first_row + 1, first_row + 2, first_row + 2};
			int cols[] = {first_col + 1, first_col + 1, first_col, first_col + 1};
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

			//修改方向 - 尖朝左
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
void BlockGroupJ::SpeedUp()
{

}

//设置图形类型
void BlockGroupJ::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_J;
}