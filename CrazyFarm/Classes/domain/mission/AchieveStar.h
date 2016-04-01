#pragma once

#include "cocos2d.h"I.h"
using namespace cocos2d;


class AchieveStar : public Node{
public:
      
	CREATE_FUNC(AchieveStar);
	void setValue(int total,int finished);
private:
	  std::vector<Sprite*> stars;
	  bool init();
};
