#include "DataBase.h"
#include <iostream>

DataBase::DataBase(const char *HOST, const char *USER, const char *PASS, const char *NAME, const int port)
{
	stat = 0;
	mysqlptr = NULL;
	result = NULL;

	mysql_init(&mysql);

	if (!DataBase::DB_connect(HOST, USER, PASS, NAME, port)) {
		cout << "database setup fail" << endl;
		exit(-1);
	}

	cout << "database setup" << endl;
}


DataBase::~DataBase()
{
	mysql_close(mysqlptr);

	cout << "databease shutdown" << endl;
}


// 테이블에 추가하는 함수
int DataBase::DB_insert(const char *table, const char *values)
{
	command = "";
	command = command + "insert into " + table + " values(" + values + ")";
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0;
	else return 1;
}


// 테이블 생성하는 함수
int DataBase::DB_create(const char *table, const char *values, const char *primary)
{
	command = "";
	command = command + "create table " + table + " (" + values + ", primary key(" + primary + "))";
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0;
	else return 1;
}


// 테이블 삭제하는 함수
int DataBase::DB_drop(const char *table)
{
	command = "";
	command = command + "drop table " + table;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0;
	else return 1;
}


// 행 삭제
int DataBase::DB_delete(const char *table, const char *where)
{
	command = "";
	command = command + "delete from " + table + " where " + where;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0;
	else return 1;
}


// 행을 변경하는 함수
int DataBase::DB_update(const char *table, const char *set, const char *where)
{
	command = "";
	command = command + "update " + table + " set " + set + " where " + where;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0;
	else return 1;
}


// 행 검색. 존나 복잡하니 곱게 짜자
int DataBase::DB_select(const char *column, const char *table, const char *where, const char *join, const char *order)
{
	row = NULL;
	command = "";
	command = command + "select " + column + " from " + table;
	if (strcmp(where, "")) command = command + " where " + where;
	if (strcmp(join, "")) command = command + " " + join;
	if (strcmp(order, "")) command = command + " order by " + order;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0;
	result = mysql_store_result(mysqlptr);
	return 1;
}

// db 연결하는 함수
bool DataBase::DB_connect(const char *HOST, const char *USER, const char *PASS, const char *NAME, int port)
{
	mysqlptr = mysql_real_connect(&mysql, HOST, USER, PASS, NAME, port, (char *)NULL, 0);
	if (mysqlptr == NULL) return FALSE;
	mysql_query(&mysql, "set names euckr");
	return TRUE;
}


// select로 검색한 다음 값이 있는가? 검색 후 무조건 1회는 사용해야함
bool DataBase::DB_hasNext()
{
	if ((row = mysql_fetch_row(result)) != NULL) return true;
	else return false;
}


// select로 얻은 로우 반환. 선행으로 꼭 hasNext 실행해야함
MYSQL_ROW DataBase::DB_getRow()
{
	return row;
}
