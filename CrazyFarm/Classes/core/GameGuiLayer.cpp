#include "core/GameGuiLayer.h"
#include "pause/GamePauseLayer.h"
#include "result/GameResultScene.h"
#include "RoomManager.h"
#include "utill/define.h"

skillCell* skillCell::create(char* spName, int propNum)
{
	auto cell = new skillCell();
	if (cell&&cell->init(spName,propNum))
	{
		cell->autorelease();
		return cell;
	}
	else
	{
		cell = nullptr;
		return cell;
	}
}

bool init(char* spName, int propNum);




bool GameGuiLayer::init(){
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	return true;
}

