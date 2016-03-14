#include "MsgOnAdd.h"

void Msg_onAdd::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	username = doc["username"].GetString();
	coins = doc["coins"].GetUint();
	diamonds = doc["diamonds"].GetUint();
	turrent_level = doc["turrent_level"].GetInt();
	vip_level = doc["vip_level"].GetInt();
	box_level = doc["box_level"].GetInt();
	roomPos = doc["pos"].GetInt();

}