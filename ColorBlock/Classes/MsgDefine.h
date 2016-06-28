#pragma once
#pragma execution_character_set("utf-8")

#define  SPRITE(path) Sprite::createWithSpriteFrameName(path)


#define MSG_PAUSE               "msg_pause"					//��Ϸ��ͣ
#define MSG_RESUME              "msg_resume"				//��Ϸ�ָ�	
#define MSG_REBEGIN				"msg_rebegin"				//���¿�ʼ	
#define MSG_BACKMAINSCENE		"msg_backMainScene"			//���ش���	
#define MSG_USESKILL			"msg_useSkill"				//ʹ�ü���XX
#define MSG_GAMEOVER            "msg_gameover"              //��Ϸ����

enum SkillType
{
	Skill_Knock = 81,
	Skill_Fill = 82,
	Skill_Revivi = 83
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