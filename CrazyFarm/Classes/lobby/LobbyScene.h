#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class LobbyScene : public cocos2d::Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void startGame();

	void rechargeGold();

	void showSettingLayer();

	void createRoomLayer();

	void autoStartGame(float dt);

	void updateScene(float dt);

	void loadResource();

    CREATE_FUNC(LobbyScene);


    ///房间列表
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {}
	virtual void tableCellTouched(TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual extension::TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
};
#endif