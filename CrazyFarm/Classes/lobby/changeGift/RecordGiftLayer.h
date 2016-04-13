#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "RecordGiftCell.h"
#include "widget/MyTableView.h"
USING_NS_CC;
USING_NS_CC_EXT;



class RecordGiftView :public TableViewDelegate
	, public TableViewDataSource
{
public:
	virtual void scrollViewDidScroll(ScrollView* view) {}
	virtual void scrollViewDidZoom(ScrollView* view){}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t  idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);

	CC_SYNTHESIZE(std::vector<RecordGiftItem>, _items, RecordItem);
};














class RecordGiftLayer : public cocos2d::Layer
{
public:
	virtual bool init(std::vector<RecordGiftItem> items);

	static RecordGiftLayer*create(std::vector<RecordGiftItem> items);
private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	RecordGiftView* tableviewDelegate;
	MyTableView*tableView;
};
