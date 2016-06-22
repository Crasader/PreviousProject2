#pragma once

#include "sqlite3.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

/************************************************************************/
/* ���ݿ��װ������                                                     */
/************************************************************************/

class DBUtil
{
public:
	static DBUtil* GetInstance();
	~DBUtil(void);

public:
	bool IsTableExisted(const string& name, int& result = m_result, string& errMsg = m_sErrMsg);					//���Ƿ����
	bool CreateTable(const string& sql, const string& name, int& result = m_result, string& errMsg = m_sErrMsg);	//������
	bool DropTable(const string& table_name, int& result = m_result, string& errMsg = m_sErrMsg);					//ɾ����

	bool InsertData(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);		//��������
	bool UpdateData(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);		//��������
	bool DeleteData(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);		//ɾ������

	bool GetDataCount(const string& sql, int& count, int& result = m_result, string& errMsg = m_sErrMsg);					//��ȡ��¼����
	bool GetDataInfo(const string& sql, vector<vector<string>>& data, int& result = m_result, string& errMsg = m_sErrMsg);	//��ȡ��¼

public:
	//�������ݿ��ļ���
	void SetDBFileName(const string& filename);

private:
	DBUtil(void);

	bool OpenDB(int& result = m_result, string& errMsg = m_sErrMsg);								//�����ݿ�
	void CloseDB();																					//�ر����ݿ�

	static int IsTableExisted(void* para, int n_column, char** column_value, char** column_name);	//�жϱ��Ƿ����
	static int GetDataCount(void* para, int n_column, char** column_value, char** column_name);		//��ȡ��¼����

	bool ExcuteSQL(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);			//ִ��SQL���

private:
	static string	m_sErrMsg;		//������Ϣ
	static int		m_result;		//������
	string			m_sDBFileName;	//���ݿ��ļ���
	string			m_sDBPath;		//���ݿ��ļ�·��
	sqlite3*		m_pDB;			//���ݿ�ָ��
};

