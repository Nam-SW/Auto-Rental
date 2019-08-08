#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataBase.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow // �л��� �뿩 ���α׷�
{
private:
	DataBase *DB = nullptr; // DB Ŭ����
	string pw, id, sex, name, duty; // �л����� ����
	bool change_check = false; // ��� ���� ���ΰ�

    Q_OBJECT // QT�� ���� �Լ���

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
	void on_PBapply_clicked(); // ��û��ư �������� �Լ�
	void on_PBapply_2_clicked(); // ������� �������� �Լ�

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

