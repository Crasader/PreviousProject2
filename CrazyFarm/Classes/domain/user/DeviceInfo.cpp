#include "domain/user/DeviceInfo.h"
#include "utill/JniFunUtill.h"
const char* DeviceInfo::getImei()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "493002407599521";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	return "493002407599521";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return JniFunUtill::getInstance()->getImei();

#endif
}
std::string DeviceInfo::getChannel_id()
{
	return "test";
}
const char*  DeviceInfo::getHd_type()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "win32";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return "mac";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return JniFunUtill::getInstance()->getHdType();
#endif
}

const char*  DeviceInfo::getHd_factory()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "win32";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return "mac";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return JniFunUtill::getInstance()->getHdFactory();
#endif
}

int DeviceInfo::getVesion()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return 1;
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	return 1;
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return 1;
#endif
}
