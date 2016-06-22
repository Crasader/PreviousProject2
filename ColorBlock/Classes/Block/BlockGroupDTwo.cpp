#include "BlockGroupDTwo.h"
#include "GameField.h"


BlockGroupDTwo::BlockGroupDTwo(void)
{
	//��������
	m_type = BlockGroupType::BlockGroupType_2;
	
}


BlockGroupDTwo::~BlockGroupDTwo(void)
{
}

//��ʼ��ͼ��
bool BlockGroupDTwo::Init()
{
	return true;
}




//����ͼ������
void BlockGroupDTwo::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_2;
}



void BlockGroupDTwo::initBlockGroupInDropMode(int colorIndex)
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
		ob.row = -1;
		ob.index = colorIndex;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
		m_blocks.push_back(ob);
	}
	break;
	}

}