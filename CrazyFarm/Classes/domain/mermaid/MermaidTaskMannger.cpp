#include "MermaidTaskMannger.h"
#include "MermaidTaskBoxLayer.h"
#include "domain/game/GameManage.h"
MermaidTaskMannger* MermaidTaskMannger::_instance = 0;

MermaidTaskMannger* MermaidTaskMannger::getInstence(){
	if (_instance == 0){
		_instance = new MermaidTaskMannger();
	}
	return _instance;
}



MermaidTaskMannger::MermaidTaskMannger(){
	setTaskPlane(nullptr);
}
bool MermaidTaskMannger::isSendInfoToServer(int fishid)
{
	if (_taskPlane)
	{
		auto vec = _taskPlane->getMarriedTaskFishItems();
		for (auto var:vec)
		{
			if (var.fishid == fishid)
			{
				return true;
			}
		}
	}
	return false;
}

void MermaidTaskMannger::onSuccessTask(unsigned int coins)
{
	if (_taskPlane)
	{
		_taskPlane->onFinishSecuss();
	}
	setTaskPlane(nullptr);
	auto layer = MermaidTaskBoxLayer::create();
	layer->setcoins(coins);
	GameManage::getInstance()->getGuiLayer()->addChild(layer, 300);
}