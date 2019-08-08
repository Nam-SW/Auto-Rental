#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataBase.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow // 학생들 대여 프로그램
{
private:
	DataBase *DB = nullptr; // DB 클래스
	string pw, id, sex, name, duty; // 학생정보 저장
	bool change_check = false; // 비번 변경 승인값

    Q_OBJECT // QT에 들어가는 함수들

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
	void on_PBapply_clicked(); // 신청버튼 눌렀을떄 함수
	void on_PBapply_2_clicked(); // 비번변경 눌렀을때 함수

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

