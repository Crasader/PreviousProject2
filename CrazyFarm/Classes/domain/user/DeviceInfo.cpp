#include "domain/user/DeviceInfo.h"

DeviceInfo* DeviceInfo::_instance = NULL;

DeviceInfo::DeviceInfo(){
	this->init();
}

void DeviceInfo::init(){
    // TODO : first use init user name and id
}

DeviceInfo* DeviceInfo::getInstance(){
	if(_instance == NULL){
		_instance = new DeviceInfo();
	}
	return _instance;
}
long DeviceInfo::getImei()
{
	return 1;	
}
std::string DeviceInfo::getChange_id()
{
	return "";
}
int DeviceInfo::getHd_type()
{
	return 1;
}

int DeviceInfo::getHd_factory()
{
	return 1;
}