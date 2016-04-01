#include "AchieveView.h"
void AchieveView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size AchieveView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(700, 106);
}
cocos2d::extension::TableViewCell* AchieveView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	AchieveCell *cell = (AchieveCell*)table->dequeueCell();
	if (!cell) {
		cell = AchieveCell::create();
	}
	else
	{

	}
	cell->setValue(MissionManager::getInstance()->getAchieveListData().at(idx));
	return cell;
}
ssize_t AchieveView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return MissionManager::getInstance()->getAchieveListData().size();
}
