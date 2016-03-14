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

}