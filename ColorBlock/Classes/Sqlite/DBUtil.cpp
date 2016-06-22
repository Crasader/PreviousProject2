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

//设置数据库文件名
void DBUtil::SetDBFileName(const string& filename)
{
	m_sDBFileName = filename;
	m_sDBPath = FileUtils::getInstance()->getWritablePath() + m_sDBFileName;
}

//打开数据库，如果该数据库不存在，就创建一个数据库
bool DBUtil::OpenDB(int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	result = sqlite3_open(m_sDBPath.c_str(), &m_pDB);
	if (result != SQLITE_OK)
	{
		errMsg = "打开数据库失败";
		return false;
	}
	return true;
}

//判断表是否存在
//para:传进回调函数的参数,n_column:字段个数
//column_value:char*数组(保存每一个字段的值),column_name:字段名称
int DBUtil::IsTableExisted(void* para, int n_column, char** column_value, char** column_name)
{
	bool* existed = (bool*)para;
	*existed = (**column_value) != '0';	//字段的值为空时表示不存在数据
	return 0;
}

//表是否存在
bool DBUtil::IsTableExisted(const string& name, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//打开数据库
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	bool existed = true;
	string sql = "SELECT count(type) FROM sqlite_master WHERE type = 'table' and name = '" + name + "'";
	result = sqlite3_exec(m_pDB, sql.c_str(), DBUtil::IsTableExisted, &existed, NULL);

	//关闭数据库
	CloseDB();

	return existed;
}

//创建表
bool DBUtil::CreateTable(const string& sql, const string& name, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//判断表是否存在
	if (IsTableExisted(name, result, errMsg))
	{
		return true;
	}

	//执行SQL语句
	return ExcuteSQL(sql.c_str(), result, errMsg);
}

//删除表
bool DBUtil::DropTable(const string& table_name, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//判断表是否存在
	if (!IsTableExisted(table_name, result, errMsg))
	{
		return true;
	}

	//执行SQL语句
	string sql = "DROP TABLE " + table_name;
	return ExcuteSQL(sql.c_str(), result, errMsg);
}

//关闭数据库
void DBUtil::CloseDB()
{
	sqlite3_close(m_pDB);
}

//插入数据
bool DBUtil::InsertData(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	return ExcuteSQL(sql, result, errMsg);
}

//删除数据
bool DBUtil::DeleteData(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	return ExcuteSQL(sql, result, errMsg);
}

//更新数据
bool DBUtil::UpdateData(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	return ExcuteSQL(sql, result, errMsg);
}

//执行SQL语句
bool DBUtil::ExcuteSQL(const string& sql, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//打开数据库
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	char* pErrMsg = NULL;
	result = sqlite3_exec(m_pDB, sql.c_str(), NULL, NULL, &pErrMsg);
	errMsg = (pErrMsg == NULL ? "" : pErrMsg);

	//关闭数据库
	CloseDB();

	return (result == SQLITE_OK);
}

//获取记录个数 - n_column:字段个数
int DBUtil::GetDataCount(void* para, int n_column, char** column_value, char** column_name)
{
	int* count = (int*)para;
	*count = n_column;
	return 0;
}

//获取记录个数
bool DBUtil::GetDataCount(const string& sql, int& count, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//打开数据库
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	char* pErrMsg = NULL;
	char** pDBResult = NULL;	//查询结果
	int nColumn = 0;

	result = sqlite3_get_table(m_pDB, sql.c_str(), &pDBResult, &count, &nColumn, &pErrMsg);
	errMsg = (pErrMsg == NULL ? "" : pErrMsg);
	bool ok = (result == SQLITE_OK);

	//释放查询结果(无论查询是否成功)
	sqlite3_free_table(pDBResult);

	//关闭数据库
	CloseDB();

	return ok;
}

//获取记录
bool DBUtil::GetDataInfo(const string& sql, vector<vector<string>>& data, int& result /* = m_result */, string& errMsg /* = m_sErrMsg */)
{
	//打开数据库
	if (!OpenDB(result, errMsg))
	{
		return false;
	}

	char* pErrMsg = NULL;
	char** pDBResult = NULL;	//查询结果,前面是字段名称，后面才是字段的值
	int nRow = 0;
	int nColumn = 0;

	result = sqlite3_get_table(m_pDB, sql.c_str(), &pDBResult, &nRow, &nColumn, &pErrMsg);
	errMsg = (pErrMsg == NULL ? "" : pErrMsg);
	bool ok = (result == SQLITE_OK);
	if (ok)
	{
		int index = nColumn;	//pDBResult前面是列名

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

	//释放查询结果(无论查询是否成功)
	sqlite3_free_table(pDBResult);

	//关闭数据库
	CloseDB();

	return ok;
}