#include "core/showFishLayer.h"

bool showFishCell::init(int type)
{
	return false;
}
showFishCell* showFishCell::createCell(int type)
{
	auto cell = new showFishCell();
	if (cell&&cell->init(type))
	{
		cell->autorelease();
	}
	else
	{
		cell = nullptr;
		
	}
	return cell;

}

//bool  showFishCell::init(int type)
//{	
//	Node::init();
//	bool bRet = false;
//	while (0)
//	{
//	}
//}









bool showFishLayer::init(){
	if ( !Node::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	auto bg = Sprite::create("showfish/fishbg.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg);












	return true;

}