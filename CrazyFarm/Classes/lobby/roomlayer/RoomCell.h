#pragma once

#include "cocos2d.h"
#include "utill/AnimationUtil.h"
#include "config/ConfigRoom.h"
#include "utill/dayUtil.h"
#include "domain/user/User.h"
using namespace cocos2d;





class RoomCell :public MenuItemImage
{
public:
	static RoomCell * createCell(Room room);
	bool init(Room room);
	void lockRoom();
	void setPlayerNum();
	void stopNormalAni();
	void resumeNormalAni();
	void playScaleAni();
	CC_SYNTHESIZE(bool, isLock, Islock);
private:
	Room m_room;
	void clickCallBack(Ref*psend);
	void TiPCallBack(Ref*psend);

	void playNormalAni();
	Sprite* caidai = nullptr;
	std::vector<Node*> anis;
	bool IsloveOn = false;
	Sprite* roomCircleLight = nullptr;
};


