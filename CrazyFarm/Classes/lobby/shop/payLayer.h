#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "payCell.h"
USING_NS_CC;
USING_NS_CC_EXT;

class payTableViewCell : public TableViewCell
{
public:
	CREATE_FUNC(payTableViewCell);
	virtual bool init();
	void setPayValue(int idx);
private:
	PayCell* cell0;
	PayCell* cell1;
	PayCell* cell2;
};


class payView :public TableViewDelegate
	, public TableViewDataSource
{
public:
	virtual void scrollViewDidScroll(ScrollView* view) {}
	virtual void scrollViewDidZoom(ScrollView* view){}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t  idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
private:


};













class payLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(payLayer);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return false; };

private:
	void closeButtonCallBack(Ref*psend);

	payView* tableviewDelegate;
};
