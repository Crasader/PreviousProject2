#include "cocos2d.h"
#include <jni.h>
#include "domain/pay/pay.h"
#include "server/HttpMannger.h"
#include "platform\android\jni\JniHelper.h"
using namespace cocos2d;





extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_payResultCallBack(JNIEnv* env,jclass jcl,jint code
		,jstring msg)
	{
		String *ret = new String(JniHelper::jstring2string(msg).c_str());
		Pay::getInstance()->jniCallBack(code,ret->getCString());
	}


extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_sendFeedback(JNIEnv* env,jclass jcl,jstring msg)
	{
		String *ret = new String(JniHelper::jstring2string(msg).c_str());
		HttpMannger::getInstance()->HttpToPostRequestFeedback(ret->getCString());
	}
