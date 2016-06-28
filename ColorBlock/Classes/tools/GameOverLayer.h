#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "BaseLayer.h"

class GameOverLayer : public BaseLayer
{
public:	
	static GameOverLayer*create(int score);
private:
	void update(float delta);
	virtual bool init(int score);
private:
	int _score;
	float _totalTime = 0;
	LabelAtlas*label;

};

#endif // __GAMEOVER_LAYER_H__