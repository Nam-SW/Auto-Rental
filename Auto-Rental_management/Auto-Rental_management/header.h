#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <time.h>

#define GET_TODAY_TABLE -1
#define GET_TODAY_DATE 0
#define GET_NEXT_MONTH 28

using namespace std;

string slicing(string str, int start, int end, int step = 1); // ���̽㿡�� ����ϴ� ���ڿ� �����̽� ����
string getdate(int sw, string start = "");

// ������ �� �����ϱ� ������ �Ѿ�ڽ��ϴ�.