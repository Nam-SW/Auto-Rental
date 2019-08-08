#include "DataBase.h"
#include <iostream>

DataBase::DataBase(const char *HOST, const char *USER, const char *PASS, const char *NAME, const int port)
{
	stat = 0;
	mysqlptr = NULL;
	result = NULL;

	mysql_init(&mysql); // DB ����.

	if (!DataBase::DB_connect(HOST, USER, PASS, NAME, port)) { // ����ó��
		cout << "database setup fail" << endl;
		exit(-1);
	}

	cout << "database setup" << endl; // �¾� ���� Ȯ�θ޼���
}


DataBase::~DataBase()
{
	mysql_close(mysqlptr);

	cout << "databease shutdown" << endl; // �˴ٿ��� Ȯ�θ޼���
}


// ���̺� �߰��ϴ� �Լ�
int DataBase::DB_insert(const char *table, const char *values)
{
	command = "";
	command = command + "insert into " + table + " values(" + values + ")";
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // ����ó��
	else return 1;
}


// ���̺� �����ϴ� �Լ�
int DataBase::DB_create(const char *table, const char *values, const char *primary)
{
	command = "";
	command = command + "create table " + table + " (" + values + ", primary key(" + primary + "))";
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // ����ó��
	else return 1;
}


// ���̺� �����ϴ� �Լ�
int DataBase::DB_drop(const char *table)
{
	command = "";
	command = command + "drop table " + table;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // ����ó��
	else return 1;
}


// �� ����
int DataBase::DB_delete(const char *table, const char *where)
{
	command = "";
	command = command + "delete from " + table + " where " + where;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // ����ó��
	else return 1;
}


// ���� �����ϴ� �Լ�
int DataBase::DB_update(const char *table, const char *set, const char *where)
{
	command = "";
	command = command + "update " + table + " set " + set + " where " + where;
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // ����ó��
	else return 1;
}


// �� �˻�. ���� �����ϴ� ���� ¥��
int DataBase::DB_select(const char *column, const char *table, const char *where, const char *join, const char *order)
{
	row = NULL;
	command = "";
	command = command + "select " + column + " from " + table;
	if (strcmp(where, "")) command = command + " where " + where;  // ������ �������� ���ǹ���
	if (strcmp(join, "")) command = command + " " + join; // ���� ó���� �ִٸ� ����ó������
	if (strcmp(order, "")) command = command + " order by " + order; // ���ı��� �ִٸ� ���Ĺ�����
	stat = mysql_query(mysqlptr, command.c_str());
	if (stat != 0) return 0; // ����ó��
	result = mysql_store_result(mysqlptr); // �˻��� ����
	return 1;
}

// db �����ϴ� �Լ�
bool DataBase::DB_connect(const char *HOST, const char *USER, const char *PASS, const char *NAME, int port)
{
	mysqlptr = mysql_real_connect(&mysql, HOST, USER, PASS, NAME, port, (char *)NULL, 0);
	if (mysqlptr == NULL) return FALSE; // ����ó��
	mysql_query(&mysql, "set names euckr");
	return TRUE;
}


// select�� �˻��� ���� ���� �ִ°�? �˻� �� ������ 1ȸ�� ����ؾ���
bool DataBase::DB_hasNext()
{
	if ((row = mysql_fetch_row(result)) != NULL) return true;
	else return false;
}


// select�� ���� �ο� ��ȯ. �������� �� hasNext �����ؾ���
MYSQL_ROW DataBase::DB_getRow()
{
	return row;
}
