#include "Jniutill.h"
#include "platform\android\jni\JniHelper.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define JAVA_SRC getJniPath()
Jniutill* Jniutill::_instance = 0;
Jniutill::Jniutill(){

	std::string filename = "game/ConfigJnipath.json";
	rapidjson::Document doc;
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	_jniPath = doc["JniPath"].GetString();
}
Jniutill* Jniutill::getInstance(){
	if(_instance == 0){
		_instance = new Jniutill();
	}
	return _instance;
}
const char*  Jniutill::getJniPath()
{
	return _jniPath.c_str();
}
void Jniutill::showMoreGame(){
	CCLOG(">>>>>>>>>>>>>>showMoreGame");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	    log("android platform");
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/NetWorkService");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"showMoreGame","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

void Jniutill::quit(){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	log("android platform");
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/NetWorkService");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"quit","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

void  Jniutill::requestEvent(int eventId){

	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/PayService");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"pay","(I)V");
		jint pay_point = eventId;
		//jint reviveNum = GAMEDATA::getInstance()->getReviveNum();
		if(isHave){
			jobject jobj;
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pay_point);
		}
#endif	

}

