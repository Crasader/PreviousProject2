#include "domain/ai/AI.h"
#include "utill/FunUtil.h"
PlayerWork AI::getUpdataTurrentWork(int AiDoCounts)
{
	PlayerWork work;
	if (AiDoCounts%190==0)
	{
		int num = getRand(Server_Seed) % 100;
		int per;
		int arr[2] = { 1, -1 };
		if (maxTurrentLevel >= 1 && maxTurrentLevel <= 10)
		{
			per = 10;
		}
		else if (maxTurrentLevel > 10 && maxTurrentLevel <= 30)
		{
			per = 20;
		}
		else if (maxTurrentLevel > 30 && maxTurrentLevel <= 100)
		{
			per = 30;
		}
		else if (maxTurrentLevel > 100 && maxTurrentLevel <= 300)
		{
			per = 30;
		}
		else if (maxTurrentLevel > 300 && maxTurrentLevel <= 500)
		{
			per = 40;
		}
		else if (maxTurrentLevel > 500 && maxTurrentLevel <= 1000)
		{
			per = 40;
		}

		if (num < per)
		{
			work._workeType = Robot_UpdateTurrent;
			work.diffTurretLv = arr[rand() % 1];
		}
		else
		{
			work._workeType = Invalid;
		}
	}
	else
	{
		work._workeType = Invalid;
	}
	return work;
}
