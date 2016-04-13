#include "moment/MomentNine.h"
#include "utill/FunUtil.h"
#include "fish/FishManage.h"
#include "data/GameData.h"
void MomentNine::init(float FFOneTime)
{
	
	FishManage::getInstance()->onClearFish();
}

bool MomentNine::updata(float dt)
{
	nNowtime += dt;
	if (nNowtime>2)
	{
		GameData::getInstance()->setisOnGroupComing(true);
	}
	return false;

}
