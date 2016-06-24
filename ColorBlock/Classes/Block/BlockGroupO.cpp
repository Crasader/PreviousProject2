#include "BlockGroupO.h"


BlockGroupO::BlockGroupO(void)
{
	//设置类型
	m_type = BlockGroupType::BlockGroupType_O;
}


BlockGroupO::~BlockGroupO(void)
{
}

//初始化图形
bool BlockGroupO::Init()
{
	return true;
}

//旋转图形
bool BlockGroupO::Rotate(const vector<BlockObject>& blocks)
{
	//O形不用转换
	NULL;
	return true;
}

//加速下落图形
void BlockGroupO::SpeedUp()
{

}

//设置图形类型
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