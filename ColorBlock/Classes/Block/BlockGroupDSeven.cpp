#include "BlockGroupDSeven.h"
#include "GameField.h"


BlockGroupDSeven::BlockGroupDSeven(void)
{
	//��������
	m_type = BlockGroupType::BlockGroupType_7;
}


BlockGroupDSeven::~BlockGroupDSeven(void)
{
}

//��ʼ��ͼ��
bool BlockGroupDSeven::Init()
{
	return true;
}

//����ͼ������
void BlockGroupDSeven::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_7;
}

void BlockGroupDSeven::initBlockGroupInDropMode(int colorIndex)
{
	m_blocks.clear();
	BlockObject ob;
	ob.col = 1;
	ob.row = 1;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


	ob.col = -1;
	ob.row = -1;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


	ob.col = 1;
	ob.row = -1;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);

	ob.col = -1;
	ob.row = 1;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


	ob.col = 2;
	ob.row = -1;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


	ob.col = 2;
	ob.row = 1;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);



	ob.col =2;
	ob.row = 2;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


	ob.col = 1;
	ob.row = 2;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


	ob.col = -1;
	ob.row = 2;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


}