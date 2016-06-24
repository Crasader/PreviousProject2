#include "BlockGroupDSix.h"
#include "GameField.h"


BlockGroupDSix::BlockGroupDSix(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_6;
}


BlockGroupDSix::~BlockGroupDSix(void)
{
}

//初始化图形
bool BlockGroupDSix::Init()
{
	return true;
}

//设置图形类型
void BlockGroupDSix::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_6;
}

void BlockGroupDSix::initBlockGroupInDropMode(int colorIndex)
{
	m_blocks.clear();
	switch (m_direction)
	{
	case BGD_0:
	{
		BlockObject ob;
		ob.col = -1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		ob.col = -2;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = 2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row =1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		;
	}
	break;
	case BGD_1:
	{
		BlockObject ob;
		ob.col = -1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		ob.col = -1;
		ob.row = 2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = -1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 2;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	case BGD_2:
	{
		BlockObject ob;
		ob.col = -1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		ob.col = -1;
		ob.row = -2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = -1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 2;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	case BGD_3:
	{
		BlockObject ob;
		ob.col = -1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		ob.col =-2;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = -2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	}

}