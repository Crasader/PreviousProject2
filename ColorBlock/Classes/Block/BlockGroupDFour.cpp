#include "BlockGroupDFour.h"
#include "GameField.h"


BlockGroupDFour::BlockGroupDFour(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_4;
}


BlockGroupDFour::~BlockGroupDFour(void)
{
}

//初始化图形
bool BlockGroupDFour::Init()
{
	return true;
}

//设置图形类型
void BlockGroupDFour::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_4;
}

void BlockGroupDFour::initBlockGroupInDropMode(int colorIndex)
{
	m_blocks.clear();
	switch (m_direction)
	{
	case BGD_0:
	{
		BlockObject ob;
		ob.col = 1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		ob.col = -1;
		ob.row = 1;
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
	case BGD_1:
	{
		BlockObject ob;

		ob.col = -1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = -1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	case BGD_2:
	{
		BlockObject ob;
		ob.col = 1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);



		ob.col = 1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = -1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	case BGD_3:
	{
		BlockObject ob;
		ob.col = 1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		ob.col = -1;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);




		ob.col = -1;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	}

}