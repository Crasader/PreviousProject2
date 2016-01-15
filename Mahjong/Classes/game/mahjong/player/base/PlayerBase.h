#ifndef __PLAYER_BASE__
#define __PLAYER_BASE__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"

USING_NS_CC;

class PlayerBase :public Layer{
public:
	const int jongNum = 13;

	virtual bool init();

	void drawHeadPortrait(PlayerInfo* playerInfo);

	void setHeadPostion(Point pos);

	CREATE_FUNC(PlayerBase);
private:
	Sprite* head_bg;
	Label* nickName;
	Sprite* headimage;
	Sprite* diamond;
	LabelAtlas* diamondNum;

	Sprite*          mStencil;       // 蒙板精灵,绿色半透明
	ProgressTimer*   mProgressTimer; // 时间进度条精灵(360度旋转)
	float            mCDTime;         // 时间
	void  timeAnim();
};
#endif