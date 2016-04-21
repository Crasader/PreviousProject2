#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ActiveCell.h"
#include "widget/MyTableView.h"
USING_NS_CC;
USING_NS_CC_EXT;



class ActivetView :public TableViewDelegate
	, public TableViewDataSource
{
public:
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {}
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view){}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t  idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	void addImg(std::string str);
private:
	std::vector<std::string> itemImgs;

};














class ActiveLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(ActiveLayer);

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	ActivetView* tableviewDelegate;
	MyTableView* tableView;

	void update(float dt);
	std::vector<std::string> imgs;

};
