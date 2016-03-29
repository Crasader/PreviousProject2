#include "LoginMannger.h"
#include "domain/user/User.h"
#include "domain/user/DeviceInfo.h"
#include "server/HttpMannger.h"


LoginMannger* LoginMannger::_instance = NULL;

LoginMannger::LoginMannger(){
	setisLoginSuccess(false);
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
	if (temp.at(0) == 'g'&&temp.at(1)=='_')
	{
		return true;
	}
	return false;
}
void LoginMannger::loadMemoryNickname()
{
	int i = 0;
	while (1)
	{
		auto key = Value(KEY_USERNICKNAME_).asString() + Value(i).asString();
		auto nickname = UserDefault::getInstance()->getStringForKey(key.c_str(),"guest");
		if (nickname!="guest")
		{
			_memoryNickname.push_back(nickname.c_str());
			i++;
		}
		else
		{
			break;
		}
	}
	return;
}

void LoginMannger::addMemoryNickname(const char*_nickName, const char*_password)
{
	for (auto var:_memoryNickname)
	{
		if (var == _nickName)
		{
			return;
		}
	}
	int i = 0;
	while (1)
	{
		auto key = Value(KEY_USERNICKNAME_).asString() + Value(i).asString();
		auto nickname = UserDefault::getInstance()->getStringForKey(key.c_str(), "guest");
		if (nickname == "guest")
		{
			UserDefault::getInstance()->setStringForKey(key.c_str(), _nickName);
			UserDefault::getInstance()->setStringForKey(_nickName, _password);
			_memoryNickname.push_back(_nickName);
			break;
		}
		else
		{
			i++;
		}
	}
	return;
}