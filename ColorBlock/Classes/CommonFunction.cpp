#include "CommonFunction.h"
#include "Block/BlockGroupO.h"
#include "Block/BlockGroupI.h"
#include "Block/BlockGroupS.h"
#include "Block/BlockGroupZ.h"
#include "Block/BlockGroupT.h"
#include "Block/BlockGroupL.h"
#include "Block/BlockGroupJ.h"
#include "Block/BlockGroupDOne.h"
#include "Block/BlockGroupDTwo.h"
#include "Block/BlockGroupDThree.h"
#include "Block/BlockGroupDFour.h"
#include "Block/BlockGroupDFive.h"
#include "Block/BlockGroupDSix.h"
#include "Block/BlockGroupDSeven.h"

USING_NS_CC;

//重置图形
void CommonFunction::GetNewBlockGroup(BlockGroup*& group, BlockGroupType type)
{
	switch (type)
	{
	case BlockGroupType::BlockGroupType_O:
		group = new BlockGroupO();
		group->SetBlockGroupDirection(BlockGroupDirection::BGD_0);
		break;
	case BlockGroupType::BlockGroupType_I:
		group = new BlockGroupI();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
		break;
	case BlockGroupType::BlockGroupType_S:
		group = new BlockGroupS();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
		break;
	case BlockGroupType::BlockGroupType_Z:
		group = new BlockGroupZ();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
		break;
	case BlockGroupType::BlockGroupType_T:
		group = new BlockGroupT();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 4));
		break;
	case BlockGroupType::BlockGroupType_L:
		group = new BlockGroupL();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 4));
		break;
	case BlockGroupType::BlockGroupType_J:
		group = new BlockGroupJ();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 4));
		break;
	default:
		group = NULL;
		break;
	}
}
BlockGroup*  CommonFunction::GetDropModeNewBlockGroup()
{
	BlockGroup* group = nullptr;
	BlockGroupType type = GetRandonDropModeType();
	switch (type)
	{
	case BlockGroupType_I:
			group = new BlockGroupI();
			group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
			break;
	case BlockGroupType_O:
		group = new BlockGroupO();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
		break;
	case BlockGroupType_1:
		group = new BlockGroupDOne();
		group->SetBlockGroupDirection(BGD_0);
		break;
	case BlockGroupType_2:
		group = new BlockGroupDTwo();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
		break;
	case BlockGroupType_3:
		group = new BlockGroupDThree();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
		break;
	case BlockGroupType_4:
		group = new BlockGroupDFour();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 4));
		break;
	case BlockGroupType_5:
		group = new BlockGroupDFive();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 2));
		break;
	case BlockGroupType_6:
		group = new BlockGroupDSix();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 4));
		break;
	case BlockGroupType_7:
		group = new BlockGroupDSeven();
		group->SetBlockGroupDirection(BlockGroupDirection(rand() % 1));
		break;


	default:
		break;
	}
	if (group)
	{
		group->initBlockGroupInDropMode(rand() % SpriteManager::GetInstance()->GetBlockTypeNumber());
	}
	return group;

}

int addVecNum(std::vector<int> vec, int index)
{	
	int result = 0;
	if (index-1>vec.size())
	{
		return -1;
	}
	for (int i = 0; i < index;i++)
	{
		result += vec.at(i);
	}
	return result;
}

BlockGroupType CommonFunction::GetRandonNormalModeType()
{
	BlockGroupType blocktype[] = { BlockGroupType_T, BlockGroupType_S, BlockGroupType_Z, BlockGroupType_L, BlockGroupType_J, BlockGroupType_O, BlockGroupType_I };
	int a[] = { 137, 164, 164, 137, 137, 136, 125 };
	vector<int> ivector(a, a + 7);
	int random = rand() % 1000+1;
	for (int i = 0; i<ivector.size();i++)
	{
		if (random <= addVecNum(ivector,i+1))
		{
			return blocktype[i];
		}
	}
	return blocktype[0];

}

BlockGroupType CommonFunction::GetRandonDropModeType()
{
	BlockGroupType blocktype[] = { BlockGroupType_1, BlockGroupType_2, BlockGroupType_3, BlockGroupType_I, BlockGroupType_5, BlockGroupType_4, BlockGroupType_6,BlockGroupType_O, BlockGroupType_7 };
	int a[] = { 54, 140, 48, 116, 110, 196, 208,60,68 };
	vector<int> ivector(a, a + 9);
	int random = rand() % 1000 + 1;
	for (int i = 0; i < ivector.size(); i++)
	{
		if (random <= addVecNum(ivector, i+1))
		{
			return blocktype[i];
		}
	}
	return blocktype[0];
}












//获取系统当前时间
string CommonFunction::GetCurrentTime()
{
	string strCurTime;

	time_t timet;
	struct tm *curTime = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	struct timeval now;
	gettimeofday(&now, NULL);

	timet = now.tv_sec;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	time(&timet);
#endif

	//获取当前时间
	curTime = localtime(&timet);

	//格式化时间
	strCurTime = StringUtils::format("%04d-%02d-%02d %02d:%02d:%02d",
		curTime->tm_year + 1900, curTime->tm_mon + 1, curTime->tm_mday,
		curTime->tm_hour, curTime->tm_min, curTime->tm_sec);

	return strCurTime;
}