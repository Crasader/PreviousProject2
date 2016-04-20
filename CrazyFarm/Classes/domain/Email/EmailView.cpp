#include "EmailView.h"
#include "EmailManager.h"
void EmailView::tableCellTouched(TableView* table, TableViewCell* cell){
	MyTableView * myTableView = (MyTableView*)table;
	Point lastEnd = myTableView->getLastEnd();
	((EmailCell*)cell)->IsBeToued();
	if (lastTouchCell)
	{
		lastTouchCell->setIsTouched(false);
	}
	((EmailCell*)cell)->setIsTouched(true);
	lastTouchCell = ((EmailCell*)cell);
	
}
Size EmailView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(339, 61);
}
cocos2d::extension::TableViewCell* EmailView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	EmailCell *cell = (EmailCell*)table->dequeueCell();
	if (!cell) {
		cell = EmailCell::create();
	}
	else
	{

	}
	cell->setValue(EmailManager::getInstance()->getEmailListData().at(idx));
	return cell;
}
ssize_t EmailView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return EmailManager::getInstance()->getEmailListData().size();
}
