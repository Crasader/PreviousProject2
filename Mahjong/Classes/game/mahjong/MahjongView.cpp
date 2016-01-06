#include "game/mahjong/MahjongView.h"
#include "game/mahjong/player/PlayerLeft.h"
#include "game/mahjong/player/PlayerRight.h"
#include "game/mahjong/player/PlayerOpposite.h"

bool MahjongView::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* view_bg = Sprite::create("gamemj/mjzhuobu.jpg");
	view_bg->setScale(0.5);
	view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(view_bg);

	//�����ҵ�λ����
	drawPlayerLeft();
	drawPlayerRight();
	drawPlayerOpposite();
	drawPlayerSelf();

	//���õ���¼�����
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(MahjongView::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MahjongView::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MahjongView::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
	//���ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			// TODO չʾ�˳�����
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

//�����Լ�
void MahjongView::drawPlayerSelf(){
	//ͷ��Ļ���
	HeadPortrait* head = new HeadPortrait();
	drawHeadPortrait(head);
	//�ƵĻ���
	ValueVector pai;
	for (int t = 0; t < 14; t++){
		pai.push_back(Value(t));
	}
	for (int i = 0; i < pai.size(); i++){
		Jong* Jong = Jong::create();
		Jong->setScale(0.5);
		Jong->setPosition(ccp(140 + 56 * i, JONG_POS_Y));
		Jong->showJong(0, pai.at(i).asInt());
		this->addChild(Jong);
		selfHandJongs.pushBack(Jong);
	}
}

//�������ֱߵ����
void MahjongView::drawPlayerLeft(){
	PlayerLeft* playerLeft = PlayerLeft::create();
	this->addChild(playerLeft);
}


//�������ֱߵ����
void MahjongView::drawPlayerRight(){
	PlayerRight* playerRight = PlayerRight::create();
	this->addChild(playerRight);

}


//���ƶ�������
void MahjongView::drawPlayerOpposite(){
	PlayerOpposite* playerOpposite = PlayerOpposite::create();
	this->addChild(playerOpposite);

}


//������ҵ�ͷ��
void MahjongView::drawHeadPortrait(HeadPortrait* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("headportrait/touxiangheidi.png");
	head_bg->setScale(0.5);
	head_bg->setPosition(ccp(50, 120));
	this->addChild(head_bg);
}



bool MahjongView::onTouchBegan(Touch *touch, Event  *event){
	//��ѡ�е��Ƹ�����ָ�ƶ�
	CCLOG("current pos === %f,%f", touch->getLocation().x, touch->getLocation().y);
	virtualJong = nullptr;
	for (int i = 0; i < selfHandJongs.size(); i++)
	{
		CCLOG("JongBoundingBox x1 === %f", selfHandJongs.at(i)->getJongBoundingBox().getMinX());
		CCLOG("JongBoundingBox x2 === %f", selfHandJongs.at(i)->getJongBoundingBox().getMaxX());
		if (selfHandJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
			CCLOG("find the jong");
			selectJong = selfHandJongs.at(i);
			return true;
		}
	}
	selectJong = nullptr;
	return true;
}


void MahjongView::onTouchMoved(Touch *touch, Event  *event){
	//�ж���ָ���ƶ��Ĺ������Ƿ�ѡ����
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
		//ѡ�е��Ƹ�����ָ�ƶ�
		if (nullptr != selectJong){
			//��ָ�ƶ��ľ���ת��Ϊ�Ƶ���������ƶ�ֵ
			if (touch->getLocation().y - touch->getPreviousLocation().y > 0){

				selectJong->setPosition(ccp(selectJong->getPositionX(), selectJong->getPositionY() +
					distance(touch->getLocation(), touch->getPreviousLocation())));
			}

			if (selectJong->getPositionY() > JONG_SEL_POS_Y){
				selectJong->setPosition(ccp(selectJong->getPositionX(), JONG_SEL_POS_Y));
				//�жϵ�ǰ�Ƿ��ֵ��Լ�����
				if (true){
					if (virtualJong == nullptr){
						virtualJong = Jong::create();
						virtualJong->setScale(0.5);
						virtualJong->setPosition(selectJong->getPosition());
						virtualJong->showJong(0, selectJong->getJongType());
						//�����ӽڵ��͸�����游�ڵ�仯
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
			//TODO ���Կ��Ǽ����ӳ�
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



void MahjongView::onTouchEnded(Touch *touch, Event  *event){
	resetAllJong();
	if (nullptr != virtualJong){	
		//step1 ��С���Ʋ����Ƴ�͸����
		ScaleTo* scale = ScaleTo::create(0.2f, 0.5f);
		CallFunc* callBakc = CallFunc::create([=]{
			virtualJong->setOpacity(255);
		});
		Sequence* seq = Sequence::create(scale, callBakc, NULL);
		virtualJong->runAction(seq);
		//step2
		Jong* outJong = Jong::create();
		outJong->showJong(0, virtualJong->getJongType());
		outJong->setPosition(virtualJong->getPosition());
		outJong->setScale(0.3);
		this->addChild(outJong);
		//step3
		virtualJong->removeFromParentAndCleanup(true);
		//step4
		Point startPoint = outJong->getPosition();
		Point endPoint = ccp(100, 100);
		float sx = startPoint.x;
		float sy = startPoint.y;
		float ex = endPoint.x + 50;
		float ey = endPoint.y + 150;
		int h = outJong->getBoundingBox().size.height*0.5;
		ccBezierConfig bezier; // ��������������  
		bezier.controlPoint_1 = ccp(sx, sy); // ��ʼ��  
		bezier.controlPoint_2 = ccp(sx + (ex - sx)*0.5, sy + (ey - sy)*0.5 + 200); //���Ƶ�  
		bezier.endPosition = ccp(endPoint.x - 30, endPoint.y + h); // ����λ��     
		BezierTo *actionMove = BezierTo::create(0.5f,bezier);
		outJong->runAction(actionMove);
	}
}

void MahjongView::resetAllJong(){
	for (int i = 0; i < selfHandJongs.size(); i++)
	{
		selfHandJongs.at(i)->setPosition(ccp(selfHandJongs.at(i)->getPositionX(), JONG_POS_Y));
	}
}

void MahjongView::resetJongPos(){
	if (nullptr != selectJong){
		for (int i = 0; i < selfHandJongs.size(); i++)
		{
			if (selfHandJongs.at(i) != selectJong){
				selfHandJongs.at(i)->setPosition(ccp(selfHandJongs.at(i)->getPositionX(), JONG_POS_Y));
			}
		}
	}
}

Point MahjongView::smallJongsPos(int index){



}



float MahjongView::distance(Point pos1,Point pos2){
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

