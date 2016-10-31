#include "AppDelegate.h"
#include "HallScene.h"
#include "GameScene.h"
#include "AnimationUtil.h"
#include "audio/include/AudioEngine.h"
#include "MenuScenePayHandler.h"
#include "PxPayMannger.h"
#include "User.h"
#include "TipScene.h"
USING_NS_CC;
using namespace experimental;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("My Game");
		director->setOpenGLView(glview);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_MAC)
	glview->setFrameSize(800, 480);
	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (visibleSize.width / visibleSize.height > 800.0 / 480.0){
		glview->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);
	}
	else{
		glview->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);
	}
#endif


	// turn on display FPS
	//director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	FileUtils::getInstance()->addSearchPath("Sign");
	FileUtils::getInstance()->addSearchPath("shop");
	FileUtils::getInstance()->addSearchPath("role");
	FileUtils::getInstance()->addSearchPath("Hall");
	FileUtils::getInstance()->addSearchPath("System_UI");
	FileUtils::getInstance()->addSearchPath("RedPack");
	AnimationUtil::getInstance()->init();

	srand(time(NULL));
	//auto scene = HallScene::createScene();
	auto scene = TipScene::createScene();

	// run
	if (nullptr == director->getRunningScene())
	{
		director->runWithScene(scene);
	}
	else
	{
		director->replaceScene(scene);
	}

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	if (!PxPayMannger::getInstance()->getIsOnpaying())
	{
		Jniutill::getInstance()->logEvent("退出时候金币", Value(User::getInstance()->getMyCoins()).asString());
	}
	// if you use SimpleAudioEngine, it must be pause
	AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	AudioEngine::resumeAll();

	if (PxPayMannger::getInstance()->getIsOnpaying())
	{
		Jniutill::getInstance()->queryOrder();
	}
}
