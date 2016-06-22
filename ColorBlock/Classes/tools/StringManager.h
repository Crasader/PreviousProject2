#pragma once

#include "cocos2d.h"
#include <string>

using std::string;

/************************************************************************/
/* 字符串管理单例类：针对汉字显示作出处理                               */
/************************************************************************/

class StringManager
{
public:
	static StringManager* GetInstance();
	~StringManager(void);
	
public:
	string GetString(const string& key);

private:
	StringManager(void);

private:
	cocos2d::ValueMap	m_strings;
};

