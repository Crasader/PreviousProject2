#include "AppDelegate.h"
#include "HelloWorldScene.h"
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
		glview = GLViewImpl::create("CrazyFarm");
		director->setOpenGLView(glview);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	glview->setFrameSize(960, 540);
	glview->setDesignResolutionSize(960, 540, ResolutionPolicy::EXACT_FIT);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (visibleSize.width / visibleSize.height > 960.0 / 540.0){

		glview->setDesignResolutionSize(960, 540, ResolutionPolicy::EXACT_FIT);
	}
	else{
		glview->setDesignResolutionSize(960, 540, ResolutionPolicy::EXACT_FIT);
	}
#endif
    
	// turn on display FPS
	director->setDisplayStats(true);
	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);
	auto  scene = HelloWorld::createScene();
	director->runWithScene(scene);


	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {


}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {


}

