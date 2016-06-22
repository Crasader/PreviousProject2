#include "StringManager.h"

USING_NS_CC;

StringManager::StringManager(void)
{
}

StringManager::~StringManager(void)
{

}

StringManager* StringManager::GetInstance()
{
	static StringManager s_manager;
	return &s_manager;
}

string StringManager::GetString(const string& key)
{
	//获取字符串集合
	if (m_strings.empty())
	{
		m_strings = FileUtils::getInstance()->getValueMapFromFile("fonts/strings.xml");
	}

	if (m_strings.find(key) != m_strings.end())
	{
		return m_strings[key].asString();
	}

	return "";
}