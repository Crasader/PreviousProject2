#include "DBUtil.h"
#include "cocos2d.h"

USING_NS_CC;

string DBUtil::m_sErrMsg = "";
int DBUtil::m_result = 0;

DBUtil::DBUtil(void)
	: m_pDB(NULL)
	, m_sDBFileName("db.db")
{
	m_sDBPath = FileUtils::getInstance()->getWritablePath() + m_sDBFileName;
}

DBUtil::~DBUtil(void)
{

}

DBUtil* DBUtil::GetInstance()
{
	static DBUtil s_manager;
	return &s_manager;
}

//�������ݿ��ļ���
void DBUtil::SetDBFileName(const string& filename)
{
	m_sDBFileName = filename;
	m_sDBPath = FileUtils::getInstance()->getWritablePath() + m_sDBFileName;
}

//�����ݿ⣬��������ݿⲻ���ڣ��ʹ���һ�����ݿ�
bool DBUtil::OpenDB(int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	result = sqlite3_open(m_sDBPath.c_str(), &m_pDB);
	if (result != SQLITE_OK)
	{
		errMsg = "�����ݿ�ʧ��";
		return false;
	}
	return true;
}

//�жϱ��Ƿ����
//para:�����ص������Ĳ���,n_column:�ֶθ���
//column_value:char*����(����ÿһ���ֶε�ֵ),column_name:�ֶ�����
int DBUtil::IsTableExisted(void* para, int n_column, char** column_value, char** column_name)
{
	bool* existed = (bool*)para;
	*existed = (**column_value) != '0';	//�ֶε�ֵΪ��ʱ��ʾ����������
	return 0;
}

//���Ƿ����
bool DBUtil::IsTableExisted(const string& name, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//�����ݿ�
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	bool existed = true;
	string sql = "SELECT count(type) FROM sqlite_master WHERE type = 'table' and name = '" + name + "'";
	result = sqlite3_exec(m_pDB, sql.c_str(), DBUtil::IsTableExisted, &existed, NULL);

	//�ر����ݿ�
	CloseDB();

	return existed;
}

//������
bool DBUtil::CreateTable(const string& sql, const string& name, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//�жϱ��Ƿ����
	if (IsTableExisted(name, result, errMsg))
	{
		return true;
	}

	//ִ��SQL���
	return ExcuteSQL(sql.c_str(), result, errMsg);
}

//ɾ����
bool DBUtil::DropTable(const string& table_name, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//�жϱ��Ƿ����
	if (!IsTableExisted(table_name, result, errMsg))
	{
		return true;
	}

	//ִ��SQL���
	string sql = "DROP TABLE " + table_name;
	return ExcuteSQL(sql.c_str(), result, errMsg);
}

//�ر����ݿ�
void DBUtil::CloseDB()
{
	sqlite3_close(m_pDB);
}

//��������
bool DBUtil::InsertData(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	return ExcuteSQL(sql, result, errMsg);
}

//ɾ������
bool DBUtil::DeleteData(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	return ExcuteSQL(sql, result, errMsg);
}

//��������
bool DBUtil::UpdateData(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	return ExcuteSQL(sql, result, errMsg);
}

//ִ��SQL���
bool DBUtil::ExcuteSQL(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//�����ݿ�
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	char* pErrMsg = NULL;
	result = sqlite3_exec(m_pDB, sql.c_str(), NULL, NULL, &pErrMsg);
	errMsg = (pErrMsg == NULL ? "" : pErrMsg);

	//�ر����ݿ�
	CloseDB();

	return (result == SQLITE_OK);
}

//��ȡ��¼���� - n_column:�ֶθ���
int DBUtil::GetDataCount(void* para, int n_column, char** column_value, char** column_name)
{
	int* count = (int*)para;
	*count = n_column;
	return 0;
}

//��ȡ��¼����
bool DBUtil::GetDataCount(const string& sql, int& count, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//�����ݿ�
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	char* pErrMsg = NULL;
	char** pDBResult = NULL;	//��ѯ���
	int nColumn = 0;

	result = sqlite3_get_table(m_pDB, sql.c_str(), &pDBResult, &count, &nColumn, &pErrMsg);
	errMsg = (pErrMsg == NULL ? "" : pErrMsg);
	bool ok = (result == SQLITE_OK);

	//�ͷŲ�ѯ���(���۲�ѯ�Ƿ�ɹ�)
	sqlite3_free_table(pDBResult);

	//�ر����ݿ�
	CloseDB();

	return ok;
}

//��ȡ��¼
bool DBUtil::GetDataInfo(const string& sql, vector<vector<string>>& data, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//�����ݿ�
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	char* pErrMsg = NULL;
	char** pDBResult = NULL;	//��ѯ���,ǰ�����ֶ����ƣ���������ֶε�ֵ
	int nRow = 0;
	int nColumn = 0;

	result = sqlite3_get_table(m_pDB, sql.c_str(), &pDBResult, &nRow, &nColumn, &pErrMsg);
	errMsg = (pErrMsg == NULL ? "" : pErrMsg);
	bool ok = (result == SQLITE_OK);
	if (ok)
	{
		int index = nColumn;	//pDBResultǰ��������

		for (int i=0; i<nRow; i++)
		{
			vector<string> vecRow;
			for (int j=0; j<nColumn; j++)
			{
				vecRow.push_back(pDBResult[index++]);
			}
			data.push_back(vecRow);
		}
	}

	//�ͷŲ�ѯ���(���۲�ѯ�Ƿ�ɹ�)
	sqlite3_free_table(pDBResult);

	//�ر����ݿ�
	CloseDB();

	return ok;
}