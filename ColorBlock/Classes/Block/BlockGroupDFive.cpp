#include "BlockGroupDFive.h"
#include "GameField.h"


BlockGroupDFive::BlockGroupDFive(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_Z;
}


BlockGroupDFive::~BlockGroupDFive(void)
{
}

//初始化图形
bool BlockGroupDFive::Init()
{
	return true;
}

//设置图形类型
void BlockGroupDFive::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_5;
}

void BlockGroupDFive::initBlockGroupInDropMode(int colorIndex)
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


		ob.col = 3;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);


		ob.col = -1;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);

		ob.col = -2;
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
		ob.row =3;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);

		ob.col = 0;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);

		ob.col = 0;
		ob.row = -2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);
	}
	break;
	}



}