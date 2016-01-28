#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "domain/pay/Pay.h"
using namespace cocos2d;
USING_NS_CC_EXT;


struct Good
{
	int RMB;
	int count;
	Good(int r, int c){ RMB = r, count = c; }
};


class PayCell : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PayCell);
	  void setValue(int goodId);
	  void setDiamondValue(int goodId);
	  void setVipValue();
	  void IsBeToued();
	  void onHttpRequestCompletedAfterPay(HttpClient *sender, HttpResponse *response)
	  {
		  if (!response)
		  {
			  return;
		  }
		  if (!response->isSucceed())
		  {
			  log("error buffer: %s", response->getErrorBuffer());
			  return;
		  }
		  long statusCode = response->getResponseCode();
		  char statusString[64] = {};
		  // dump data
		  std::vector<char> *buffer = response->getResponseData();
		  auto temp = std::string(buffer->begin(), buffer->end());
		  rapidjson::Document doc;
		  doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	  };
private:
	CC_SYNTHESIZE(int, m_nGoodId, goodID);
	int m_PayType;
	Sprite* paySprite;
	Sprite* propNum;
	Sprite* giftNum;
	Sprite* hotTxt;
};
