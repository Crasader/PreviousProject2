#include "domain/pay/Pay.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h"
#include "utill/JniFunUtill.h"
#include "PayEventPointConfig.h"
#include "domain/user/DeviceInfo.h"
#include "server/HttpMannger.h"
#include "utill/JniFunUtill.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "utill/Chinese.h"
#include "data/GameData.h"
#include "domain/game/GameManage.h"
#include "config/ConfigVipLevel.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "WaitCircle.h"
#define PAYPOSTREQUEST "http://114.119.39.150:1701/mo/order/booking"

Pay* Pay::_instance = NULL;

Pay::Pay(){
    this->init();
}

bool Pay::init(){
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
	return true;
}

Pay* Pay::getInstance(){
    if(_instance == NULL){
        _instance = new Pay();
    }
    return _instance;
}
void Pay::Overbooking(int paypoint, int eventPoint, Node*paynode)
{
	/*if (isPaying)
	{
	return;
	}*/
	isPaying = true;
	auto sessioned = User::getInstance()->getSessionid();
	if (sessioned=="")
	{
		HttpMannger::getInstance()->HttpToPostRequestLogInInfo(DeviceInfo::getChannel_id(), User::getInstance()->getUserId(), DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
		paynode->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]{OverbookingActual(paypoint, eventPoint); }), nullptr));
	}
	else
	{
		OverbookingActual(paypoint, eventPoint);
	}

}
void Pay::OverbookingActual(int paypoint, int eventPoint)
{
	auto sessioned = User::getInstance()->getSessionid();
	if (sessioned == "")
	{
		isPaying = false;
		ToolTipMannger::ShowPayTimeoutTip();
		return; 
	}
	int payeventVersion = PayEventPointConfig::getInstance()->getPayeventVersion();
	int payPointVersion = PayPointConfig::getInstance()->getVersion();
	auto payPointInfo = PayPointConfig::getInstance()->getPayPointInfoById(paypoint);
	auto channel_id = DeviceInfo::getChannel_id();
	auto sessionid = User::getInstance()->getSessionid();
	int price = payPointInfo.price;
	HttpMannger::getInstance()->HttpToPostRequestBeforePay(sessionid, payPointVersion * 1000 + payeventVersion, eventPoint, paypoint, channel_id,payPointInfo.pay_point_desc,price);
}

void Pay::pay(payRequest*data)
{
	prepayidToPayRequest[data->wx_prepayid] = data;
	log("pushback data wx_prepayid = %s", data->wx_prepayid.c_str());

	payResult = -1;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	payCallBack(0, "success", data->wx_prepayid);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	payCallBack(0, "success",data->wx_prepayid);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	switch (data->third_payType)
	{	
	//微信支付
	case 1:
		JniFunUtill::getInstance()->WXPay(data->wx_prepayid.c_str(),data->wx_nonceStr.c_str(),data->wx_timestamp.c_str(),data->wx_sign.c_str());
		break;
	case 0:
		JniFunUtill::getInstance()->SKYPay(PayPointConfig::getInstance()->getPayPointInfoById(data->pay_point_id).price, data->orderID.c_str());
		break;
	default:
		JniFunUtill::getInstance()->SKYPay(PayPointConfig::getInstance()->getPayPointInfoById(data->pay_point_id).price, data->orderID.c_str());
		break;
}
#endif
}
std::string Pay::getOrderIdByprepayid(std::string prepayid)
{
	if (!(prepayidToPayRequest.find(prepayid) != prepayidToPayRequest.end()))
	{

		return "";
	}
	else
	{
		return prepayidToPayRequest[prepayid]->orderID;
	}
}
void Pay::jniCallBack(int code, const char*msg, const char*wx_prepayid)
{
	log("jni callBack code = %d",code);
	if (code == 0)
	{
		if (!(prepayidToPayRequest.find(wx_prepayid) != prepayidToPayRequest.end()))
		{
			log("have no data on client %s",wx_prepayid);
			return;
		}
		auto circle = WaitCircle::ShowPayWaitCircle();
		circle->setMyPrepayid(wx_prepayid);
		circle->setName(wx_prepayid);
	}
	else
	{
		payCallBack(code, msg,wx_prepayid);
	}
}
void Pay::DemandEntry(int reqNum, std::string orederid)
{
	HttpMannger::getInstance()->HttpToPostRequestDemandEntry(orederid, reqNum);
}
void Pay::payCallBack(int code, const char* msg, std::string prepayid)
{
	WaitCircle::RemovePayWaitCircle(prepayid);
	isPaying = false;
	log("pay callback success");
	if (!(prepayidToPayRequest.find(prepayid) != prepayidToPayRequest.end()))
	{
		log("have no data on callback %s", prepayid.c_str());
		return;
	}
	auto nowData = prepayidToPayRequest[prepayid];
	auto info = PayPointConfig::getInstance()->getPayPointInfoById(nowData->pay_point_id);
	if (code == 0)
	{
		int lastlv = User::getInstance()->getVipLevel();
		auto lvdata = ConfigVipLevel::getInstance()->getVipLevel(lastlv);
		for (auto var:info.items)
		{
			switch (var.ItemID)
			{
				case 1:
					User::getInstance()->addCoins(var.ItemNum*lvdata.pay_reward);
					if (!User::getInstance()->getIsHaveBycoin())
					{
						User::getInstance()->setHaveBycoin();
						User::getInstance()->addDiamonds(100);
					}
					
					break;
				case 2:
					User::getInstance()->addDiamonds(var.ItemNum*lvdata.pay_reward);
					break;
				case 3:
					NobilityManager::getInstance()->addStepsDay(30);
					break;
			default:
				break;
			}
		}
		
		if (nowData->pay_point_id == 15)
		{
			User::getInstance()->setHaveFirstPay();
		}
		User::getInstance()->addChargeMoney(info.price / 100);
		
		
		payResult = 1;
		HttpMannger::getInstance()->HttpToPostRequestAfterPay(nowData->sessionid, nowData->pay_and_Event_version, nowData->pay_event_id, nowData->pay_point_id, nowData->channel_id, info.price,code, nowData->orderID.c_str());
	
		///VIP升级
		int nowlv = User::getInstance()->getVipLevel();
		if (nowlv>lastlv)
		{
			auto layer = GameManage::getInstance()->getGameLayer();
			if (layer)
			{
				layer->RefreShmyPlayerTurret();
			}
		}
	}
	else
	{
		payResult = 2;
		HttpMannger::getInstance()->HttpToPostRequestAfterPay(nowData->sessionid, nowData->pay_and_Event_version, nowData->pay_event_id, nowData->pay_point_id, nowData->channel_id, info.price,code, nowData->orderID.c_str());
	}
	prepayidToPayRequest.erase(nowData->wx_prepayid);
	delete nowData;
	
	nowData = nullptr;
}

PayPointInfo Pay::getInfoByPaypoint(int paypoint)
{
	return PayPointConfig::getInstance()->getPayPointInfoById(paypoint);
}

void Pay::update(float dt)
{	
	switch (payResult)
	{
	case 1:
	{
		auto layer = TwiceSureDialog::createDialog(ChineseWord("paySuccess").c_str(), nullptr);
		layer->setPosition(0, 0);
		Director::getInstance()->getRunningScene()->addChild(layer, 10);
		payResult = -1;
	}
		break;
	case 2:
	{
		auto layer = TwiceSureDialog::createDialog(ChineseWord("payFailed").c_str(), nullptr);
		layer->setPosition(0, 0);
		Director::getInstance()->getRunningScene()->addChild(layer, 10);
		payResult = -1;
	}
		break;

	default:
		break;
	}
}
