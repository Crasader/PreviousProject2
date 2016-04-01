#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MissionCell.h"
#include "widget/MyTableView.h"
USING_NS_CC;
USING_NS_CC_EXT;



class MissionView :public TableViewDelegate
	, public TableViewDataSource
{
public:
	virtual void scrollViewDidScroll(ui::ScrollView* view) {}
	virtual void scrollViewDidZoom(ui::ScrollView* view){}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t  idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
private:
};
