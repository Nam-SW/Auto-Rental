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

string slicing(string str, int start, int end, int step = 1); // 파이썬에서 사용하는 문자열 슬라이싱 구현
string getdate(int sw, string start = "");

// 나머진 다 같으니까 설명은 넘어가겠습니다.