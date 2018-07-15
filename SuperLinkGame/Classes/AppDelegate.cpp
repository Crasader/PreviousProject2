#include "AppDelegate.h"
#include "LobbyScene.h"

USING_NS_CC;

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
		glview = GLViewImpl::create("SuperLinkGame");
		director->setOpenGLView(glview);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(480, 800);
	glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (visibleSize.width / visibleSize.height > 800.0 / 480.0){//竖屏方向拉伸变形
		//拉伸变形，铺满屏幕
		//假设：屏幕分辨率（fWidth，fHeight） ； 设计分辨率（dWidth，dHeight）。
		//放缩因子：k1 = fWidth/dWidth ； k2 = fHeight/dHeight。
		//EXACT_FIT= dWidth * k1, dHeight * k2 
		glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);
	}
	else{
		//全屏展示，不留黑边
		//NO_BORDER: dWidth * max(k1,k2) , dHeight * max(k1,k2)
		glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);
	}
#endif
	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = LobbyScene::createScene();

	// run
	director->runWithScene(scene);


	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
