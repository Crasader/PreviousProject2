#include "core/showFishLayer.h"


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

bool  showFishCell::init(int type)
{
	Node::init();
	bool bRet = false;
	do
	{

		auto visibilesize = Director::getInstance()->getVisibleSize();
		auto sp = Sprite::create("showFishAniFrame.png");
		sp->setPosition(visibilesize.width*0.27, visibilesize.height*0.6);
		addChild(sp);
		sp = Sprite::create("showFishInfoFrame");
		sp->setPosition(visibilesize.width*0.7, visibilesize.height*0.6);
		addChild(sp);

	} while (0);


	return true


		;
}




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