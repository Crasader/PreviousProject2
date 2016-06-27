#pragma once
#pragma execution_character_set("utf-8")

#define  SPRITE(path) Sprite::createWithSpriteFrameName(path)


#define MSG_PAUSE               "msg_pause"					//游戏暂停
#define MSG_RESUME              "msg_resume"				//游戏恢复	
#define MSG_REBEGIN				"msg_rebegin"				//重新开始	
#define MSG_BACKMAINSCENE		"msg_backMainScene"			//返回大厅	
#define MSG_USESKILL			"msg_useSkill"				//使用技能XX


enum SkillType
{
	Skill_Knock = 1,
	Skill_Fill = 2,
	Skill_Revivi = 3
};
struct SkillInfo
{
	SkillType Id;
	int num;
};


enum GameTouchType
{
	Touch_Normal,
	Touch_SkillKnock,
	Touch_SkillFill
};