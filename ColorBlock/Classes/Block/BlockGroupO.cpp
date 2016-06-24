#include "BlockGroupO.h"


BlockGroupO::BlockGroupO(void)
{
	//��������
	m_type = BlockGroupType::BlockGroupType_O;
}


BlockGroupO::~BlockGroupO(void)
{
}

//��ʼ��ͼ��
bool BlockGroupO::Init()
{
	return true;
}

//��תͼ��
bool BlockGroupO::Rotate(const vector<BlockObject>& blocks)
{
	//O�β���ת��
	NULL;
	return true;
}

//��������ͼ��
void BlockGroupO::SpeedUp()
{

}

//����ͼ������
void BlockGroupO::SetBlockGroupType()
{
	m_type = BlockGroupType::BlockGroupType_O;
}

void BlockGroupO::initBlockGroupInDropMode(int colorIndex)
{
	m_blocks.clear();

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


	ob.col = -1;
	ob.row = -1;
	ob.index = colorIndex;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(colorIndex,true);
	m_blocks.push_back(ob);


}