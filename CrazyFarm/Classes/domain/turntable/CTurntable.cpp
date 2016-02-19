#include "CTurntable.h"

#include "TurntableCell.h"
#include "TurnTableDialog.h"
#include "domain/logevent/LogEventTurnTable.h"

#define MAX_COUNT 6 
bool CTurntable::init()
{

    if ( !Sprite::initWithFile("turntable_frame.png") )
    {
        return false;
    }
    
	
	result = BonusPoolManager::getInstance()->getBonuspoolResult();
	auto pool = result.reward_list;
	reward = pool.at(result.reward_position);
	curPos = result.reward_position;
	Size visibleSize = getContentSize();
	pSprite_circle = CCSprite::create("turntable_rarota.png");
    pSprite_circle->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
    addChild(pSprite_circle, 0);
    

    Sprite* pSprite_point = Sprite::create("bg_point.png");
    pSprite_point->setPosition(visibleSize.width/2,visibleSize.height/2);
    addChild(pSprite_point, 1);
    
	////创建奖励Item
	//angle[0] = 0;	
	//angle[1] = 48.25;
	//angle[2] = 90;
	//angle[3] = 135;
	//angle[4] = 180;
	//angle[5] = 225;
	//angle[6] = 270;
	//angle[7] = 311.75;
	int size = pool.size();
	 for (int i = 0; i < size; i++) 
	{
	  auto item = pool[i];
	  int id = item.item_id;
	  int num = item.num;
	  auto cell = TurntableCell::create(id, num); 
	  if (id == 1013)
	  {
		  cell->setScale(0.9);
		  auto txttip = Sprite::create("TXTxzdhhf.png");
		  txttip->setAnchorPoint(Point::ANCHOR_MIDDLE);
		  txttip->setPosition(cell->getContentSize().width / 2, cell->getContentSize().height-20);
		  cell->addChild(txttip);

	  }
		cell->setTag(i);
		cell->setAnchorPoint(ccp(0.5, -1.2));
		cell->setPosition(pSprite_circle->getContentSize()/2);
		cell->setRotation(i*60);
		
		pSprite_circle->addChild(cell);   
    }
    return true;
}


void CTurntable::menuButtonCallbackStop()
{
	static int count = 0;


    
    pSprite_circle->stopAllActions();
	float curangle = (360-360 * (curPos+ CCRANDOM_MINUS1_1()*0.5) / MAX_COUNT); //改变里面的数字 更改停的位置
	CCLOG("curAngle = %f", curangle);
	pSprite_circle->setRotation(curangle); 
    
    CCActionInterval* actionTo_1 = CCRotateBy::create(1.5, 360 * 2);
    CCActionInterval* actionTo_2 = CCRotateBy::create(0.5, 144);
    CCActionInterval* actionTo_3 = CCRotateBy::create(0.65, 108);
    CCActionInterval* actionTo_4 = CCRotateBy::create(0.85, 72);
    CCActionInterval* actionTo_5 = CCRotateBy::create(1.0, 36);
	pSprite_circle->runAction(Sequence::create(actionTo_1, actionTo_2, actionTo_3, actionTo_4, actionTo_5, DelayTime::create(1.0f), CallFunc::create([&]{
		auto parent = (TurnTableDialog*)getParent();
		parent->onGetRewards(reward); }),nullptr));

 


}

void CTurntable::menuButtonCallback(Ref* pSend) {
    


	LogEventTurnTable::getInstance()->sendDataToServer(result.bouns_position + 1, result.reward_position + 1);
    static bool need_rotation = false;


    
    
    
    if (!need_rotation) {
        need_rotation = true;
        CCActionInterval* actionTo_5 = CCRotateBy::create(1.0, 36);
        CCActionInterval* actionTo_4 = CCRotateBy::create(0.85, 72);
        CCActionInterval* actionTo_3 = CCRotateBy::create(0.65, 108);
        CCActionInterval* actionTo_2 = CCRotateBy::create(0.5, 144);
        CCActionInterval* actionTo_1 = CCRotateBy::create(2.5, 360 * 5);

		pSprite_circle->runAction(Sequence::create(actionTo_5, actionTo_4, actionTo_3, actionTo_2, actionTo_1, CallFunc::create(CC_CALLBACK_0(CTurntable::menuButtonCallbackStop, this)), nullptr));
        pSprite_circle->runAction(CCRepeatForever::create(actionTo_1));
    
        need_rotation = false;
    }
}



