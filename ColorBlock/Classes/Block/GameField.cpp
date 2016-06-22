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
	//方块开始坐标
	int cx = start.x;//524;
	int cy = start.y;// 1080 - 35 - 3;

	//方块尺寸
	const cocos2d::Size& size = SpriteManager::GetInstance()->GetBlockSize();

	//设置方块坐标
	for (int i=0; i<BLOCK_ROW; i++)
	{
		for (int j=0; j<BLOCK_COL; j++)
		{
			m_posBlocks[i * BLOCK_COL + j].x = cx + j * size.width + size.width / 2;	//算上anchor
			m_posBlocks[i * BLOCK_COL + j].y = cy - i * size.height - size.height / 2;	//算上anchor
		}
	}

	return true;
}

//随机获取图形中方块的行列值
void GameField::GetBlockGroupRowCol(std::vector<BlockObject>& blocks, int col_total,
									int row_0, int row_1, int row_2, int row_3,
									int c0, int c1, int c2, int c3
									) const
{
	int col = (BLOCK_COL - col_total) / 2;						//起始列索引（从中部下落）
	int rows[] = {row_0, row_1, row_2, row_3};					//行索引
	int cols[] = {col + c0, col + c1, col + c2, col + c3};		//列索引
	for (int i=0; i<4; i++)
	{
		blocks[i].row = rows[i];
		blocks[i].col = cols[i];
	}
}

//随机获取图形中方块的行列值
				
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
			case BlockGroupDirection::BGD_0:	//竖着
				GetBlockGroupRowCol(group.GetBlocks(), 1, -4, -3, -2, -1, 0, 0, 0, 0);
				break;
			case BlockGroupDirection::BGD_1:	//横着
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
			case BlockGroupDirection::BGD_0:	//S形
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
			case BlockGroupDirection::BGD_0:	//Z形
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
			case BlockGroupDirection::BGD_0:	//尖朝下
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -2, -2, -1, 0, 1, 2, 1);
				break;
			case BlockGroupDirection::BGD_1:	//尖朝右
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -2, -1, 0, 0, 1, 0);
				break;
			case BlockGroupDirection::BGD_2:	//尖朝上
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -1, -1, -1, 1, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_3:	//尖朝左
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
			case BlockGroupDirection::BGD_0:	//尖朝右
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -1, -1, 0, 0, 0, 1);
				break;
			case BlockGroupDirection::BGD_1:	//尖朝上
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -1, -1, -1, 2, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_2:	//尖朝左
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -3, -2, -1, 0, 1, 1, 1);
				break;
			case BlockGroupDirection::BGD_3:	//尖朝下
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
			case BlockGroupDirection::BGD_0:	//尖朝左
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -2, -1, -1, 1, 1, 0, 1);
				break;
			case BlockGroupDirection::BGD_1:	//尖朝下
				GetBlockGroupRowCol(group.GetBlocks(), 3, -2, -2, -2, -1, 0, 1, 2, 2);
				break;
			case BlockGroupDirection::BGD_2:	//尖朝右
				GetBlockGroupRowCol(group.GetBlocks(), 2, -3, -3, -2, -1, 0, 1, 0, 0);
				break;
			case BlockGroupDirection::BGD_3:	//尖朝上
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

//获取行列号对应的坐标(精灵的anchor为(0.5,0.5))
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

//获取下一个图形中方块的坐标(精灵的anchor为(0.5,0.5))
void GameField::GetBlockPosition(BlockGroup& group, const cocos2d::Rect& rect) const
{
	//获取4个小方块顶点坐标
	switch (group.GetBlockGroupType())
	{
	case BlockGroupType::BlockGroupType_O:
		GetBlockPosition(group, rect, 2, 2, 0, 1, 0, 1, 0, 0, 1, 1);
		break;
	case BlockGroupType::BlockGroupType_I:
		{
			switch (group.GetBlockGroupDirection())
			{
			case BlockGroupDirection::BGD_0:		//竖着
				GetBlockPosition(group, rect, 1, 4, 0, 0, 0, 0, 0, 1, 2, 3);
				break;
			case BlockGroupDirection::BGD_1:		//横着
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
			case BlockGroupDirection::BGD_0:		//S形
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
			case BlockGroupDirection::BGD_0:		//Z形
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
			case BlockGroupDirection::BGD_0:		//尖朝下
				GetBlockPosition(group, rect, 3, 2, 0, 1, 2, 1, 0, 0, 0, 1);
				break;
			case BlockGroupDirection::BGD_1:		//尖朝右
				GetBlockPosition(group, rect, 2, 3, 0, 0, 1, 0, 0, 1, 1, 2);
				break;
			case BlockGroupDirection::BGD_2:		//尖朝上
				GetBlockPosition(group, rect, 3, 2, 1, 0, 1, 2, 0, 1, 1, 1);
				break;
			case BlockGroupDirection::BGD_3:		//尖朝左
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
			case BlockGroupDirection::BGD_0:		//尖朝右
				GetBlockPosition(group, rect, 2, 3, 0, 0, 0, 1, 0, 1, 2, 2);
				break;
			case BlockGroupDirection::BGD_1:		//尖朝上
				GetBlockPosition(group, rect, 3, 2, 2, 0, 1, 2, 0, 1, 1, 1);
				break;
			case BlockGroupDirection::BGD_2:		//尖朝左
				GetBlockPosition(group, rect, 2, 3, 0, 1, 1, 1, 0, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_3:		//尖朝下
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
			case BlockGroupDirection::BGD_0:		//尖朝左
				GetBlockPosition(group, rect, 2, 3, 1, 1, 0, 1, 0, 1,2, 2);
				break;
			case BlockGroupDirection::BGD_1:		//尖朝下
				GetBlockPosition(group, rect, 3, 2, 0, 1, 2, 2, 0, 0, 0, 1);
				break;
			case BlockGroupDirection::BGD_2:		//尖朝右
				GetBlockPosition(group, rect, 2, 3, 0, 1, 0, 0, 0, 0, 1, 2);
				break;
			case BlockGroupDirection::BGD_3:		//尖朝上
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

//获取下一个图形中方块的坐标
void GameField::GetBlockPosition(BlockGroup& group,
								 const cocos2d::Rect& rect,
								 int width_number, int height_number,
								 int x_index0, int x_index1, int x_index2, int x_index3,
								 int y_index0, int y_index1, int y_index2, int y_index3
								 ) const
{
	//区域宽高
	Vec2 start = rect.origin;
	Vec2 end = Vec2(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
	float width = (end.x - start.x > 0) ? (end.x - start.x) : (start.x - end.x);
	float height = (end.y - start.y > 0) ? (end.y - start.y) : (start.y - end.y);

	//方块大小
	const Size& size = SpriteManager::GetInstance()->GetBlockSize();
	float widths[] = {0, size.width, size.width * 2, size.width * 3};
	float heights[] = {0, -size.height, -size.height * 2, -size.height * 3};

	//图形宽高
	float group_width = size.width * width_number;
	float group_height = size.height * height_number;

	//绘图左上角坐标(包含anchor)
	float cx = start.x + (width - group_width) / 2 + size.width / 2;
	float cy = start.y - (height - group_height) / 2 - size.height / 2;

	//计算每个小方块的坐标值
	float cxs[] = {cx +  widths[x_index0], cx +  widths[x_index1], cx +  widths[x_index2], cx +  widths[x_index3]};
	float cys[] = {cy + heights[y_index0], cy + heights[y_index1], cy + heights[y_index2], cy + heights[y_index3]};

	//给图形中每个小方块的坐标赋值
	for (int i=0; i<4; i++)
	{
		group.GetBlocks()[i].sprite->setPosition(cxs[i], cys[i]);
	}
}