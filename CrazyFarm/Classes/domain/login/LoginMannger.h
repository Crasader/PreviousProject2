#pragma once
#include "cocos2d.h"
#include "utill/define.h"
#define  KEY_USERNICKNAME_  "KEY_USERNICKNAME_"
using namespace cocos2d;


struct loginInfo 
{
	char* _nickName;
	char* _password;
};


class LoginMannger{
public:
	static LoginMannger* getInstance();
	void toRegister();
	void toLogin(const char* nickname, const char* password);
	void loadMemoryNickname();
	std::vector<std::string> getMemoryNickname(){ return _memoryNickname; };

	bool checkNicknameIsdefault(const char* nickname);
	void addMemoryNickname(const char*_nickName, const char*_password);
private:
	LoginMannger();
	static LoginMannger* _instance;
	CC_SYNTHESIZE(bool, _isLoginSuccess, isLoginSuccess);



	
	std::vector<std::string> _memoryNickname;

};

