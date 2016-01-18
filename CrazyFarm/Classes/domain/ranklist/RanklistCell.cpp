#include "RanklistCell.h"
#include "utill/Chinese.h"
#include "domain/ranklist/RanklistManager.h"
bool RanklistCell::init(){

	bg = Sprite::create("ranklistBar1.png");
	auto size = bg->getContentSize();
	bg->setPosition(size/2);
	addChild(bg);


	


	rankSprite = Sprite::create();
	rankSprite->setPosition(34,size.height/2);
	addChild(rankSprite);

	rankIndexTTF = LabelAtlas::create("0", "rankListNum.png", 26, 36, '0');
	rankIndexTTF->setPosition(34, size.height / 2);
	addChild(rankIndexTTF);

	sexSprite = Sprite::create();
	sexSprite->setPosition(135, size.height / 2);
	addChild(sexSprite);

	auto vipSp = Sprite::create("VIPtxt.png");
	vipSp->setPosition(203, size.height / 2);
	addChild(vipSp);

	VIPLvTTF = LabelAtlas::create("0", "VIPnum.png", 31, 43, '0');
	VIPLvTTF->setAnchorPoint(Point::ZERO);
	VIPLvTTF->setPosition(Point(vipSp->getContentSize().width, 0));
	vipSp->addChild(VIPLvTTF);


	auto vipLvFrame = Sprite::create("viplevelFrame.png");
	vipLvFrame->setPosition(278, size.height / 2);
	addChild(vipLvFrame);

	VIPLvSmallTTF = LabelAtlas::create("0", "vipLevelNum.png", 11, 16, '0');
	VIPLvSmallTTF->setAnchorPoint(Point::ZERO);
	VIPLvSmallTTF->setPosition(vipLvFrame->getContentSize() / 2);
	vipLvFrame->addChild(VIPLvSmallTTF);

	NameTTF = LabelTTF::create("", "arial", 20);
	NameTTF->setAnchorPoint(Point::ZERO);
	NameTTF->setPosition(vipLvFrame->getPositionX() + vipLvFrame->getContentSize().width, 0);
	addChild(NameTTF);

	auto lvSp = Sprite::create("LVTXT.png");
	vipSp->setPosition(518, size.height / 2);
	addChild(vipSp);

	LvTTF = LabelAtlas::create("0", "VIPnum.png", 31, 43, '0');
	LvTTF->setAnchorPoint(Point::ZERO);
	LvTTF->setPosition(Point(lvSp->getContentSize().width, 0));
	lvSp->addChild(LvTTF);
	//拥有金币
	auto haveCoinTTF = LabelTTF::create(ChineseWord("haveCoin").c_str(), "arial", 20);
	haveCoinTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	haveCoinTTF->setPosition(632, size.height / 2);
	addChild(haveCoinTTF);
    
	auto coinsp = Sprite::create("coin.png");
	coinsp->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	coinsp->setPosition(haveCoinTTF->getPositionX() + haveCoinTTF->getContentSize().width, size.height / 2);
	addChild(coinsp);

	CoinNumTTF = LabelAtlas::create("0", "coinnumTxt.png", 14, 18, '0');
	CoinNumTTF->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	CoinNumTTF->setPosition(857, size.height / 2);
	addChild(CoinNumTTF);
	return true;
}


void RanklistCell::setCoinValue(int index)
{
	if (index%2==1)
	{
		bg->setTexture("ranklistBar2.png");
	}
	else
	{
		bg->setTexture("ranklistBar1.png");
	}
	rankIndexTTF->setString(Value(index + 1).asString().c_str());
	auto data = RanklistManager::getInstance()->getCoinRankListData();
	auto item = data.at(index);
	VIPLvTTF->setString(Value(item.vipLevel).asString().c_str());
	LvTTF->setString(Value(item.vipLevel).asString().c_str()); ///缺少等级接口
	CoinNumTTF->setString(Value(item.coin).asString().c_str());
	NameTTF->setString(Value(item.name).asString().c_str());
	String* str;
	int k = rand() % 2;
	str = ((k==1) ? String::createWithFormat("bagMale.png") : String::createWithFormat("bagFamale.png"));///缺少性别接口
	sexSprite->setTexture(str->getCString());

	str = String::createWithFormat("ranklist_%d.png", index + 1);
	rankSprite->setTexture(str->getCString());

}

void RanklistCell::IsBeToued()
{


}