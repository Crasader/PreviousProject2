#include "CTurntable.h"

#include "lobby/signlayer/SignCell.h"
#include "core/TurnTableDialog.h"

#define MAX_COUNT 8 
bool CTurntable::init()
{

    if ( !Sprite::initWithFile("turntable_frame.png") )
    {
        return false;
    }
    
	
	auto result = BonusPoolManager::getInstance()->getBonuspoolResult();
	auto pool = result.reward_list;
	reward = pool.at(result.reward_position);
	curPos = result.reward_position;
	Size visibleSize = getContentSize();
	pSprite_circle = CCSprite::create("turntable_rarota.png");
    pSprite_circle->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
    addChild(pSprite_circle, 0);
    

    Sprite* pSprite_point = Sprite::create("bg_point.png");
    pSprite_point->setPosition(visibleSize.width/2,visibleSize.height/2+25);
    addChild(pSprite_point, 1);
    
	//创建奖励Item
      int size = pool.size();
	 for (int i = 0; i < size; i++) 
	{
	  auto item = pool[i];
	  int id = item.item_id;
	  int num = item.num;
		auto cell = SignCell::create(id, num);
		cell->setTag(i);
		cell->setAnchorPoint(ccp(0.5, -1.2));
		cell->setPosition(visibleSize.width/2,visibleSize.height/2);
		cell->setRotation(360 / size * i+22.5);
		pSprite_circle->addChild(cell);   
    }
    
	m_menuBegin = MenuItemImage::create("turntabelBegin_1.png", "turntabelBegin_2.png", CC_CALLBACK_1(CTurntable::menuButtonCallback,this));

	m_menuBegin->setPosition(visibleSize/2);
    
    
  
    
	Menu* pMenu = Menu::create(m_menuBegin, NULL);
    pMenu->setPosition(Point::ZERO);
   addChild(pMenu, 2);
    return true;
}


void CTurntable::menuButtonCallbackStop()
{
	static int count = 0;
	CCLOG("FUN %d", ++count);
    m_menuBegin->setEnabled(false);
    
    pSprite_circle->stopAllActions();
	pSprite_circle->setRotation(360 * (curPos-1 + CCRANDOM_MINUS1_1()*0.5) / MAX_COUNT+22.5); //改变里面的数字 更改停的位置
    
    CCActionInterval* actionTo_1 = CCRotateBy::create(1.5, 360 * 2);
    CCActionInterval* actionTo_2 = CCRotateBy::create(0.5, 144);
    CCActionInterval* actionTo_3 = CCRotateBy::create(0.65, 108);
    CCActionInterval* actionTo_4 = CCRotateBy::create(0.85, 72);
    CCActionInterval* actionTo_5 = CCRotateBy::create(1.0, 36);
	pSprite_circle->runAction(Sequence::create(actionTo_1, actionTo_2, actionTo_3, actionTo_4, actionTo_5, DelayTime::create(1.0f), CallFunc::create([&]{
		auto parent = (TurnTableDialog*)getParent();
		parent->onGetRewards(reward); }),nullptr));

 


}

void CTurntable::menuButtonCallback(Ref* pSender) {
    
	m_menuBegin->setEnabled(false);
    

    static int old_pos = 0;
    static bool need_rotation = false;
    int pos = CCRANDOM_0_1() * MAX_COUNT;
    CCLOG("pos is %d", pos);
    
    
    
    if (!need_rotation) {
        need_rotation = true;
        CCLOG("old_pos id %d", old_pos);
        CCActionInterval* actionTo_5 = CCRotateBy::create(1.0, 36);
        CCActionInterval* actionTo_4 = CCRotateBy::create(0.85, 72);
        CCActionInterval* actionTo_3 = CCRotateBy::create(0.65, 108);
        CCActionInterval* actionTo_2 = CCRotateBy::create(0.5, 144);
        CCActionInterval* actionTo_1 = CCRotateBy::create(2.5, 360 * 5);

		pSprite_circle->runAction(Sequence::create(actionTo_5, actionTo_4, actionTo_3, actionTo_2, actionTo_1, CallFunc::create(CC_CALLBACK_0(CTurntable::menuButtonCallbackStop, this)), nullptr));
        pSprite_circle->runAction(CCRepeatForever::create(actionTo_1));
        old_pos = pos;
        need_rotation = false;
    }
}



