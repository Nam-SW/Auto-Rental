#include "DataBase.h"
#include <iostream>

DataBase::DataBase(const char *HOST, const char *USER, const char *PASS, const char *NAME, const int port)
{
	stat = 0;
	mysqlptr = NULL;
	result = NULL;

	mysql_init(&mysql); // DB 실행.

	if (!DataBase::DB_connect(HOST, USER, PASS, NAME, port)) { // 에러처리
		cout << "database setup fail" << endl;
		exit(-1);
	}

	cout << "database setup" << endl; // 셋업 이후 확인메세지
}


DataBase::~DataBase()
{
	mysql_close(mysqlptr);

	cout << "databease shutdown" << endl; // 셧다운후 확인메세지
}


// 테이블에 추가하는 함수
int DataBase::DB_insert(const char *table, const char *values)
{
	command = "";
	command = command + "insert into " + table + " values(" + values + ")";
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // 에러처리
	else return 1;
}


// 테이블 생성하는 함수
int DataBase::DB_create(const char *table, const char *values, const char *primary)
{
	command = "";
	command = command + "create table " + table + " (" + values + ", primary key(" + primary + "))";
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // 에러처리
	else return 1;
}


// 테이블 삭제하는 함수
int DataBase::DB_drop(const char *table)
{
	command = "";
	command = command + "drop table " + table;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // 에러처리
	else return 1;
}


// 행 삭제
int DataBase::DB_delete(const char *table, const char *where)
{
	command = "";
	command = command + "delete from " + table + " where " + where;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // 에러처리
	else return 1;
}


// 행을 변경하는 함수
int DataBase::DB_update(const char *table, const char *set, const char *where)
{
	command = "";
	command = command + "update " + table + " set " + set + " where " + where;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // 에러처리
	else return 1;
}


// 행 검색. 존나 복잡하니 곱게 짜자
int DataBase::DB_select(const char *column, const char *table, const char *where, const char *join, const char *order)
{
	row = NULL;
	command = "";
	command = command + "select " + column + " from " + table;
	if (strcmp(where, "")) command = command + " where " + where;  // 조건이 있을때는 조건문도
	if (strcmp(join, "")) command = command + " " + join; // 병합 처리가 있다면 병합처리문도
	if (strcmp(order, "")) command = command + " order by " + order; // 정렬까지 있다면 정렬문까지
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // 에러처리
	result = mysql_store_result(mysqlptr); // 검색값 저장
	return 1;
}

// db 연결하는 함수
bool DataBase::DB_connect(const char *HOST, const char *USER, const char *PASS, const char *NAME, int port)
{
	mysqlptr = mysql_real_connect(&mysql, HOST, USER, PASS, NAME, port, (char *)NULL, 0);
	if (mysqlptr == NULL) return FALSE; // 에러처리
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
