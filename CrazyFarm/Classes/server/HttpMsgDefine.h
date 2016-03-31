#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define TIMEOUT 404
struct RewardValue 
{
	int _itemid;
	int _num;
	RewardValue(int itemid, int num){ _itemid = itemid, _num = num; };
	RewardValue(){};
};
struct CDkeyValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> _rewards;

};
struct LoginValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::string _sesssionid;

};
struct RegisterValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::string _sesssionid;
	std::vector<RewardValue> rewards;
};

struct FirstRegisterValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::string _sesssionid;
	std::vector<RewardValue> rewards;
	std::string username;
};
struct SetNameValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
};
struct OpenBoxValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	int  _reward_coins;
	int _chestLevel;
};
