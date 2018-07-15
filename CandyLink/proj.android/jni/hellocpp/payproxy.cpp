#include "cocos2d.h"
#include "../../../Classes/MenuScenePayHandler.h"
#include <jni.h>
#include"GameData.h"
#include "CallAndroidMethod.h"
using namespace cocos2d;

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventSuccess(JNIEnv* env,jclass jcl,jint eventId
		,jintArray propIds,jintArray propNums)
	{
		jint *carr;
		carr = env->GetIntArrayElements(propIds, false);
		jint *carr1;
		carr1 = env->GetIntArrayElements(propNums, false);
		jint length=env->GetArrayLength(propIds);
		MenuScenePayHandler::getInstance()->dealEventSuccess(eventId,carr,carr1,length);
	}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventClose(JNIEnv* env,jclass jcl,jint eventId){
	MenuScenePayHandler::getInstance()->dealEventClose(eventId);
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventFail(JNIEnv* env,jclass jcl,jint eventId){

	MenuScenePayHandler::getInstance()->dealEventFail(eventId);
}


extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_showMoreGameNative(JNIEnv* env,jclass jcl,jboolean open){

	MenuScenePayHandler::getInstance()->setMoreGameState(open);
}


extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_showTehui(JNIEnv* env,jclass jcl,jboolean open){

	MenuScenePayHandler::getInstance()->setTehuiState(open);
}





extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniCallbackHelper_GameQuitLogEvent(JNIEnv* env,jclass jcl){

	if (GAMEDATA::getInstance()->levelvector.size() > 0)
	{
		String str;
		for (auto k : GAMEDATA::getInstance()->levelvector)
		{
			str.append(String::createWithFormat("%d", k)->getCString());
		}
		CallAndroidMethod::getInstance()->logevent("Game_quit", str.getCString(), "0");
		GAMEDATA::getInstance()->levelvector.clear();
	}

}









