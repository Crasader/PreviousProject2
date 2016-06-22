#include "BlockGroupI.h"
#include "GameField.h"

BlockGroupI::BlockGroupI(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_I;
}


BlockGroupI::~BlockGroupI(void)
{
}

//初始化图形
bool BlockGroupI::Init()
{
	return true;
}

//旋转图形
bool BlockGroupI::Rotate(const vector<BlockObject>& blocks)
{
	switch (m_direction)
	{
	case BlockGroupDirection::BGD_0:	//I形 - 竖着
		{
			//所有潜在位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

			//获取第一列索引
			int first_row = m_blocks[2].row;
			int first_col = m_blocks[0].col;
			if (m_blocks[0].col == 0)
			{
				first_col = first_col;

				//添加右侧方块
				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
				int cols[] = {m_blocks[0].col + 1, m_blocks[1].col + 1, m_blocks[2].col + 1};
				vecRow.assign(rows, rows + 3);
				vecCol.assign(cols, cols + 3);
			}
			else if (m_blocks[0].col == GameField::GetInstance()->GetBlockColCount() - 1)
			{
				first_col -= 3;

				//添加左侧方块
				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
				int cols[] = {m_blocks[0].col - 1, m_blocks[1].col - 1, m_blocks[2].col - 1};
				vecRow.assign(rows, rows + 3);
				vecCol.assign(cols, cols + 3);
			}
			else
			{
				first_col -= (m_blocks[0].col == GameField::GetInstance()->GetBlockColCount() - 2) ? 2 : 1;

				//添加两侧方块
				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0,
							  m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
				int cols[] = {m_blocks[0].col - 1, m_blocks[1].col - 1, m_blocks[2].col - 1,
							  m_blocks[0].col + 1, m_blocks[1].col + 1, m_blocks[2].col + 1};
				vecRow.assign(rows, rows + 6);
				vecCol.assign(cols, cols + 6);
			}

			//获取变形后的方块
			int rows[] = {first_row, first_row, first_row, first_row};
			int cols[] = {first_col, first_col + 1, first_col + 2, first_col + 3};
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
	case BlockGroupDirection::BGD_1:	//横着
		{
			//最后一行不能变形
			if (m_blocks[0].row == GameField::GetInstance()->GetBlockRowCount() - 1)
			{
				return false;
			}

			//所有潜在位置的方块
			vector<int> vecRow;
			vector<int> vecCol;

// 				//添加两侧方块
// 				int rows[] = {m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0,
// 					m_blocks[0].row + 0, m_blocks[1].row + 0, m_blocks[2].row + 0};
// 				int cols[] = {m_blocks[0].col - 1, m_blocks[1].col - 1, m_blocks[2].col - 1,
// 					m_blocks[0].col + 1, m_blocks[1].col + 1, m_blocks[2].col + 1};
// 				vecRow.assign(rows, rows + 6);
// 				vecRow.assign(cols, cols + 6);

			//获取变形后的方块
			int first_row = m_blocks[0].row - 2;
			int col = m_blocks[1].col;
			int rows[] = {first_row, first_row + 1, first_row + 2, first_row + 3};
			int cols[] = {col, col, col, col};
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
void BlockGroupI::SpeedUp()
{

}

//设置图形类型
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