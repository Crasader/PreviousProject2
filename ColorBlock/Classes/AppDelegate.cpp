#include "AppDelegate.h"
#include "LogoScene.h"
#include "MainScene.h"
#include "AppMacros.h"

#include <vector>
#include <string>

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
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
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Color Block");
        director->setOpenGLView(glview);
    }

	//960*640
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(480, 800);
#else
	director->setDisplayStats(false);
#endif
	director->setOpenGLView(glview);

	// Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	// a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
#else
	glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);
#endif
	
	Size frameSize = glview->getFrameSize();

	vector<string> searchPath;

	searchPath.push_back("game/MainScene");
	searchPath.push_back("game/fonts");
	searchPath.push_back("game/GameScane");
	searchPath.push_back("game");
	FileUtils::getInstance()->setSearchPaths(searchPath);

    // turn on display FPS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	director->setDisplayStats(true);
#else
	director->setDisplayStats(false);
#endif
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object
	auto scene = MainScene::createScene();

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
