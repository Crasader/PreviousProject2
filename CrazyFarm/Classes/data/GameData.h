#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"
#include "domain/magnate/MagnateManager.h"
#include "config/ConfigTurrent.h"
#include "domain/mermaid/MermaidTask.h"
using namespace cocos2d;

#define Server_Seed GameData::getInstance()->getRandomSeed()


struct CatchFishIdByMultiple
{
	std::vector<int> fishids;
	
	int Multiple;
};
class GameData {
public:
	static GameData* getInstance();
	Turrent getTurrentData();
	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();
private:
	GameData();
	void init();
	static GameData* _instance;
	CC_SYNTHESIZE(int, nRoomId, RoomID);	
	CC_SYNTHESIZE(int, nNowLevel, nowLevel);

	CC_SYNTHESIZE(bool, isOnMaridTask, IsOnMaridTask);
	CC_SYNTHESIZE(bool, bIsOnBankrupt, isOnBankrupt);
	CC_SYNTHESIZE(bool, bisPlayerOneGame, isPlayerOneGame);//�Ƿ���й�һ����Ϸ

	CC_SYNTHESIZE(bool, bIsOnGameScene, isOnGameScene);


	CC_SYNTHESIZE(int, nChairNo, chairNo);

	//�Ƿ�ֱ��ʹ�ü���
	CC_SYNTHESIZE(bool, m_isDirectUseSkill, isDirectUseSkill);


	//��Ϸ״̬
	CC_SYNTHESIZE(bool, m_isOnGroupComing, isOnGroupComing);
	//�Ƿ���ع���Ϸ�������
	CC_SYNTHESIZE(bool, m_isLoadMsgOnGame, isLoadMsgOnGame);




	//���ĵ������������//0:��ʼ 1��showTurretCell 2: MenuItemUpgrade;
	CC_SYNTHESIZE(int, _TouchLockTurretType, TouchLockTurretType); 

	

	//��Ϸ��10S��ұ仯�;���仯
	CC_SYNTHESIZE(int, _gainCoin, gainCoin);
	CC_SYNTHESIZE(int, _costCoin, costCoin);
	CC_SYNTHESIZE(int, _changeExp, changeExp);

	std::vector<CatchFishIdByMultiple> _catchFishes;
	std::vector<int> _goldFishIds;

	CC_SYNTHESIZE(int, _shootCounts, shootCounts);
public:
	std::vector<CatchFishIdByMultiple>& getCatchFishes(){ return _catchFishes; };
	std::vector<int>& getCatchGoldFishes(){ return _goldFishIds; };
	void addCatchFishes(int fishid, int level);
	void addGoldCatchFishes(int fishid);
private:
	//ȫ���������
	int _RandomSeed;
public:
	
	unsigned int getRandomSeed();
	void setRandomSeed(unsigned int var);

	CC_SYNTHESIZE(Vec2, _tempBullerPos,	TempBullerPos);
};

#endif
