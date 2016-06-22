#pragma once

#include "sqlite3.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

/************************************************************************/
/* 数据库封装单例类                                                     */
/************************************************************************/

class DBUtil
{
public:
	static DBUtil* GetInstance();
	~DBUtil(void);

public:
	bool IsTableExisted(const string& name, int& result = m_result, string& errMsg = m_sErrMsg);					//表是否存在
	bool CreateTable(const string& sql, const string& name, int& result = m_result, string& errMsg = m_sErrMsg);	//创建表
	bool DropTable(const string& table_name, int& result = m_result, string& errMsg = m_sErrMsg);					//删除表

	bool InsertData(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);		//插入数据
	bool UpdateData(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);		//更新数据
	bool DeleteData(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);		//删除数据

	bool GetDataCount(const string& sql, int& count, int& result = m_result, string& errMsg = m_sErrMsg);					//获取记录个数
	bool GetDataInfo(const string& sql, vector<vector<string>>& data, int& result = m_result, string& errMsg = m_sErrMsg);	//获取记录

public:
	//设置数据库文件名
	void SetDBFileName(const string& filename);

private:
	DBUtil(void);

	bool OpenDB(int& result = m_result, string& errMsg = m_sErrMsg);								//打开数据库
	void CloseDB();																					//关闭数据库

	static int IsTableExisted(void* para, int n_column, char** column_value, char** column_name);	//判断表是否存在
	static int GetDataCount(void* para, int n_column, char** column_value, char** column_name);		//获取记录个数

	bool ExcuteSQL(const string& sql, int& result = m_result, string& errMsg = m_sErrMsg);			//执行SQL语句

private:
	static string	m_sErrMsg;		//错误信息
	static int		m_result;		//错误码
	string			m_sDBFileName;	//数据库文件名
	string			m_sDBPath;		//数据库文件路径
	sqlite3*		m_pDB;			//数据库指针
};

