#pragma once
#include "cocos2d.h"
#include "utill/define.h"
#define  KEY_USERNICKNAME_  "KEY_USERNICKNAME_"
using namespace cocos2d;





class LoginMannger{
public:
	static LoginMannger* getInstance();
	void toRegister();
	void toRegister(const char*nickname, const char* password, int gender);
	void toLogin(const char* nickname, const char* password);
	void loadMemoryNickname();
	std::list<std::string> getMemoryNickname(){ loadMemoryNickname(); return _memoryNickname; };

	bool checkNicknameIsdefault(const char* nickname);
	void addMemoryNickname(const char*_nickName, const char*_password);
	void removeMemoryNickname(const char*_nickName);
private:
	LoginMannger();
	static LoginMannger* _instance;




	
	std::list<std::string> _memoryNickname;

};

