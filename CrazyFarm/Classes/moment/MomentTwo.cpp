#include "moment/MomentTwo.h"
#include "fish/FishGroupData.h"

void MomentTwo::initData()
{
	MomentIntervalCreate::initData();
	m_groupTag = 1;
	fishMinSize = 10;
}