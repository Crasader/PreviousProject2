#include "game/mahjong/PlayerHero.h"
#include "game/mahjong/otherplayer/PlayerLeft.h"
#include "game/mahjong/otherplayer/PlayerRight.h"
#include "game/mahjong/otherplayer/PlayerOpposite.h"

bool PlayerHero::init(){
	if (!Layer::init())
	{
		return false;
	}
    //����Զ����¼��ļ���
	addCoustomListener();
	//��ӵ���¼��ļ���
	addTouchListener();
	drawPlayerHero();
	return true;
}

//�����Լ�
void PlayerHero::drawPlayerHero(){
	//ͷ��Ļ���
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	//�ƵĻ���
	for (int t = 1; t < 15; t++){
		Jong* jong = Jong::create();
		jong->showJong(0, t);
		selfHandJongs.pushBack(jong);
	}
	selfHandJongs = upsetJongs(selfHandJongs);
	for (int i = 0; i < selfHandJongs.size(); i++){
		selfHandJongs.at(i)->setPosition(ccp(140 + 59 * i, JONG_POS_Y));
		this->addChild(selfHandJongs.at(i));
	}
}


//������ҵ�ͷ��
void PlayerHero::drawHeadPortrait(PlayerInfo* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("gamemj/head_bg.png");
	head_bg->setPosition(ccp(50, 120));
	this->addChild(head_bg);
}



bool PlayerHero::onTouchBegan(Touch *touch, Event  *event){
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


void PlayerHero::onTouchMoved(Touch *touch, Event  *event){
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



void PlayerHero::onTouchEnded(Touch *touch, Event  *event){
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
		ccBezierConfig bezier; // ��������������  
		bezier.controlPoint_1 = ccp(sx, sy); // ��ʼ��  
		bezier.controlPoint_2 = ccp(sx + (ex - sx)*0.5, sy + (ey - sy)*0.5 + 200); //���Ƶ�  
		bezier.endPosition = ccp(endPoint.x - 30, endPoint.y + h); // ����λ��     
		BezierTo *actionMove = BezierTo::create(0.5f, bezier);
		outJong->runAction(actionMove);
		selfSmallJongs.pushBack(outJong);
	}
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
		return ccp(originPos.x + 27 * line, originPos.y-38);
	}
	else {
		return ccp(originPos.x + 27 * (index-12), originPos.y - 38 * 2);
	}


}



float PlayerHero::distance(Point pos1, Point pos2){
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}


Vector<Jong*>  PlayerHero::sortJongs(Vector<Jong*> jongs){
	Vector<Jong*> newJongs;
	return newJongs;
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


void PlayerHero::addCoustomListener(){
	//auto dealJongListener = EventListenerCustom::create("deal_listener", [=](EventCustom* event){

	//});
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dealJongListener, 1);
}


void PlayerHero::addTouchListener(){
	//���õ���¼�����
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayerHero::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PlayerHero::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PlayerHero::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
}
