#pragma once

#include "cocos2d.h"
#include "Block/BlockGroup.h"

#include <string>
using std::string;

class CommonFunction
{
public:
	//����ͼ��
    static void GetNewBlockGroup(BlockGroup*& group, BlockGroupType type);

	static BlockGroup* GetDropModeNewBlockGroup();



	static BlockGroupType GetRandonDropModeType();

	static BlockGroupType GetRandonNormalModeType();

	//��ȡϵͳ��ǰʱ��
	static string GetCurrentTime();
};
