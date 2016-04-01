#include "MissionView.h"
void MissionView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size MissionView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(700, 106);
}
cocos2d::extension::TableViewCell* MissionView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	MissionCell *cell = (MissionCell*)table->dequeueCell();
	if (!cell) {
		cell = MissionCell::create();
	}
	else
	{

	}
	cell->setValue(MissionManager::getInstance()->getMissionListData().at(idx));
	return cell;
}
ssize_t MissionView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return MissionManager::getInstance()->getMissionListData().size();
}
