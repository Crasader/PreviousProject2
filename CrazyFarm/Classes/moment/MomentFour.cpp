#include "moment/MomentFour.h"
#include "fish/FishGroupData.h"

void MomentFour::initData()
{
	MomentIntervalCreate::initData();
	m_groupTag = 3;
	fishMinSize = 10;
}