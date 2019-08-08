#include "header.h"

string slicing(string str, int start, int end, int step = 1) {// 파이썬 문자열 슬라이싱 구현
	string temp;
	if (start < 0) start = str.length() + (start % str.length()); // start setter
	if (end < 0) end = str.length() + (end % str.length()); // end setter
	if (step > 0) { // step이 0보다 작을떄 == 반대로 순회하기
		for (int i = start; i < end && i < str.length(); i += step)
			temp += str.at(i);
	}
	else { // 바르게 순회하기
		for (int i = start; i > end && i > -1; i += step)
			temp += str.at(i);
	}

	return temp;
}

string getdate(int sw, string start) {

	string temp;

	time_t now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

	if (sw == GET_TODAY_TABLE) {// 오늘 테이블명
		temp = temp + "d" + buf[5] + buf[6] + buf[8] + buf[9];
	}
	else if (sw == GET_TODAY_DATE) { // 오늘 날짜
		for (int i = 0; i < 10; i++) temp += buf[i];
	}
	else { // 임의의 숫자를 삽입, 그 날이 지난 날짜를 반환
		if (start == "") {
			for (int i = 0; i < 10; i++)
				if (buf[i] != '-') temp += buf[i];
		} else {
			for (int i = 0; i < 10; i++)
				if (start.at(i) != '-') temp += start.at(i);
		}
		// 위에는 받은 날짜를 "yyyy-mm-dd"에서 "yyyymmdd"로 바꿔주는 과정

		int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (atoi(slicing(temp, 0, 4).c_str()) % 400 == 0 || atoi(slicing(temp, 0, 4).c_str()) % 4 == 0 && atoi(slicing(temp, 0, 4).c_str()) % 100 != 0) //윤년 판별
			month[1] = 29;


		int d = atoi(slicing(temp, 6, -1).c_str()), m = atoi(slicing(temp, 4, 6).c_str()), y = atoi(slicing(temp, 0, 4).c_str());
		d += sw; //입력받은 날을 추가
		while (d > month[m-1]) {
			d -= month[m-1];
			m++;
			if (m > 12) m = 1, y++;
		}

		temp = to_string(y) + "-";
		if (m < 10) temp += ("0" + to_string(m) + "-");
		else temp += (to_string(m) + "-");
		if (d < 10) temp += ("0" + to_string(d));
		else temp += to_string(d);
		// 위에는 날짜를 다시 "yyyy-mm-dd"로 바꿔주는 과정
	}


	return temp;
}