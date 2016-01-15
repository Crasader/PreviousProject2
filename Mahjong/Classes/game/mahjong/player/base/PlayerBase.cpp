#include "game/mahjong/player/base/PlayerBase.h"

bool PlayerBase::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}

void PlayerBase::drawHeadPortrait(PlayerInfo* playerInfo){
	//���Ʊ���
	head_bg = Sprite::create("gamemj/head_bg.png");
	this->addChild(head_bg);
	//�����ǳ�
	nickName = Label::create("Monkey", "Arial", 16);
	this->addChild(nickName);
	//����ͼƬ
	headimage = Sprite::create("gamemj/head_4.png");
	this->addChild(headimage);
	//������ʯ
	diamond = Sprite::create("gamemj/diamond.png");
	this->addChild(diamond);
	//��������
	diamondNum = LabelAtlas::create("123", "gamemj/diamond_num.png", 8, 11, '0');
	this->addChild(diamondNum);

	// �����Ӱģ��
	mStencil = Sprite::create("");
	mStencil->setPosition(Point::ZERO);
	mStencil->setVisible(false);
	addChild(mStencil);



	// �����ת����������
	Sprite* progressSprite = Sprite::create("");
	mProgressTimer = ProgressTimer::create(progressSprite);
	mProgressTimer->setPosition(Point::ZERO);
	mProgressTimer->setVisible(false);
	addChild(mProgressTimer, 100);
}


void PlayerBase::setHeadPostion(Point pos){
	head_bg->setPosition(pos);
	nickName->setPosition(ccp(pos.x,pos.y+50));
	headimage->setPosition(pos);
	diamond->setPosition(ccp(pos.x-28, pos.y - 50));
	diamondNum->setPosition(ccp(pos.x - 18, pos.y - 55));
}

void PlayerBase::timeAnim(){
	// ģ��ɼ�
	mStencil->setVisible(true);

	// ���þ��������Ϊ˳ʱ��
	mProgressTimer->setVisible(true);
	mProgressTimer->setType(ProgressTimer::Type::RADIAL);
	mProgressTimer->stopAllActions();
	//׼��һ��5����ת360�ȵĶ���(�𽥸��ǰ�͸ģ���γ���ȴЧ��;������м�ʱ��ȴ������ʵ�ֺ�ʱ�����)
	ActionInterval* action_progress_to = Sequence::create(ProgressTo::create(mCDTime, 100), ProgressTo::create(0, 0), nullptr);
	//auto action_callback = CallFunc::create(CC_CALLBACK_0(SkillButton::skillCoolDownCallBack, this));
	//mProgressTimer->runAction(Sequence::create(action_progress_to, action_callback, NULL));

}

