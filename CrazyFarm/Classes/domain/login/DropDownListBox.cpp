#include "DropDownListBox.h"
#include "utill/Chinese.h"
DropDownList::DropDownList(Sprite* label, Size size)
	: showLabel(label)
	, isShowMenu(false)
	, lastSelectedIndex(0)
{
	//创建好一个menu，但是现在还不添加到视图中
	mainMenu =Menu::create();
	mainMenu->setPosition(Point(size.width , size.height / 2));
	mainMenu->retain();
	bgFrame = Sprite::create("DropDownListFrame.png");
	bgFrame->setAnchorPoint(Point(0, 1));
	bgFrame->setPosition(62,-3);
	addChild(bgFrame,-1);
	bgFrame->setVisible(false); 

	showLabel->setPosition(Point(size.width / 2, size.height / 2));
	addChild(showLabel);
	setContentSize(size);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(DropDownList::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(DropDownList::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(DropDownList::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


}

DropDownList::~DropDownList()
{
	
}

DropDownList*DropDownList::create(Sprite* label, CCSize size)
{
	DropDownList* list = new DropDownList(label, size);
	list->autorelease();
	return list;
}


void DropDownList::onEnter()
{
	setTouchEnabled(true);
	CCLayer::onEnter();
}


bool DropDownList::onTouchBegan(CCTouch *touch, CCEvent *event)
{
	auto rect = _loginscene->_editName->getBoundingBox();
	if (rect.containsPoint(touch->getLocation()))
	{
		if (!isShowMenu)
		{
			bgFrame->setVisible(true);
			isShowMenu = true;
			addChild(mainMenu);
			_loginscene->_editName->setText(ChineseWord("UserOtherNickname").c_str());
		
			_loginscene->_editName->setFontColor(Color3B::GRAY);
			return true;

		}
		else
		{
			onClose();
			return false;
		}
		
	}
	else
	{
		if (isShowMenu)
		{
			_loginscene->setChangeNickName(selectLabels.at(0));
			onClose(); 
			return true;
		}
			
		
	}
	return false;

	
}

//创建以menu item 并添加一个label覆盖到上面
void DropDownList::addLabel(std::string label)
{
	Size size = getContentSize();

	auto ttf = LabelTTF::create(label, "arial",22);
	auto frame = Sprite::create("nicknameSelected.png");
	frame->setPosition(ttf->getContentSize() / 2);
	ttf->addChild(frame,-1);

	selectLabels.push_back(label);

	MenuItem* item = MenuItemSprite::create(
		LabelTTF::create(label, "arial", 22),ttf,
		CC_CALLBACK_1(DropDownList::onSelected,this)
		);
	item->setAnchorPoint(Point::ANCHOR_MIDDLE);
	item->setPosition(65, -(int)selectLabels.size() * 37);
	mainMenu->addChild(item);
	item->setTag((int)selectLabels.size() - 1);
}

//选中下拉列表后
void DropDownList::onSelected(CCObject* sender)
{
	MenuItem* item = dynamic_cast<MenuItem*>(sender);
	if (item)
	{
		lastSelectedIndex = item->getTag();
		_loginscene->setChangeNickName(selectLabels.at(lastSelectedIndex));
		if (lastSelectedIndex != 0)
		{
			std::string temp;
			temp = selectLabels[0];
			selectLabels[0] = selectLabels[lastSelectedIndex];
			selectLabels[lastSelectedIndex] = temp;

			Vec2 tempPos;
			tempPos = mainMenu->getChildByTag(0)->getPosition();
			mainMenu->getChildByTag(0)->setPosition(mainMenu->getChildByTag(lastSelectedIndex)->getPosition());
			mainMenu->getChildByTag(lastSelectedIndex)->setPosition(tempPos);


			Node*tempnode;
			tempnode = mainMenu->getChildByTag(lastSelectedIndex);
			mainMenu->getChildByTag(0)->setTag(lastSelectedIndex);
			tempnode->setTag(0);
		}
		

	}
	onClose(); //关闭下拉列表框
}

//关闭下拉列表框
void DropDownList::onClose()
{
	removeChild(mainMenu, true);  //通过删除mainMenu,关闭下拉列表框
	isShowMenu = false;
	bgFrame->setVisible(false);
}
void DropDownList::setLoginscene(LoginScene*scene)
{
	_loginscene = scene;
}