#include "MsgOnInit.h"

void Msg_onInit::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	roomPos = doc["r_pos"].GetInt();
	rapidjson::Value& users = doc["users"];
	if (!users.IsArray())
	{
		log("ConfigExp The data is not json");
		return;
	}
	for (unsigned int i = 0; i < users.Size();i++)
	{
		auto &user = users[i];
		RoomPlayer* player = new RoomPlayer();
		player->setCoins(user["coins"].GetInt());
		player->setDiamonds(user["diamonds"].GetInt());
		player->setMaxTurretLevel(user["turrent_level"].GetInt());
		player->setLevel(user["vip_level"].GetInt());
		player->setChestLv(user["box_level"].GetInt());
		player->setUserName(user["username"].GetString());
		player->setRoomPosition(user["pos"].GetInt());
		roomplayers.push_back(player);
	}
}