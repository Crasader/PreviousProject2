#include "BlockGroupDThree.h"
#include "GameField.h"


BlockGroupDThree::BlockGroupDThree(void)
{
	//��������
	m_type = BlockGroupType::BlockGroupType_3;
}


BlockGroupDThree::~BlockGroupDThree(void)
{
}

//��ʼ��ͼ��
bool BlockGroupDThree::Init()
{
	return true;
}

//����ͼ������
void BlockGroupDThree::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_3;
}

void BlockGroupDThree::initBlockGroupInDropMode(int colorIndex)
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
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 2;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = -1;
		ob.row = 0;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	case BGD_1:
	{
		BlockObject ob;
		ob.col = 0;
		ob.row = 1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);


		ob.col = 0;
		ob.row = 2;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);

		ob.col = 0;
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
		m_blocks.push_back(ob);
	}
	break;
	}



}