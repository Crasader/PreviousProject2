#include "RecordGiftCell.h"
#include "utill/Chinese.h"
#include "domain/ranklist/RanklistManager.h"
#include "config/ConfigExp.h"
bool RecordGiftCell::init(){

	bg = ui::Scale9Sprite::create();
	bg->setAnchorPoint(Point::ZERO);
	bg->setContentSize(Size(915,72));
	bg->setPosition(0,0);
	addChild(bg);

	dataTTF = LabelTTF::create("", "arial", 20);
	dataTTF->setColor(Color3B(35, 66, 98));
	dataTTF->setPosition(109, 35);
	addChild(dataTTF);

	stateTTF = LabelTTF::create("", "arial", 20);
	stateTTF->setColor(Color3B(35, 66, 98));
	stateTTF->setPosition(808, 35);
	addChild(stateTTF);

	nameTTF = LabelTTF::create("", "arial", 20);
	nameTTF->setColor(Color3B(35, 66, 98));
	nameTTF->setPosition(330, 35);
	addChild(nameTTF);


	return true;
}


void RecordGiftCell::setValue(RecordGiftItem item)
{
	dataTTF->setString(Value(item._date).asString());
	stateTTF->setString(item.change_state);
	nameTTF->setString(item.reward_desc);
}