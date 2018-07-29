#include "CallAndroidMethod.h"
#include "GameData.h"
#include "GameLayer.h"
#include"GameGuiLayer.h"
#include"MenuScenePayHandler.h"
CallAndroidMethod* CallAndroidMethod::_instance = 0;
CallAndroidMethod::CallAndroidMethod(){
}
CallAndroidMethod* CallAndroidMethod::getInstance(){
	if(_instance == 0){
		_instance = new CallAndroidMethod();
	}
	return _instance;
}

void CallAndroidMethod::quit(){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/Activity","quit","()V");
        if(isHave){
            JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
        }
	#endif
}
