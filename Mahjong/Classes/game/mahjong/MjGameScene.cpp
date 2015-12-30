#include"game\mahjong\MjGameScene.h"
#include"game\mahjong\MahjongView.h"

bool MjGameScene::init(){
	if (!Scene::init()){
		return false;
	}
	MahjongView* mjView = MahjongView::create();
	this->addChild(mjView);
	return true;
}