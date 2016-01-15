#include "game/mahjong/player/base/PlayerBase.h"

bool PlayerBase::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}

void PlayerBase::drawHeadPortrait(PlayerInfo* playerInfo){
	//绘制背景
	head_bg = Sprite::create("gamemj/head_bg.png");
	this->addChild(head_bg);
	//绘制昵称
	nickName = Label::create("Monkey", "Arial", 16);
	this->addChild(nickName);
	//绘制图片
	headimage = Sprite::create("gamemj/head_4.png");
	this->addChild(headimage);
	//绘制钻石
	diamond = Sprite::create("gamemj/diamond.png");
	this->addChild(diamond);
	//绘制数字
	diamondNum = LabelAtlas::create("123", "gamemj/diamond_num.png", 8, 11, '0');
	this->addChild(diamondNum);

	// 添加阴影模版
	mStencil = Sprite::create("");
	mStencil->setPosition(Point::ZERO);
	mStencil->setVisible(false);
	addChild(mStencil);



	// 添加旋转进度条精灵
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
	// 模版可见
	mStencil->setVisible(true);

	// 设置精灵进度条为顺时针
	mProgressTimer->setVisible(true);
	mProgressTimer->setType(ProgressTimer::Type::RADIAL);
	mProgressTimer->stopAllActions();
	//准备一个5秒旋转360度的动画(逐渐覆盖半透模板形成冷却效果;这里进行计时冷却动画的实现和时间控制)
	ActionInterval* action_progress_to = Sequence::create(ProgressTo::create(mCDTime, 100), ProgressTo::create(0, 0), nullptr);
	//auto action_callback = CallFunc::create(CC_CALLBACK_0(SkillButton::skillCoolDownCallBack, this));
	//mProgressTimer->runAction(Sequence::create(action_progress_to, action_callback, NULL));

}

