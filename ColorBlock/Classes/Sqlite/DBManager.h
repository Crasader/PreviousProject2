#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

/************************************************************************/
/* ���ݿ��������                                                     */
/************************************************************************/

//��Ϸ�Ѷ�
typedef enum
{
	GAMEDIFFICULTY_EASY = 0,	//��
	GAMEDIFFICULTY_NORMAL,		//һ��
	GAMEDIFFICULTY_DIFFICULT	//����
} GameDifficulty;

class DBManager
{
public:
	//��Ϸ�����ṹ��
	typedef struct _tagGameScore
	{
		string	name;	//����
		string	time;	//ʱ��
		int		score;	//����
	} GameScore;

public:
	static DBManager* GetInstance();
	~DBManager(void);

	//�����ݿ��ȡ����
	bool GetDataFromDB();
	
public:	//��������

	//��ȡ������������
	float GetBgmVolume() const { return m_fVolumeBgm; }

	//���ñ�����������
	void SetBgmVolume(float volume);

	//��ȡ��Ч����
	float GetEffectsVolume() const { return m_fVolumeEffects; }

	//������Ч����
	void SetEffectsVolume(float volume);
	
public:	//�Ѷ�����

	//��ȡ��Ϸ�Ѷ�
	GameDifficulty GetGameDifficulty() const { return m_eGameDifficulty; }

	//������Ϸ�Ѷ�
	void SetGameDifficulty(GameDifficulty difficulty);

public:	//��Ϸ����

	//�����Ϸ����
	void AddScore(const GameScore& score);

	//��ȡǰʮ������
	bool GetFirst10Ranking(vector<GameScore>& ranking);

public:	//���߸���

	//���õ��߸���
	void SetSkillNum(int id,int num);

	//��ȡ���߸���
	int GetSkillNum(int id);

private:
	DBManager(void);

	bool AddInitdataToGameParaTable();	//��GamePara������ӳ�ʼ������

private:
	float			m_fVolumeBgm;		//������������
	float			m_fVolumeEffects;	//��Ч����

	GameDifficulty	m_eGameDifficulty;	//��Ϸ�Ѷ�
};

