#include "game/mahjong/anim/DealJongs.h"

bool DealJongs::init(){
	if (!Layer::init()){
	  
		return false;
	}
	return true;
}

void DealJongs::showDealJong(){
	


	//step2 ��ʼ�ַ�����
	for (int i = 0; i < 3; i++){

	}
	
	//MoveTo* move2 = MoveTo::create(0.2f, ccp(960, 260));
	//Spawn* spawn2 = Spawn::create(scale, move2, NULL);
	//MoveTo* move3 = MoveTo::create(0.2f, ccp(480, 500));
	//Spawn* spawn3 = Spawn::create(scale, move3, NULL);
	//MoveTo* move4 = MoveTo::create(0.2f, ccp(0, 260));
	//Spawn* spawn4 = Spawn::create(scale, move4, NULL);
	//Sequence* seq = Sequence::create(spawn1, spawn2, spawn3, spawn4, NULL);
	

}

void DealJongs::dealHero(){
	//step1 ���Ʒ��Ƶ�����
	Sprite* pai1 = Sprite::create("gamemj/xiaogais.png");
	pai1->setPosition(ccp(0, 0));
	Sprite* pai2 = Sprite::create("gamemj/xiaogais.png");
	pai2->setPosition(ccp(50, 0));
	Sprite* pai3 = Sprite::create("gamemj/xiaogais.png");
	pai3->setPosition(ccp(0, 20));
	Sprite* pai4 = Sprite::create("gamemj/xiaogais.png");
	pai4->setPosition(ccp(50, 20));
	Sprite* total = Sprite::create();
	total->setScale(0.3f);
	total->setAnchorPoint(ccp(0, 0));
	total->setPosition(ccp(460, 260));
	total->addChild(pai1);
	total->addChild(pai2);
	total->addChild(pai3);
	total->addChild(pai4);
	this->addChild(total);
	ScaleTo* scale = ScaleTo::create(0.2f, 1.0f);
	MoveTo* move1 = MoveTo::create(0.2f, ccp(480, 50));
	Spawn* spawn1 = Spawn::create(scale, move1, NULL);
	total->runAction(spawn1);
}