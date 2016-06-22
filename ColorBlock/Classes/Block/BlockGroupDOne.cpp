#include "BlockGroupDOne.h"
#include "GameField.h"


BlockGroupDOne::BlockGroupDOne(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_1;
}


BlockGroupDOne::~BlockGroupDOne(void)
{
}

//初始化图形
bool BlockGroupDOne::Init()
{
	return true;
}



//设置图形类型
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