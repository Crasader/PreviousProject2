#include "JniFunUtill.h"
#include "platform\android\jni\JniHelper.h"


JniFunUtill* JniFunUtill::_instance = 0;
JniFunUtill::JniFunUtill(){
}
JniFunUtill* JniFunUtill::getInstance(){
	if(_instance == 0){
		_instance = new JniFunUtill();
	}
	return _instance;
}

const char * JniFunUtill::getSDcardpath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "getSDPath", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return " ";
}