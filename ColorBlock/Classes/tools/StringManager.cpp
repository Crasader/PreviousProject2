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
	//��ȡ�ַ�������
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