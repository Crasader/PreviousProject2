#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <string>

class GAMESTATE {
public:
	static GAMESTATE* getInstance();
private:
	GAMESTATE();
	void init();
	static GAMESTATE* _instance;
};
#endif
