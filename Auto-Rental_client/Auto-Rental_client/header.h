#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <mysql.h>
#include <time.h>

#define GET_TODAY_TABLE -1 // 오늘 날짜의 테이블을 얻는 값
#define GET_TODAY_DATE 0 // 오늘 날짜를 얻는 값
#define GET_NEXT_MONTH 28 // 한달

using namespace std;

string getdate(int sw, string start = ""); // 날짜를 보내주는 함수