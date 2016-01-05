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
			//TODO չʾ�˳�����
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
	//HeadPortrait* head = new HeadPortrait();
	//drawHeadPortrait(head);
	//�ƵĻ���

	ValueVector pai;
	for (int t = 0; t < 14; t++){
		pai.push_back(Value(t));
	}
	for (int i = 0; i < pai.size(); i++){
		Jong* Jong = Jong::create();
		Jong->setScale(0.5);
		Jong->setPosition(ccp(120 + 56 * i, JONG_POS_Y));
		Jong->showJong(0, pai.at(i).asInt());
		this->addChild(Jong);
		selfJongs.pushBack(Jong);
	}
}

//�������ֱߵ����
void MahjongView::drawPlayerLeft(){

}


//�������ֱߵ����
void MahjongView::drawPlayerRight(){


}


//���ƶ�������
void MahjongView::drawPlayerOpposite(){


}


//������ҵ�ͷ��
void MahjongView::drawHeadPortrait(HeadPortrait* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("headportrait/touxiangheidi.png");
	head_bg->setScale(0.5);
	head_bg->setPosition(ccp(100, 150));
	this->addChild(head_bg);
}



bool MahjongView::onTouchBegan(Touch *touch, Event  *event){
	//��ѡ�е��Ƹ�����ָ�ƶ�
	CCLOG("current pos === %f,%f", touch->getLocation().x, touch->getLocation().y);
	virtualJong = nullptr;
	for (int i = 0; i < selfJongs.size(); i++)
	{
		//TODO
		CCLOG("JongBoundingBox x1 === %f", selfJongs.at(i)->getJongBoundingBox().getMinX());
		CCLOG("JongBoundingBox x2 === %f", selfJongs.at(i)->getJongBoundingBox().getMaxX());
		//CCLOG("JongBoundingBox y1 === %f", selfJongs.at(i)->getJongBoundingBox().getMinY());
		//CCLOG("JongBoundingBox y2 === %f", selfJongs.at(i)->getJongBoundingBox().getMaxY());
		if (selfJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
			CCLOG("find the jong");
			selectJong = selfJongs.at(i);
			return true;
		}
	}
	selectJong = nullptr;
	return true;
}


void MahjongView::onTouchMoved(Touch *touch, Event  *event){
	//�ж���ָ���ƶ��Ĺ������Ƿ�ѡ����
	if (nullptr == virtualJong){
		for (int i = 0; i < selfJongs.size(); i++)
		{
			if (selfJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
				selectJong = selfJongs.at(i);
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
	//�߶ȼ��,�����߶Ⱥ���ѡ
	resetAllJong();
	if (nullptr != virtualJong){
		virtualJong->removeFromParentAndCleanup(true);
	}
}

void MahjongView::resetAllJong(){
	for (int i = 0; i < selfJongs.size(); i++)
	{
		selfJongs.at(i)->setPosition(ccp(selfJongs.at(i)->getPositionX(), JONG_POS_Y));
	}
}

void MahjongView::resetJongPos(){
	if (nullptr != selectJong){
		for (int i = 0; i < selfJongs.size(); i++)
		{
			if (selfJongs.at(i) != selectJong){
				selfJongs.at(i)->setPosition(ccp(selfJongs.at(i)->getPositionX(), JONG_POS_Y));
			}
		}
	}
}

float MahjongView::distance(Point pos1,Point pos2){
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}