
//      DataBase.h, DataBase.cpp 파일은 클라이언트 프로그램에도 정의되어 있으므로
//      매니지먼트 프로그램에선 주석으로 설명을 하지 않겠습니다.

#pragma once
#include <string>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")

#define DB_HOST "127.0.0.1" // 서버컴에 따라 바껴야함
#define DB_USER "root"
#define DB_PASS "nsw0311"
#define DB_NAME "test"
#define DB_PORT 3306

using namespace std;

class DataBase
{
public:
	DataBase(const char *HOST, const char *USER, const char *PASS, const char *NAME, const int port);
	~DataBase();

private:
	MYSQL mysql;
	MYSQL *mysqlptr;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int stat;
	string command;

public:
	// 행 추가
	int DB_insert(const char *table, const char *values);
	// 테이블 생성하는 함수
	int DB_create(const char *table, const char *values, const char *primary);
	// 테이블 삭제하는 함수
	int DB_drop(const char *table);
	// 행 삭제
	int DB_delete(const char *table, const char *where);
	// 행 변경
	int DB_update(const char *table, const char *set, const char *where);
	// 행 검색. 존나 복잡하니 곱게 짜자
	int DB_select(const char *column, const char *table, const char *where = "", const char *join = "", const char *order = "");
	// select로 검색한 다음 값이 있는가? 검색 후 무조건 1회는 사용해야함
	bool DB_hasNext();
	// select로 얻은 로우 반환. 선행으로 꼭 hasNext 실행해야함
	MYSQL_ROW DB_getRow();

private:
	// db 연결하는 함수
	bool DB_connect(const char *HOST, const char *USER, const char *PASS, const char *NAME, int port);
};

