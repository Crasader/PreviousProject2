#ifndef __MY_TABLE_VIEW_H__
#define __MY_TABLE_VIEW_H__
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC_EXT;
USING_NS_CC;
class MyTableView: public TableView
{
public:
	static MyTableView * create(TableViewDataSource* dataSource, Size size);

	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	Point &getLastEnd(){return mLastEnd;}
private:
	MyTableView(){}
	Point mLastEnd;
};


#endif