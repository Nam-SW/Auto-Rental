#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <time.h>

#define GET_TODAY_TABLE -1 // ���� ��¥�� ���̺��� ��� ��
#define GET_TODAY_DATE 0 // ���� ��¥�� ��� ��
#define GET_NEXT_MONTH 28 // �Ѵ�

using namespace std;

string getdate(int sw, string start = ""); // ��¥�� �����ִ� �Լ�