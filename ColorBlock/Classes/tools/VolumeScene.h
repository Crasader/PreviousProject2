#ifndef __VOLUME_SCENE_H__
#define __VOLUME_SCENE_H__

#include "cocos2d.h"
#include "ui/UISlider.h"
USING_NS_CC;
class VolumeScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
	void menuCloseCallback(Ref *pSender, ui::Slider::EventType type);
    void menuCallOK(cocos2d::Ref* pSender);
	void menuCallreturn(Ref *pSender);
	void sliderEvent(Ref *pSender, ui::Slider::EventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(VolumeScene);

private:
	cocos2d::ui::Slider*	m_volumeSlider;
	cocos2d::ui::Slider*	m_volumeEffectslider;
};

#endif // __VOLUME_SCENE_H__
