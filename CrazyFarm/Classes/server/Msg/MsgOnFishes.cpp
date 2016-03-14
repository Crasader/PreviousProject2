#include "MsgOnFishes.h"

void Msg_OnFishes::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	auto &events = doc["events"];
	for (unsigned int i = 0; i < events.Size();i++)
	{
		eventstrs.push_back(events[i].GetString());
	}
	
}