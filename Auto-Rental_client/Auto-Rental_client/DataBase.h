#pragma once
#include <string>
#include <mysql.h> // mysql ���̺귯��
#pragma comment(lib, "libmySQL.lib")

#define DB_HOST "127.0.0.1" // DB ���� �ּ�
#define DB_USER "root" // DB ������
#define DB_PASS "nsw0311" // DB ��й�ȣ
#define DB_NAME "test" // DB ��Ű�� ��
#define DB_PORT 3306 // DB ��Ʈ��ȣ

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
	// �� �߰�
	int DB_insert(const char *table, const char *values);
	// ���̺� �����ϴ� �Լ�
	int DB_create(const char *table, const char *values, const char *primary);
	// ���̺� �����ϴ� �Լ�
	int DB_drop(const char *table);
	// �� ����
	int DB_delete(const char *table, const char *where);
	// �� ����
	int DB_update(const char *table, const char *set, const char *where);
	// �� �˻�. ���� �����ϴ� ���� ¥��
	int DB_select(const char *column, const char *table, const char *where = "", const char *join = "", const char *order = "");
	// select�� �˻��� ���� ���� �ִ°�? �˻� �� ������ 1ȸ�� ����ؾ���
	bool DB_hasNext();
	// select�� ���� �ο� ��ȯ. �������� �� hasNext �����ؾ���
	MYSQL_ROW DB_getRow();

private:
	// db �����ϴ� �Լ�
	bool DB_connect(const char *HOST, const char *USER, const char *PASS, const char *NAME, int port);
};

