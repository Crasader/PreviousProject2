#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct SkillConfigInfo {
    int skill_id;
    int item_id; // 对应道具编号
    int unlock_buy_type; // 解锁购买类型 0,炮台等级;1，vip等级
    int unlock_buy_level;  // 结果购买等级
    int cd_time;        // 技能持续时间。0表示不需要等待。
};


class ConfigSkill {
    
public:
	ConfigSkill();
	static ConfigSkill* getInstance();
    
	bool LoadConfig();
    
    SkillConfigInfo getskillConfigInfoByItemId(int itemId);
    SkillConfigInfo getskillConfigInfoBySkillId(int skillId);
private:
	static ConfigSkill* _instance;
	
    std::map<int, SkillConfigInfo> skillConfigInfos;
};

