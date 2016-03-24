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
	//用户信息
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
	//鱼群
	rapidjson::Value& fishes = doc["fishes"];
	for (unsigned int i = 0; i < fishes.Size();i++)
	{
		auto &info = fishes[i];
		MsgFishesInfo fishInfo;
		fishInfo.seq_id = info["seq_id"].GetInt();
		fishInfo.seq_interval = info["seq_interval"].GetInt();
		fishInfo.seq_create_time = info["seq_create_time"].GetDouble();
		fishInfo.randomSTC = info["seq_create_time"].GetDouble();
		{
			auto &fishgroupinfo = info["fish_group_info"];
			MsgFishGourpInfo groupInfo;
			
			groupInfo.group_type = fishgroupinfo["group_type"].GetInt();
			groupInfo.sub_type = fishgroupinfo["sub_type"].GetInt();
			groupInfo.seq = fishgroupinfo["seq"].GetInt();
			groupInfo.seq_time = fishgroupinfo["seq_time"].GetInt();
			if (groupInfo.group_type == 0)
			{
				auto &fishitems = fishgroupinfo["fishes"];
				for (unsigned int k = 0; k < fishitems.Size(); k++)
				{
					MsgFishInfo fishitem;
					fishitem.fish_ids = fishitems[k]["fish_ids"].GetInt();
					fishitem.time = fishitems[k]["time"].GetDouble();
					fishitem.fish_route = fishitems[k]["fish_route"].GetInt();


					//
					fishitem.time -= groupInfo.seq_time*(groupInfo.seq - 1);
					//
					groupInfo.fishItems.push_back(fishitem);
				}
			}
			else
			{

			}
			fishInfo.fishGroupsItem = groupInfo;
		}
		_FishesInfos.push_back(fishInfo);
	}

	//初始时间戳
	initCreateTime = doc["create_time"].GetDouble();

}