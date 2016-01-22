#include "domain/user/DeviceInfo.h"

const char* DeviceInfo::getImei()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "493002407599521";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	return "493002407599521";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return "493002407599521";
#endif
}
std::string DeviceInfo::getChange_id()
{
	return "test";
}
int DeviceInfo::getHd_type()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return 1;
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return 1;
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return 1;
#endif
}

int DeviceInfo::getHd_factory()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return 1;
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return 1;
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return 1;
#endif
}