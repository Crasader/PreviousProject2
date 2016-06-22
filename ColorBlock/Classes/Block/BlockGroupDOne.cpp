#include "BlockGroupDOne.h"
#include "GameField.h"


BlockGroupDOne::BlockGroupDOne(void)
{
	//��������
	m_type = BlockGroupType::BlockGroupType_1;
}


BlockGroupDOne::~BlockGroupDOne(void)
{
}

//��ʼ��ͼ��
bool BlockGroupDOne::Init()
{
	return true;
}



//����ͼ������
void BlockGroupDOne::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_1;
}



void BlockGroupDOne::initBlockGroupInDropMode(int colorIndex)
{
	m_blocks.clear();
	BlockObject ob;
	ob.col = 0;
	ob.row = 0;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex);
	m_blocks.push_back(ob);

}