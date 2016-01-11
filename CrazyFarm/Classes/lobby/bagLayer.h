#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "lobby/bag/BagCell.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CustomTableViewCell : public TableViewCell
{
public:
	CREATE_FUNC(CustomTableViewCell);
	virtual bool init();
	void setPayValue(int idx);
private:
	BagCell* cell0;
	BagCell* cell1;
	BagCell* cell2;
};


class BagView :public TableViewDelegate
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














class BagLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(BagLayer);

private:
	void closeButtonCallBack(Ref*psend);

	void chankanCallBack(Ref*);
	BagView* tableviewDelegate;
};
