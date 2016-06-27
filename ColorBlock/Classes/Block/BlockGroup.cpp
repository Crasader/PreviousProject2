#include "BlockGroup.h"
#include "GameField.h"
#include "SpriteManager.h"

USING_NS_CC;

BlockGroup::BlockGroup(void)
	: m_direction(BlockGroupDirection::BGD_0)
	, m_nMoveDownSpeed(1)
{
	m_blocks.resize(BLOCK_GROUP_NUMBER);
	//设置图形类型
	SetBlockGroupType();
}


BlockGroup::~BlockGroup(void)
{
}

//重置方块
void BlockGroup::ResetBlockGroup(cocos2d::Node* parent, int color_index)
{
	//方块
	int index = color_index;
	if (color_index < 0 || color_index >= SpriteManager::GetInstance()->GetBlockTypeNumber())
	{
		index = rand() % SpriteManager::GetInstance()->GetBlockTypeNumber();
	}

	//随机获取行列值 
	GameField::GetInstance()->GetBlockGroupRowCol(*this);

	//获取图片
	Vec2 posBlock = Vec2::ZERO;
	for (int i=0; i<BlockGroup::GetBlockGroupNumber(); i++)
	{
		m_blocks[i].index = index;
		m_blocks[i].sprite = SpriteManager::GetInstance()->GetBlockSprite(index);
		if (m_blocks[i].sprite != NULL)
		{
			GameField::GetInstance()->GetBlockPosition(m_blocks[i].row, m_blocks[i].col, posBlock);
			m_blocks[i].sprite->setPosition(posBlock);
		}
		if (parent != NULL)
		{
			parent->addChild(m_blocks[i].sprite);
		}
	}
}

//重置下一个方块
void BlockGroup::ResetNextBlockGroup(cocos2d::Node* parent, const cocos2d::Rect& rect)
{
	//方块
	int index = rand() % SpriteManager::GetInstance()->GetBlockTypeNumber();
	for (int i=0; i<BlockGroup::GetBlockGroupNumber(); i++)
	{
		m_blocks[i].index = index;
		m_blocks[i].sprite = SpriteManager::GetInstance()->GetBlockSprite(index);
		if (parent != NULL)
		{
			parent->addChild(m_blocks[i].sprite);
		}
	}

	//位置
	GameField::GetInstance()->GetBlockPosition(*this, rect);
}

//重新设置方块的坐标
void BlockGroup::ResetBlockPosition(int block_index)
{
	if (block_index < 0 || block_index >= BLOCK_GROUP_NUMBER || m_blocks[block_index].sprite == NULL)
	{
		return;
	}

	ResetBlockPosition(m_blocks[block_index]);
}

//重新设置方块的坐标
void BlockGroup::ResetBlockPosition(BlockObject& block)
{
	Vec2 posBlock = Vec2::ZERO;
	GameField::GetInstance()->GetBlockPosition(block.row, block.col, posBlock);
	block.sprite->setPosition(posBlock);
}

//向左移动图形
bool BlockGroup::MoveLeft(const vector<BlockObject>& blocks)
{
	bool result = true;
	vector<BlockObject>::const_iterator cit;
	for (int i=0; i<4; i++)
	{
		//到达左边界
		if (m_blocks[i].col <= 0)
		{
			result = false;
			break;
		}

		//当前方块是否可以移动
		for (cit=blocks.begin(); cit!=blocks.end(); ++cit)
		{
			if (cit->row == m_blocks[i].row && cit->col == m_blocks[i].col - 1)
			{
				result = false;
				break;
			}
		}

		if (!result)
		{
			break;
		}
	}

	//可以向左移动
	if (result)
	{
		for (int i=0; i<4; i++)
		{
			m_blocks[i].col--;
			ResetBlockPosition(m_blocks[i]);
		}
	}
	return result;
}

//向右移动图形
bool BlockGroup::MoveRight(const vector<BlockObject>& blocks)
{
	bool result = true;
	vector<BlockObject>::const_iterator cit;
	for (int i=0; i<4; i++)
	{
		//到达右边界
		if (m_blocks[i].col >= GameField::GetInstance()->GetBlockColCount() - 1)
		{
			result = false;
			break;
		}

		//当前方块是否可以移动
		for (cit=blocks.begin(); cit!=blocks.end(); ++cit)
		{
			if (cit->row == m_blocks[i].row && cit->col == m_blocks[i].col + 1)
			{
				result = false;
				break;
			}
		}

		if (!result)
		{
			break;
		}
	}

	//可以向右移动
	if (result)
	{
		for (int i=0; i<4; i++)
		{
			m_blocks[i].col++;
			ResetBlockPosition(m_blocks[i]);
		}
	}
	return result;
}

//向下移动图形
bool BlockGroup::MoveDown(const vector<BlockObject>& blocks)
{
	bool result = true;
	vector<BlockObject>::const_iterator cit;
	for (int i=0; i<4; i++)
	{
		//到达下边界
		if (m_blocks[i].row >= GameField::GetInstance()->GetBlockRowCount() - 1)
		{
			result = false;
			break;
		}

		//当前方块是否可以移动
		for (cit=blocks.begin(); cit!=blocks.end(); ++cit)
		{
			if (cit->col == m_blocks[i].col && cit->row == m_blocks[i].row + 1)
			{
				result = false;
				break;
			}
		}

		if (!result)
		{
			break;
		}
	}

	//可以向下移动
	if (result)
	{
		for (int i=0; i<4; i++)
		{
			m_blocks[i].row++;
			ResetBlockPosition(m_blocks[i]);
		}
	}
	return result;
}

//直接移动到底部
bool BlockGroup::MoveDownDirect(const vector<BlockObject>& blocks, int nReservedRowCount /* = 0 */)
{
	//已经在最底部
	if (m_blocks[3].row >= GameField::GetInstance()->GetBlockRowCount() - 1)
	{
		return false;
	}

	vector<BlockObject>::const_iterator cit;
	int nMoveRowCount = 0;
	bool bIntersect = false;
	for (int row=m_blocks[3].row+1; row<GameField::GetInstance()->GetBlockRowCount(); row++)
	{
		for (int i=0; i<4; i++)
		{
			//当前方块是否可以移动(row - m_blocks[3].row)行
			for (cit=blocks.begin(); cit!=blocks.end(); ++cit)
			{
				if (cit->col == m_blocks[i].col && cit->row == m_blocks[i].row + (row - m_blocks[3].row))
				{
					bIntersect = true;
					break;
				}
			}

			if (bIntersect)
			{
				break;
			}
		}

		if (bIntersect)
		{
			break;
		}
		else
		{
			nMoveRowCount++;
		}
	}

	//已经在底部
	if (nMoveRowCount <= 0)
	{
		return false;
	}

	//可以向下移动
	for (int i=0; i<4; i++)
	{
		m_blocks[i].row += (nMoveRowCount > nReservedRowCount ? (nMoveRowCount - nReservedRowCount) : 0);
		ResetBlockPosition(m_blocks[i]);
	}
	return true;
}

void BlockGroup::removeFromeParent()
{
	for (auto var:m_blocks)
	{
		if (var.sprite)
		{
			var.sprite->removeFromParentAndCleanup(1);
		}
		
	}
}