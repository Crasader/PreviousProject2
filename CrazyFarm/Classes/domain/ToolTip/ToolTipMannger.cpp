#include "ToolTipMannger.h"
#include "TwiceSureDialog.h"
#include "utill/Chinese.h"

void ToolTipMannger::ShowPayTimeoutTip()
{
	auto dialog = TwiceSureDialog::createDialog(ChineseWord("netTimeOut").c_str());
	dialog->setPosition(0, 0);
	Director::getInstance()->getRunningScene()->addChild(dialog, 20);
}
void ToolTipMannger::ShowPaySuccessTip()
{
	auto dialog = TwiceSureDialog::createDialog(ChineseWord("BuySuccess").c_str());
	dialog->setPosition(0, 0);
	Director::getInstance()->getRunningScene()->addChild(dialog, 20);
}
