#include "DBManager.h"
#include "DBUtil.h"
#include "cocos2d.h"

USING_NS_CC;

//数据库名称
const string DB_NAME = "para.db";
const string GAME_PARA = "GamePara";
const string GAME_SCORE = "GameScore";
const string SKILL_INFO = "SKill_Info_%d";
DBManager::DBManager(void)
	: m_fVolumeBgm(0.5f)
	, m_fVolumeEffects(0.5f)
	, m_eGameDifficulty(GameDifficulty::GAMEDIFFICULTY_EASY)
{
	//设置数据库名称
	DBUtil::GetInstance()->SetDBFileName(DB_NAME);
}

DBManager::~DBManager(void)
{

}

DBManager* DBManager::GetInstance()
{
	static DBManager s_manager;
	return &s_manager;
}

//向GamePara表中添加初始化数据
bool DBManager::AddInitdataToGameParaTable()
{
	std::stringstream ss;
	ss << "INSERT INTO " << GAME_PARA << "(BgmVolume, EffectsVolume, Difficulty) "
		<< "VALUES(" << (int)(m_fVolumeBgm) << "," << (int)(m_fVolumeEffects) << "," << (int)m_eGameDifficulty << ");";
	string sql = ss.str();

	int result = 0;
	string errMsg;
	if (!DBUtil::GetInstance()->InsertData(sql, result, errMsg))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		log("添加初始化游戏参数失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
		return false;
	}
	
	return true;
}

//从数据库获取数据
bool DBManager::GetDataFromDB()
{
	int result = 0;
	string errMsg;
	string sql;

	//如果分数表不存在就创建
	if (!DBUtil::GetInstance()->IsTableExisted(GAME_SCORE))
	{
		//创建表
		sql = "CREATE TABLE " + GAME_SCORE + "(ID INTEGER PRIMARY KEY AUTOINCREMENT, Name text, Score INTEGER, Time text);";
		if (!DBUtil::GetInstance()->CreateTable(sql, GAME_SCORE, result, errMsg))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			log("创建表失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
			return false;
		}
	}

	//如果参数表不存在就创建
	if (!DBUtil::GetInstance()->IsTableExisted(GAME_PARA))
	{
		//创建表
		sql = "CREATE TABLE " + GAME_PARA + "(ID INTEGER PRIMARY KEY AUTOINCREMENT, tag text, BgmVolume INTEGER, EffectsVolume INTEGER, Difficulty INTEGER);";
		if (!DBUtil::GetInstance()->CreateTable(sql, GAME_PARA, result, errMsg))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			log("创建表失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
			return false;
		}

		//向GamePara表中添加初始化数据
		return AddInitdataToGameParaTable();
	}

	//如果表为空就添加一条数据
	sql = "SELECT BgmVolume, EffectsVolume, Difficulty FROM " + GAME_PARA;
	int count = 0;
	if (DBUtil::GetInstance()->GetDataCount(sql, count, result, errMsg) && count <= 0)
	{
		//向GamePara表中添加初始化数据
		return AddInitdataToGameParaTable();
	}
	
	//获取游戏参数
	sql = "SELECT BgmVolume, EffectsVolume, Difficulty FROM " + GAME_PARA;
	vector<vector<string>> vecPara;
	if (!DBUtil::GetInstance()->GetDataInfo(sql, vecPara, result, errMsg))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		log("创建表失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
		return false;
	}
	else
	{
		if (vecPara.size() > 0 && vecPara.begin()->size() == 3)
		{
			int value1 = atoi(vecPara.begin()->at(0).c_str());
			int value2 = atoi(vecPara.begin()->at(1).c_str());
			int value3 = atoi(vecPara.begin()->at(2).c_str());

			m_fVolumeBgm = (value1 == 0) ? 0.0f : (value1 );
			m_fVolumeEffects = (value2 == 0) ? 0.0f : (value2 );
			m_eGameDifficulty = GameDifficulty(value3);
			return true;
		}
		else
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			log("获取表[%s]的数据出现错误，表数据结构遭到破坏", GAME_PARA);
#endif
			return false;
		}
	}
}

//设置背景音乐音量
void DBManager::SetBgmVolume(float volume)
{
	m_fVolumeBgm = volume > 100 ? 100 : volume;
	m_fVolumeBgm = m_fVolumeBgm > 0.0f ? m_fVolumeBgm : 0.0f;

	//修改背景音乐音量
	std::stringstream ss;
	ss << "UPDATE " << GAME_PARA << " SET BgmVolume = " << (int)(m_fVolumeBgm) << ";";
	string sql = ss.str();
	int result = 0;
	string errMsg;
	if (!DBUtil::GetInstance()->UpdateData(sql, result, errMsg))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		log("创建表失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
	}
}

//设置音效音量
void DBManager::SetEffectsVolume(float volume)
{
	m_fVolumeEffects = volume > 100 ? 100 : volume;
	m_fVolumeEffects = m_fVolumeEffects > 0.0f ? m_fVolumeEffects : 0.0f;

	//修改音效音量
	std::stringstream ss;
	ss << "UPDATE " << GAME_PARA << " SET EffectsVolume = " << (int)(m_fVolumeEffects) << ";";
	string sql = ss.str();
	int result = 0;
	string errMsg;
	if (!DBUtil::GetInstance()->UpdateData(sql, result, errMsg))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		log("创建表失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
	}
}

//设置游戏难度
void DBManager::SetGameDifficulty(GameDifficulty difficulty)
{
	m_eGameDifficulty = difficulty;

	//修改游戏难度
	std::stringstream ss;
	ss << "UPDATE " << GAME_PARA << " SET Difficulty = " << (int)m_eGameDifficulty << ";";
	string sql = ss.str();
	int result = 0;
	string errMsg;
	if (!DBUtil::GetInstance()->UpdateData(sql, result, errMsg))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		log("创建表失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
	}
}

//添加游戏分数
void DBManager::AddScore(const GameScore& score)
{
	std::stringstream ss;
	ss << "INSERT INTO " << GAME_SCORE << "(Name, Score, Time) "
		<< "VALUES('" << score.name << "', " << score.score << ", '" << score.time << "');";
	string sql = ss.str();

	int result = 0;
	string errMsg;
	if (!DBUtil::GetInstance()->InsertData(sql, result, errMsg))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		log("添加分数记录失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
	}
}

//获取前十名分数
bool DBManager::GetFirst10Ranking(vector<GameScore>& ranking)
{
	//清空集合
	ranking.clear();

	vector<vector<string>> scores;
	int result = 0;
	string errMsg;

	//获取降序前10名
	string sql = "SELECT Name, Time, Score FROM " + GAME_SCORE + " ORDER BY Score DESC LIMIT 10";
	if (!DBUtil::GetInstance()->GetDataInfo(sql, scores, result, errMsg))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		log("获取分数前10名失败，错误码：%d，错误信息：%s", result, errMsg.c_str());
#endif
		return false;
	}

	vector<vector<string>>::const_iterator cit;
	for (cit=scores.begin(); cit!=scores.end(); ++cit)
	{
		const vector<string>& columes = *cit;
		GameScore score;
		score.name = columes.at(0);
		score.time = columes.at(1);
		score.score = Value(columes.at(2)).asInt();
		ranking.push_back(score);
	}

	return true;
}


void DBManager::SetSkillNum(int id,int num)
{
	auto SaveKey = String::createWithFormat(SKILL_INFO.c_str(), id);
	UserDefault::getInstance()->setIntegerForKey(SaveKey->getCString(), num);
}


int DBManager::GetSkillNum(int id)
{
	auto SaveKey = String::createWithFormat(SKILL_INFO.c_str(), id);
	return UserDefault::getInstance()->getIntegerForKey(SaveKey->getCString(), 10);
}