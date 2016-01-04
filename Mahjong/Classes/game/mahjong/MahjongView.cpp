#include "game/mahjong/MahjongView.h"

bool MahjongView::init(){
	if (!Layer::init())
	{
		return false;
	}
	//
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* view_bg = Sprite::create("gamemj/mjzhuobu.jpg");
	view_bg->setScale(0.5);
	view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(view_bg);

	drawPlayerSelf();
	//设置点击事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(MahjongView::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MahjongView::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MahjongView::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO 展示退出界面
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

//绘制自己
void MahjongView::drawPlayerSelf(){
	//头像的绘制
	//HeadPortrait* head = new HeadPortrait();
	//drawHeadPortrait(head);
	//牌的绘制

	ValueVector pai;
	for (int t = 0; t < 14; t++){
		pai.push_back(Value(t));
	}
	for (int i = 0; i < pai.size(); i++){
		Jong* Jong = Jong::create();
		Jong->setScale(0.5);
		Jong->setPosition(ccp(120+56*i, 100));
		Jong->showJong(0,pai.at(i).asInt());
		this->addChild(Jong);
		selfJongs.pushBack(Jong);
	}
}

//绘制左手边的玩家
void MahjongView::drawPlayerLeft(){

}


//绘制右手边的玩家
void MahjongView::drawPlayerRight(){


}


//绘制对面的玩家
void MahjongView::drawPlayerOpposite(){


}


//绘制玩家的头像
void MahjongView::drawHeadPortrait(HeadPortrait* headPortrait){
	//绘制背景
	Sprite* head_bg = Sprite::create("headportrait/touxiangheidi.png");
	head_bg->setScale(0.5);
	head_bg->setPosition(ccp(100,150));
	this->addChild(head_bg);
}



bool MahjongView::onTouchBegan(Touch *touch, Event  *event){
	//被选中的牌跟随手指移动,检测移动距离
	CCLOG("current pos === %f,%f", touch->getLocation().x, touch->getLocation().y);
	
	for (int i = 0; i < selfJongs.size(); i++)
	{
		//TODO
		CCLOG("JongBoundingBox x1 === %f", selfJongs.at(i)->getJongBoundingBox().getMinX());
		CCLOG("JongBoundingBox x2 === %f", selfJongs.at(i)->getJongBoundingBox().getMaxX());
		//CCLOG("JongBoundingBox y1 === %f", selfJongs.at(i)->getJongBoundingBox().getMinY());
		//CCLOG("JongBoundingBox y2 === %f", selfJongs.at(i)->getJongBoundingBox().getMaxY());
		if (selfJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
			CCLOG("find the jong");
		}
	}

	//判断是都属于玩家回合,是:打出,不是:回复
	return true;
}


void MahjongView::onTouchMoved(Touch *touch, Event  *event){


}



void MahjongView::onTouchEnded(Touch *touch, Event  *event){


}