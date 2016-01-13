#include "game/mahjong/PlayerHero.h"
#include "game/mahjong/otherplayer/PlayerLeft.h"
#include "game/mahjong/otherplayer/PlayerRight.h"
#include "game/mahjong/otherplayer/PlayerOpposite.h"

bool PlayerHero::init(){
	if (!Layer::init())
	{
		return false;
	}
	//添加自定义事件的监听
	addCoustomListener();
	//添加点击事件的监听
	addTouchListener();
	drawPlayerHero();
	return true;
}


void PlayerHero::initData(){
	isAllowPlay = false;
}

//绘制自己
void PlayerHero::drawPlayerHero(){
	//头像的绘制
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	//牌的绘制 TODO:test方法
	for (int t = 1; t < 14; t++){
		Jong* jong = Jong::create();
		jong->showJong(0, t);
		selfHandJongs.pushBack(jong);
	}
	//selfHandJongs = upsetJongs(selfHandJongs);
	for (int i = 0; i < selfHandJongs.size(); i++){
		selfHandJongs.at(i)->setPosition(ccp(140 + 59 * i, JONG_POS_Y));
		this->addChild(selfHandJongs.at(i));
	}
}


//绘制玩家的头像
void PlayerHero::drawHeadPortrait(PlayerInfo* headPortrait){
	//绘制背景
	Sprite* head_bg = Sprite::create("gamemj/head_bg.png");
	head_bg->setPosition(ccp(50, 120));
	this->addChild(head_bg);
}



void PlayerHero::resetAllJong(){
	for (int i = 0; i < selfHandJongs.size(); i++)
	{
		selfHandJongs.at(i)->setPosition(ccp(selfHandJongs.at(i)->getPositionX(), JONG_POS_Y));
	}
}

void PlayerHero::resetJongPos(){
	if (nullptr != selectJong){
		for (int i = 0; i < selfHandJongs.size(); i++)
		{
			if (selfHandJongs.at(i) != selectJong){
				selfHandJongs.at(i)->setPosition(ccp(selfHandJongs.at(i)->getPositionX(), JONG_POS_Y));
			}
		}
	}
}

Point PlayerHero::getSmallJongsPos(int index){
	int row = index / 6;
	int line = index % 6;
	Point originPos = ccp(440, 226);
	if (row == 0){
		return ccp(originPos.x + 27 * line, originPos.y);
	}
	else if (row == 1){
		return ccp(originPos.x + 27 * line, originPos.y - 38);
	}
	else {
		return ccp(originPos.x + 27 * (index - 12), originPos.y - 38 * 2);
	}


}



float PlayerHero::distance(Point pos1, Point pos2){
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}


Vector<Jong*>  PlayerHero::sortJongs(Vector<Jong*> jongs){
	int size = jongs.size();
	for (int i = 0; i < size - 1; i++){
		for (int j = size - 1; j > i; j--)
		{
			if (jongs.at(j)->getPositionX() < jongs.at(j - 1)->getPositionX()){
				jongs.swap(jongs.at(j), jongs.at(j - 1));
			}
		}
	}
	return jongs;
}


Vector<Jong*> PlayerHero::upsetJongs(Vector<Jong*> jongs){
	Vector<Jong*> newJongs;
	int size = jongs.size();
	for (int i = 0; i < size; i++){
		int current = random() % jongs.size();
		newJongs.pushBack(jongs.at(current));
		jongs.erase(current);
	}
	return newJongs;
}


//手牌整理动画
void PlayerHero::reArrangeJongs(){
	//摸什么打什么,不需要重排
	if (currentJong == selectJong){
		isAllowPlay = false;
		return;
	}
	Point needMovePos;//摸到的牌的移动位置
	if (currentJong->getJongType() == selectJong->getJongType()){
		//摸到的和打出去的牌大小一样
		log("condition : currentJong->getJongType() == selectJong->getJongType()");
		needMovePos = selectJong->getPosition();
	}
	else{
		for (int b = 0; b < selfHandJongs.size(); b++){
			log("selfHandJongs jong x %d = %f", b, selfHandJongs.at(b)->getPositionX());
		}
		//step1 获取打出去的那张牌的位置
		Point pos = selectJong->getPosition();
		//step2 获取打掉的牌的序列号
		int index = 0;
		for (int i = 0; i < selfHandJongs.size(); i++){
			if (selectJong == selfHandJongs.at(i)){
				index = i;
				log("select jong index = %d", index);
			}
		}

		//step3 获取需要移动的牌的队列以及方向
		bool isMoved = false;
		bool moveLeft = true;
		Vector<Jong*> needMoveJongs;//需要移动的队列

		if (currentJong->getJongType() >= selectJong->getJongType()){
			//右边
			moveLeft = true;
			for (int j = index + 1; j < selfHandJongs.size(); j++){
				if (selfHandJongs.at(j)->getJongType() >= currentJong->getJongType()){
					if (!isMoved){
						needMovePos = ccp(selfHandJongs.at(j)->getPositionX() - 59, JONG_POS_Y);
						isMoved = true;
					}
				}
				else{
					//needMoveJongs.pushBack(selfHandJongs.at(j));
					auto move = MoveTo::create(0.4f, ccp(selfHandJongs.at(j)->getPositionX() - 59, JONG_POS_Y));
					selfHandJongs.at(j)->runAction(move);
				}
			}

		}
		else{
			//左边
			moveLeft = false;
			for (int k = index - 1; k > 0; k--){
				if (selfHandJongs.at(k)->getJongType() <= currentJong->getJongType()){
					if (!isMoved){
						needMovePos = ccp(selfHandJongs.at(k)->getPositionX() + 59, JONG_POS_Y);
						isMoved = true;
					}
				}
				else{
					//needMoveJongs.pushBack(selfHandJongs.at(k));
					auto move = MoveTo::create(0.4f, ccp(selfHandJongs.at(k)->getPositionX() + 59, JONG_POS_Y));
					selfHandJongs.at(k)->runAction(move);
				}
			}
		}
		//step 4 按方向移动手牌
		if (moveLeft){
			for (int a = 0; a < needMoveJongs.size(); a++){
				auto move = MoveTo::create(0.4f, ccp(needMoveJongs.at(a)->getPositionX() - 59, JONG_POS_Y));
				needMoveJongs.at(a)->runAction(move);
			}
		}
		else{
			for (int a = 0; a < needMoveJongs.size(); a++){
				auto move = MoveTo::create(0.4f, ccp(needMoveJongs.at(a)->getPositionX() + 59, JONG_POS_Y));
				needMoveJongs.at(a)->runAction(move);
			}
		}



	}
	//移动摸到的牌
	ccBezierConfig bezier; // 创建贝塞尔曲线  
	bezier.controlPoint_1 = currentJong->getPosition(); // 起始点  
	bezier.controlPoint_2 = ccp(needMovePos.x + (currentJong->getPositionX() - needMovePos.x)*0.5, JONG_POS_Y + 50); //控制点  
	bezier.endPosition = ccp(needMovePos.x, needMovePos.y); // 结束位置    
	BezierTo *actionMove = BezierTo::create(0.5f, bezier);
	currentJong->runAction(actionMove);
	isAllowPlay = false;
}



void PlayerHero::addCoustomListener(){
	auto dealJongListener = EventListenerCustom::create("player_hero_turn", [=](EventCustom* event){
		//轮到自己打牌,获取牌的信息
		Jong* jong = Jong::create();
		jong->showJong(0, 5);
		selfHandJongs.pushBack(jong);
		jong->setPosition(ccp(915, JONG_POS_Y));
		currentJong = jong;
		this->addChild(jong);
		isAllowPlay = true;
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dealJongListener, 1);
}



void PlayerHero::addTouchListener(){
	//设置点击事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayerHero::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PlayerHero::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PlayerHero::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
}


bool PlayerHero::onTouchBegan(Touch *touch, Event  *event){
	//被选中的牌跟随手指移动
	//CCLOG("current pos === %f,%f", touch->getLocation().x, touch->getLocation().y);
	virtualJong = nullptr;
	for (int i = 0; i < selfHandJongs.size(); i++)
	{
		//CCLOG("JongBoundingBox x1 === %f", selfHandJongs.at(i)->getJongBoundingBox().getMinX());
		//CCLOG("JongBoundingBox x2 === %f", selfHandJongs.at(i)->getJongBoundingBox().getMaxX());
		if (selfHandJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
			CCLOG("find the jong");
			selectJong = selfHandJongs.at(i);
			return true;
		}
	}
	selectJong = nullptr;
	return false;
}


void PlayerHero::onTouchMoved(Touch *touch, Event  *event){
	//判断手指在移动的过程中是否选中牌
	if (nullptr == virtualJong){
		for (int i = 0; i < selfHandJongs.size(); i++)
		{
			if (selfHandJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
				selectJong = selfHandJongs.at(i);
				virtualJong = nullptr;
				resetJongPos();
				break;
			}
			selectJong = nullptr;
		}
		//选中的牌跟随手指移动
		if (nullptr != selectJong){
			//手指移动的距离转化为牌的纵坐标的移动值
			if (touch->getLocation().y - touch->getPreviousLocation().y > 0){

				selectJong->setPosition(ccp(selectJong->getPositionX(), selectJong->getPositionY() +
					distance(touch->getLocation(), touch->getPreviousLocation())));
			}

			if (selectJong->getPositionY() > JONG_SEL_POS_Y){
				selectJong->setPosition(ccp(selectJong->getPositionX(), JONG_SEL_POS_Y));
				//判断当前是否轮到自己出牌
				if (isAllowPlay){
					if (virtualJong == nullptr){
						virtualJong = Jong::create();
						virtualJong->setPosition(selectJong->getPosition());
						virtualJong->showJong(0, selectJong->getJongType());
						//设置子节点的透明度随父节点变化
						virtualJong->setOpacity(100);
						virtualJong->setCascadeColorEnabled(true);
						virtualJong->setCascadeOpacityEnabled(true);
						this->addChild(virtualJong);
					}
					virtualJong->setPosition(touch->getLocation());
				}
				else{
					resetAllJong();
				}
			}
		}
		else{
			//TODO 可以考虑加入延迟
			resetAllJong();
		}

	}
	else{
		if (virtualJong->getPositionY() > JONG_SEL_POS_Y){
			virtualJong->setPosition(touch->getLocation());
		}
		else{
			virtualJong->removeFromParentAndCleanup(true);
			virtualJong = nullptr;
		}
	}
}



void PlayerHero::onTouchEnded(Touch *touch, Event  *event){
	resetAllJong();
	if (nullptr != virtualJong){
		//step1 缩小虚牌并逐渐移除透明度
		ScaleTo* scale = ScaleTo::create(0.2f, 0.5f);
		CallFunc* callBakc = CallFunc::create([=]{
			virtualJong->setOpacity(255);
		});
		Sequence* seq = Sequence::create(scale, callBakc, NULL);
		virtualJong->runAction(seq);
		//step2
		Jong* outJong = Jong::create();
		outJong->showJong(2, virtualJong->getJongType());
		outJong->setPosition(virtualJong->getPosition());
		this->addChild(outJong);
		//step3
		virtualJong->removeFromParentAndCleanup(true);
		//step4
		Point startPoint = outJong->getPosition();
		Point endPoint = getSmallJongsPos(selfSmallJongs.size());
		float sx = startPoint.x;
		float sy = startPoint.y;
		float ex = endPoint.x + 50;
		float ey = endPoint.y + 150;
		int h = outJong->getBoundingBox().size.height*0.5;
		ccBezierConfig bezier; // 创建贝塞尔曲线  
		bezier.controlPoint_1 = ccp(sx, sy); // 起始点  
		bezier.controlPoint_2 = ccp(sx + (ex - sx)*0.5, sy + (ey - sy)*0.5 + 200); //控制点  
		bezier.endPosition = ccp(endPoint.x - 30, endPoint.y + h); // 结束位置     
		BezierTo *actionMove = BezierTo::create(0.5f, bezier);
		outJong->runAction(actionMove);
		selfSmallJongs.pushBack(outJong);
		//移除手牌
		selectJong->setVisible(false);
		reArrangeJongs();
		selectJong->removeFromParentAndCleanup(true);
		selfHandJongs.eraseObject(selectJong);
		DelayTime* de = DelayTime::create(0.5f);
		CallFunc* fuc = CallFunc::create([=](){
			selfHandJongs = sortJongs(selfHandJongs);
		});
		Sequence* seq2 = Sequence::create(de, fuc, NULL);
		this->runAction(seq2);
	}
}


