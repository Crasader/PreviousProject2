#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

/************************************************************************/
/* 数据库管理单例类                                                     */
/************************************************************************/

//游戏难度
typedef enum
{
	GAMEDIFFICULTY_EASY = 0,	//简单
	GAMEDIFFICULTY_NORMAL,		//一般
	GAMEDIFFICULTY_DIFFICULT	//困难
} GameDifficulty;

class DBManager
{
public:
	//游戏分数结构体
	typedef struct _tagGameScore
	{
		string	name;	//名字
		string	time;	//时间
		int		score;	//分数
	} GameScore;

public:
	static DBManager* GetInstance();
	~DBManager(void);

	//从数据库获取数据
	bool GetDataFromDB();
	
public:	//音量设置

	//获取背景音乐音量
	float GetBgmVolume() const { return m_fVolumeBgm; }

	//设置背景音乐音量
	void SetBgmVolume(float volume);

	//获取音效音量
	float GetEffectsVolume() const { return m_fVolumeEffects; }

	//设置音效音量
	void SetEffectsVolume(float volume);
	
public:	//难度设置

	//获取游戏难度
	GameDifficulty GetGameDifficulty() const { return m_eGameDifficulty; }

	//设置游戏难度
	void SetGameDifficulty(GameDifficulty difficulty);

public:	//游戏分数

	//添加游戏分数
	void AddScore(const GameScore& score);

	//获取前十名分数
	bool GetFirst10Ranking(vector<GameScore>& ranking);

public:	//道具个数

	//设置道具个数
	void SetSkillNum(int id,int num);

	//获取道具个数
	int GetSkillNum(int id);

private:
	DBManager(void);

	bool AddInitdataToGameParaTable();	//向GamePara表中添加初始化数据

private:
	float			m_fVolumeBgm;		//背景音乐音量
	float			m_fVolumeEffects;	//音效音量

	GameDifficulty	m_eGameDifficulty;	//游戏难度
};

