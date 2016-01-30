#ifndef GLOBALSCHEDULE_H_  
#define GLOBALSCHEDULE_H_  
//#include "domain/game/GameManage.h"
#include "cocos2d.h"  
USING_NS_CC;  
   

class GlobalSchedule: public Node {  
    public:
		static GlobalSchedule* getInstance();
		CREATE_FUNC(GlobalSchedule);
		float getGameTime();
		float getRoomTime();
		virtual bool init();
		virtual void update(float delta);

    private:  
        GlobalSchedule();  
        ~GlobalSchedule(); 
		void onEnter();
		
		void updataByMin(float dt); 
		
		void addGameTime(float dt);
		void addRoomTime(float dt);
		
		const char*   SCHEDULE_GAMETIME = "SCHEDULE_GAMETIME";
		const char*   SCHEDULE_ROOMTIME = "SCHEDULE_ROOMTIME";
       /* static GlobalSchedule* m_pSchedule;  */
};  
   
#endif /* GLOBALSCHEDULE_H_ */