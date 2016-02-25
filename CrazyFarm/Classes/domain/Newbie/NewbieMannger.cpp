#include "NewbieMannger.h"


NewbieMannger* NewbieMannger::_instance = NULL;

NewbieMannger::NewbieMannger(){

}


NewbieMannger* NewbieMannger::getInstance(){
	if (_instance == NULL){
		_instance = new NewbieMannger();
	}
	return _instance;
}