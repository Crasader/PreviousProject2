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


const char* JniFunUtill::getImei()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/GameExtend", "getImei", "()Ljava/lang/String;")) {
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
const char*JniFunUtill::getHdFactory()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/GameExtend", "getHdFactory", "()Ljava/lang/String;")) {
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
const char*JniFunUtill::getHdType()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/GameExtend", "getHdType", "()Ljava/lang/String;")) {
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

void JniFunUtill::pay(int price, const char* orderid)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity","pay","(ILjava/lang/String;)V");
	jstring jorderid = methodInfo.env->NewStringUTF(orderid);
	jint jprice = price;
	if(isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,jprice,jorderid);
}
#endif
}
