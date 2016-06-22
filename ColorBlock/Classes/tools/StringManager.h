#pragma once

#include "cocos2d.h"
#include <string>

using std::string;

/************************************************************************/
/* �ַ����������ࣺ��Ժ�����ʾ��������                               */
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

