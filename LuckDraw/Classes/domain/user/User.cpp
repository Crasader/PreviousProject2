#include "domain/user/User.h"
#include "server/HttpMannger.h"

User* User::_instance = NULL;

User::User(){

}

User* User::getInstance(){
	if(_instance == NULL){
		_instance = new User();
	}
	return _instance;
}