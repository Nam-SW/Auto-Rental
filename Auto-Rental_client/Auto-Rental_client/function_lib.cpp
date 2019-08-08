#include "header.h"

string slicing(string str, int start, int end, int step = 1) {// ���̽� ���ڿ� �����̽� ����
	string temp;
	if (start < 0) start = str.length() + (start % str.length()); // start setter
	if (end < 0) end = str.length() + (end % str.length()); // end setter
	if (step > 0) { // step�� 0���� ������ == �ݴ�� ��ȸ�ϱ�
		for (int i = start; i < end && i < str.length(); i += step)
			temp += str.at(i);
	}
	else { // �ٸ��� ��ȸ�ϱ�
		for (int i = start; i > end && i > -1; i += step)
			temp += str.at(i);
	}

	return temp;
}

string getdate(int sw, string start) {

	string temp;

	time_t now = time(0); //���� �ð��� time_t Ÿ������ ����
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss ������ ��Ʈ��

	if (sw == GET_TODAY_TABLE) {// ���� ���̺��
		temp = temp + "d" + buf[5] + buf[6] + buf[8] + buf[9];
	}
	else if (sw == GET_TODAY_DATE) { // ���� ��¥
		for (int i = 0; i < 10; i++) temp += buf[i];
	}
	else { // ������ ���ڸ� ����, �� ���� ���� ��¥�� ��ȯ
		if (start == "") {
			for (int i = 0; i < 10; i++)
				if (buf[i] != '-') temp += buf[i];
		} else {
			for (int i = 0; i < 10; i++)
				if (start.at(i) != '-') temp += start.at(i);
		}
		// ������ ���� ��¥�� "yyyy-mm-dd"���� "yyyymmdd"�� �ٲ��ִ� ����

		int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (atoi(slicing(temp, 0, 4).c_str()) % 400 == 0 || atoi(slicing(temp, 0, 4).c_str()) % 4 == 0 && atoi(slicing(temp, 0, 4).c_str()) % 100 != 0) //���� �Ǻ�
			month[1] = 29;


		int d = atoi(slicing(temp, 6, -1).c_str()), m = atoi(slicing(temp, 4, 6).c_str()), y = atoi(slicing(temp, 0, 4).c_str());
		d += sw; //�Է¹��� ���� �߰�
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
		// ������ ��¥�� �ٽ� "yyyy-mm-dd"�� �ٲ��ִ� ����
	}


	return temp;
}