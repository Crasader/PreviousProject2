#include "LoginMannger.h"
#include "domain/user/User.h"
#include "domain/user/DeviceInfo.h"
#include "server/HttpMannger.h"


LoginMannger* LoginMannger::_instance = NULL;

LoginMannger::LoginMannger(){
	
}


LoginMannger* LoginMannger::getInstance(){
	if (_instance == NULL){
		_instance = new LoginMannger();
	}
	return _instance;
}
void LoginMannger::toRegister()
{
	HttpMannger::getInstance()->HttpToPostRequestRegisterInfo(DeviceInfo::getChannel_id(), DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
}
void LoginMannger::toRegister(const char*nickname, const char* password, int gender)
{
	HttpMannger::getInstance()->HttpToPostRequestRegisterForwardly(nickname,password,gender,DeviceInfo::getChannel_id(), DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
}
void LoginMannger::toLogin(const char* nickname,const char* password)
{
	
	bool isDefult = checkNicknameIsdefault(nickname);
	if (isDefult)
	{
		HttpMannger::getInstance()->HttpToPostRequestLogInInfo(DeviceInfo::getChannel_id(),nickname, DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
	}
	else
	{
		HttpMannger::getInstance()->HttpToPostRequestLogInByName(nickname, password);
	}
	
}
bool LoginMannger::checkNicknameIsdefault(const char* nickname)
{
	std::string temp = nickname;
	if (temp.size()<0)
	{
		return false;
	}
	if (temp.at(0) == 'g'&&temp.at(1)=='_')
	{
		return true;
	}
	return false;
}
void LoginMannger::loadMemoryNickname()
{
	_memoryNickname.clear();
	for (int i = 0; i < 5;i++)
	{
		auto key = Value(KEY_USERNICKNAME_).asString() + Value(i).asString();
		auto nickname = UserDefault::getInstance()->getStringForKey(key.c_str(), "guest");
		if (nickname != "guest")
		{
			_memoryNickname.push_back(nickname.c_str());
		}
	}
	return;
}

void LoginMannger::addMemoryNickname(const char*_nickName, const char*_password)
{
	UserDefault::getInstance()->setStringForKey(_nickName, _password);
	for (auto var:_memoryNickname)
	{
		if (var == _nickName)
		{
			_memoryNickname.remove(_nickName);
			break;
		}
	}
	_memoryNickname.push_back(_nickName);
	int i = 0;
	for (auto var:_memoryNickname)
	{
		auto key = Value(KEY_USERNICKNAME_).asString() + Value(i).asString();
		UserDefault::getInstance()->setStringForKey(key.c_str(), var.c_str());
		i++;
	}
	return;
}


void LoginMannger::removeMemoryNickname(const char*_nickName)
{
	for (auto var : _memoryNickname)
	{
		if (var == _nickName)
		{
			_memoryNickname.remove(_nickName);
			break;
		}
	}
	int i = 0;
	for (int i = 0; i < 5;i++)
	{
		auto key = Value(KEY_USERNICKNAME_).asString() + Value(i).asString();
		auto nickname = UserDefault::getInstance()->getStringForKey(key.c_str(), "guest");
		if (nickname == _nickName)
		{
			UserDefault::getInstance()->setStringForKey(key.c_str(), "guest");
			UserDefault::getInstance()->setStringForKey(_nickName, "");
			break;
		}
	}

	return;
}