#ifndef __TURRET_H__
#define __TURRET_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

#define TURRETTYPE_1 0
#define TURRETTYPE_2 1
#define TURRETTYPE_3 2
#define TURRETTYPE_4 3
#define TURRETTYPE_5 4
#define TURRETTYPE_6 5
class Turret: public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(Turret);
	  void initWithType(int type); 
	  void upgradeTurret();
	  void degradeTurret();
	  void shoot();
	  Point getTampionPos(){ return emptySp->convertToWorldSpace(Point(0, 0)); }
private:
	  int turretType;
	  string getSrcByType(int type);
	  Sprite* emptySp;
	  

};
#endif