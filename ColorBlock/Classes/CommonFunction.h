#pragma once

#include "cocos2d.h"
#include "Block/BlockGroup.h"

#include <string>
using std::string;

class CommonFunction
{
public:
	//重置图形
    static void GetNewBlockGroup(BlockGroup*& group, BlockGroupType type);

	static BlockGroup* GetDropModeNewBlockGroup();



	static BlockGroupType GetRandonDropModeType();

	static BlockGroupType GetRandonNormalModeType();

	//获取系统当前时间
	static string GetCurrentTime();
};
