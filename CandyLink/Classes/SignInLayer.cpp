#include"SignInLayer.h"
#include"GameData.h"
#include"GameScene.h"
#include"LobbyScene.h"
#include"CallAndroidMethod.h"
using namespace cocos2d;








SignCell::SignCell()
{

}


SignCell* SignCell::create(int day, int proptype, int propnum, int signtype)
{
	SignCell* bRet = new SignCell();
	if (bRet&&bRet->init(day,proptype,propnum,signtype))
	{
		bRet->autorelease(); 
			return bRet; 
	}
	else 
	{ 
	  delete bRet; 
	  bRet = NULL; 
	  return NULL; 
	} 
}
////signtype  1可以签 2点击签过  3不能签
////proptype  1提示   2加时    3重排
bool SignCell::init(int day, int proptype, int propnum, int signtype)
{
	
	bool bRet = false;
	while (!bRet)
	{
		char* type;
		if (signtype == 1)
		{
			type = "normal";
		}
		else if (signtype == 2)
		{
			type = "click";
		}
		//bg
		bg = Sprite::create(String::createWithFormat(("bg_%s.png"),type)->getCString());
		bg->setPosition(Point::ZERO);
		auto bgsize = bg->getContentSize();
		addChild(bg);

		//day
		auto daystr = String::createWithFormat("day_%d_%s.png", day, type);
		auto daysprite = Sprite::create(daystr->getCString());
		daysprite->setPosition(bgsize.width / 2, bgsize.height*0.8);
		bg->addChild(daysprite);

		//proptype 
		char* propstr;
		switch (proptype)
		{
		case 1:
			propstr = "tip";
			break;
		case 2:
			propstr = "plustime";
			break;
		case 3:
			propstr = "refresh";
			break;
		default:
			break;
		}
		auto propsprite = Sprite::create(String::createWithFormat(("prop_%s_%s.png"), propstr, type)->getCString());
		propsprite->setPosition(bgsize.width / 2, bgsize.height*0.45);
		bg->addChild(propsprite);
		//num
		auto nLabel = LabelAtlas::create((String::createWithFormat(":%d", propnum))->getCString(), (String::createWithFormat("sign/Num_%s.png", type))->getCString(),17,18,'0');
		nLabel->setPosition(bgsize.width *0.3, bgsize.height*0.10);
		bg->addChild(nLabel);
		bRet = true;

	}
	return bRet;
}

void SignCell::SetBlind()
{
	bg->setTexture("bg_blind.png");
}






SignInLayer* SignInLayer::_instance = nullptr;
SignInLayer::SignInLayer(){

}

SignInLayer* SignInLayer::getInstance(){
	if (_instance == 0){
		_instance = new SignInLayer();
	}
	return _instance;
}




bool SignInLayer::init()
{
	if (!Layer::init()){
		return false;
	}	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SignInLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SignInLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SignInLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	LayerColor* layerColor = CCLayerColor::create();
	layerColor->setColor(ccc3(0, 0, 0));
	layerColor->setOpacity(180);
	layerColor->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
	this->addChild(layerColor);
	

	currentDay = CallAndroidMethod::getInstance()->getCurrentSignDayas()%7;
	//BG
	background = Sprite::create("qwindow.png");
	background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.5 + origin.y);
	addChild(background);
    bgsize = background->getContentSize();
	initsigndate();
	//title
	auto title = Sprite::create("qtitle.png");
	title->setPosition(bgsize.width/2,bgsize.height*0.85);
	background->addChild(title);

	//cell
	auto menu = Menu::create();
	for (auto cell: cells)
	{
		SignCell *signincellnor;
		SignCell *signincellclick;
		
		if (cell.day < currentDay)
		{
			/*		signincellnor = SignCell::create(cell.day, cell.proptype, cell.num, 2);
					signincellclick = SignCell::create(cell.day, cell.proptype, cell.num, 2);*/
			signincellnor = SignCell::create(cell.day, cell.proptype, cell.num, 1);
			signincellnor->SetBlind();
			signincellclick = SignCell::create(cell.day, cell.proptype, cell.num, 1);
			signincellclick->SetBlind();
		}
		else if (cell.day == currentDay)
		{
			signincellnor = SignCell::create(cell.day, cell.proptype, cell.num, 1);
			signincellclick = SignCell::create(cell.day, cell.proptype, cell.num, 2);
		}
		else
		{
			signincellnor = SignCell::create(cell.day, cell.proptype, cell.num, 1);
			signincellnor->SetBlind();
			signincellclick = SignCell::create(cell.day, cell.proptype, cell.num, 1);
			signincellclick->SetBlind();
		}
		MenuItemSprite *Itemcell = MenuItemSprite::create(signincellnor, signincellclick, CC_CALLBACK_1(SignInLayer::geteveryGift, this));
		Itemcell->setPosition(cell.pos);
		menu->addChild(Itemcell);	
	}
	menu->setPosition(Point::ZERO);
	auto queding = MenuItemImage::create("qgetgift.png", "qgetgift_click.png", CC_CALLBACK_1(SignInLayer::geteveryGift, this));
	queding->setPosition(Point(bgsize.width / 2, bgsize.height*0.17));
	menu->addChild(queding);

	

	//auto getgift = Menu::create();
	//auto getNormal = Sprite::create("qgetgift.png");
	//Rect _rect = Rect(getNormal->getPositionX(), getNormal->getPositionY(), getNormal->getContentSize().width, getNormal->getContentSize().height);
	//auto getSelected = Sprite::createWithTexture(getNormal->getTexture(), _rect, false);
	//getSelected->setScale(1.1);
	///*auto get = MenuItemSprite::create(getNormal, getSelected, CC_CALLBACK_0(SignInLayer::geteveryGift, this));*/
	///*get->setPosition(0,-150);*/
	//getgift->setAnchorPoint(Point(0.5, 0.5));
	////getgift->addChild(get);
	//getgift->setPosition(Point(0.5, 0.5));

	//this->addChild(getgift);
	background->addChild(menu);
	return true;

}

void SignInLayer::initsigndate()
{
	SignCellDate date;
	date.day = 1;
	date.num = 2;
	date.proptype = 3;
	date.pos = Point(bgsize.width*0.17, bgsize.height*0.65);
	cells.push_back(date);

	date.day = 2;
	date.num = 2;
	date.proptype = 1;
	date.pos = Point(bgsize.width*0.39, bgsize.height*0.65);
	cells.push_back(date);

	date.day = 3;
	date.num = 2;
	date.proptype = 2;
	date.pos = Point(bgsize.width*0.61, bgsize.height*0.65);
	cells.push_back(date);

	date.day = 4;
	date.num = 3;
	date.proptype = 2;
	date.pos = Point(bgsize.width*0.83, bgsize.height*0.65);
	cells.push_back(date);

	date.day = 5;
	date.num = 5;
	date.proptype = 3;
	date.pos = Point(bgsize.width*0.28, bgsize.height*0.42);
	cells.push_back(date);

	date.day = 6;
	date.num = 5;
	date.proptype = 1;
	date.pos = Point(bgsize.width*0.5, bgsize.height*0.42);
	cells.push_back(date);

	date.day = 7;
	date.num = 5;
	date.proptype = 2;
	date.pos = Point(bgsize.width*0.72, bgsize.height*0.42);
	cells.push_back(date);

}



void SignInLayer::geteveryGift(Ref* psender){
	
	//GAMEDATA::getInstance()->setLoginTimes(GAMEDATA::getInstance()->getLoginTimes()+1);
	
	switch (currentDay)
	{
	case 0:
		GAMEDATA::getInstance()->setResetNum(GAMEDATA::getInstance()->getResetNum() + 2);
		break;
	case 1:
		GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() + 2);
		break;
	case 2:
		GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum() + 2);
		break;
	case 3:
		GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum() + 3);
		break;
	case 4:
		GAMEDATA::getInstance()->setResetNum(GAMEDATA::getInstance()->getResetNum() + 5);
		break;
	case 5:
		GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() + 5);
		break;
	case 6:
		GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum() + 5);
		break;
	default:
		break;
	}
	CallAndroidMethod::getInstance()->sign();
	this->removeFromParentAndCleanup(true);	
}

void SignInLayer::update(float dt){
	
	
}


//触摸函数ccTouchBegan，返回true
bool SignInLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

