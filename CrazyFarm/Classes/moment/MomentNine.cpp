#include "moment/MomentNine.h"
#include "utill/FunUtil.h"
#include "fish/FishManage.h"
void MomentNine::init()
{
	FishManage::getInstance()->onClearFish();
}

bool MomentNine::updata(float dt)
{
	nNowtime += dt;
	if (nNowtime>20)
	{
		return true;
	}
	return false;

}
