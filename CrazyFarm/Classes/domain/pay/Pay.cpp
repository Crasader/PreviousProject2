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
#include "PayingDialog.h"
#include "server/Server.h"
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

	if (!JniFunUtill::getInstance()->isWXAppInstalled())
	{
		auto dio = TwiceSureDialog::createDialog(ChineseWord("nowxpaytip").c_str());
		dio->setPosition(0, 0);
		Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(dio, 40);
		return;
	}
	if (m_state!=UnDoing)
	{
		return;
	}
	PayingDialog::ShowPayDialog();
	m_state = OrderBooking;
	auto sessioned = User::getInstance()->getSessionid();
	if (sessioned=="")
	{
		HttpMannger::getInstance()->HttpToPostRequestLogInInfo(DeviceInfo::getChannel_id(), User::getInstance()->getUserName(), DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
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
		m_state = UnDoing;
		ToolTipMannger::ShowPayTimeoutTip();
		PayingDialog::RemovePayDialog();
		return; 
	}
	int payeventVersion = PayEventPointConfig::getInstance()->getPayeventVersion();
	int payPointVersion = PayPointConfig::getInstance()->getVersion();
	auto payPointInfo = PayPointConfig::getInstance()->getPayPointInfoById(paypoint);
	auto channel_id = DeviceInfo::getChannel_id();
	auto sessionid = User::getInstance()->getSessionid();
	int price = payPointInfo.price;


	EventListenerCustom* _listener2 = EventListenerCustom::create("Over_Book_Order", [=](EventCustom* event){

		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("Over_Book_Order");
		OverBookValue*value = static_cast<OverBookValue*>(event->getUserData());
		if (value->_errorcode == 0)
		{
			payRequest*request = new payRequest();
			request->channel_id = channel_id;
			request->orderID = value->orderID;
			request->pay_and_Event_version = payPointVersion * 1000 + payeventVersion;
			request->pay_event_id = eventPoint;
			request->pay_point_id = paypoint;
			request->sessionid = sessionid;
			request->third_payType = 1;
			request->wx_nonceStr = value->wx_nonceStr;
			request->wx_prepayid = value->wx_prepayid;
			request->wx_sign = value->wx_sign;
			request->wx_timestamp = value->wx_timestamp;
			pay(request);
		}
		else if (value->_errorcode==404)
		{
			ToolTipMannger::ShowPayTimeoutTip();
			setPayState(UnDoing);
			PayingDialog::RemovePayDialog();
		}
		else
		{
			ToolTipMannger::showDioag(value->_errormsg);
			setPayState(UnDoing);
			PayingDialog::RemovePayDialog();
		}

		

	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);

	HttpMannger::getInstance()->HttpToPostRequestBeforePay(1,sessionid, payPointVersion * 1000 + payeventVersion, eventPoint, paypoint, channel_id,payPointInfo.pay_point_desc,price);
}

void Pay::pay(payRequest*data)
{
	prepayid_To_orderid[data->wx_prepayid] = data->orderID;
	log("pushback data wx_prepayid = %s", data->wx_prepayid.c_str());
	nowPayOrderId = data->orderID;
	payResult = -1;
	m_state = WxPaying;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::vector<RewardValue> value;
	for (auto var: PayPointConfig::getInstance()->getPayPointInfoById(data->pay_point_id).items)
	{
		value.push_back(RewardValue(var.ItemID, var.ItemNum));
	}
	payCallBack(0, "success", value,PayPointConfig::getInstance()->getPayPointInfoById(data->pay_point_id).price,data->wx_prepayid);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	payCallBack(0, "success", value,PayPointConfig::getInstance()->getPayPointInfoById(data->pay_point_id).price,data->wx_prepayid);
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
	CC_SAFE_DELETE(data);
}
std::string Pay::getOrderIdByprepayid(std::string prepayid)
{
	if (!(prepayid_To_orderid.find(prepayid) != prepayid_To_orderid.end()))
	{

		return "";
	}
	else
	{
		return prepayid_To_orderid[prepayid];
	}
}

std::string Pay::getPrepayIdByOrderid(std::string orderid)
{
	for (auto it = prepayid_To_orderid.begin(); it != prepayid_To_orderid.end(); ++it)
	{
		if (orderid == it->second)
		{
			return it->first;
		}
	}
	return "";
}
void Pay::jniCallBack(int code, const char*msg, const char*wx_prepayid)
{
	if (code == 0)
	{
		if (!(prepayid_To_orderid.find(wx_prepayid) != prepayid_To_orderid.end()))
		{
			std::vector<RewardValue> rewards;
			payCallBack(code, msg, rewards, 0, wx_prepayid);
			return;
		}
		wx_cb_prepayid = wx_prepayid;
		payResult = 3;
		m_state = DemandEntrying;
	}
	else
	{
		std::vector<RewardValue> rewards;
			payCallBack(code, msg, rewards, 0, wx_prepayid);
	}
}
void Pay::DemandEntry(int reqNum, std::string prePayid)
{

	EventListenerCustom* _listener2 = EventListenerCustom::create("DemandEntry", [=](EventCustom* event){
		
			log("demandentry cb");
			DemandOrderValue*value = static_cast<DemandOrderValue*>(event->getUserData());
			if (value->_errorcode == 0)
			{
				if (value->realprice > 0)
				{
					WaitCircle::RemovePayWaitCircle(prePayid);
					payCallBack(value->_errorcode, value->_errormsg.c_str(), value->rewards, value->realprice, prePayid);
				}
			}
			else
			{
				if (reqNum > 2)
				{
					WaitCircle::RemovePayWaitCircle(prePayid);
					payCallBack(value->_errorcode, value->_errormsg.c_str(), value->rewards, value->realprice, prePayid);
				}
				else
				{
					WaitCircle::sendRequestWaitCirCle(prePayid);
				}
			}
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("DemandEntry");
		}
		

		

	);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);

	if (GameManage::getInstance()->getGuiLayer())
	{
		log("demand in game");
		Server::getInstance()->sendCheckPayresult(getOrderIdByprepayid(prePayid),1);
	}
	else
	{
		log("demand not in game");
		HttpMannger::getInstance()->HttpToPostRequestDemandEntry(prePayid, reqNum);
	}
	
}
void Pay::payCallBack(int code, const char* msg, std::vector<RewardValue> rewards, int releprice,std::string prepayid)
{
	
	PayingDialog::RemovePayDialog();
	m_state = UnDoing;
	prepayid_To_orderid.erase(prepayid);
	if (code == 0)
	{
		int lastlv = User::getInstance()->getVipLevel();
		auto lvdata = ConfigVipLevel::getInstance()->getVipLevel(lastlv);
		for (auto var : rewards)
		{
			switch (var._itemid)
			{
				case 1001:
					User::getInstance()->addCoins(var._num*lvdata.pay_reward);
					if (!User::getInstance()->getIsHaveBycoin())
					{
						User::getInstance()->setHaveBycoin();
						User::getInstance()->addDiamonds(100);
					}
					
					break;
				case 1002:
					User::getInstance()->addDiamonds(var._num*lvdata.pay_reward);
					break;
				case 1000:
					User::getInstance()->setNobilityDay(User::getInstance()->getNobilityDay() + var._num);
					break;
			default:
				break;
			}
		}

		User::getInstance()->addChargeMoney(releprice);
		
		
		payResult = 1;
	
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
		
	}
}
void Pay::CancelTheOrder()
{
	if (nowPayOrderId!=""&&m_state!=DemandEntrying)
	{
		std::vector<RewardValue> rewards;
		payCallBack(1, "failed", rewards, 0, getPrepayIdByOrderid(nowPayOrderId));
		/*HttpMannger::getInstance()->HttpToPostRequestCancelOrder(nowPayOrderId);*/
	}
	
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
		Director::getInstance()->getRunningScene()->addChild(layer, 30);
		payResult = -1;
	}
		break;
	case 2:
	{
		auto layer = TwiceSureDialog::createDialog(ChineseWord("payFailed").c_str(), nullptr);
		layer->setPosition(0, 0);
		Director::getInstance()->getRunningScene()->addChild(layer, 30);
		payResult = -1;
	}
		break;
	case 3:
	{
		auto circle = WaitCircle::ShowPayWaitCircle();
		circle->setMyPrepayid(wx_cb_prepayid);
		circle->setName(wx_cb_prepayid);
	
		payResult = -1;
	}
	default:
		break;
	}
}
