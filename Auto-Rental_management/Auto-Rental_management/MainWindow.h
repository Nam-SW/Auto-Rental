#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QtWidgets/QLabel>
#include "DataBase.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow // ������ ���� ���α׷�
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_PBman_toggled(bool checked);
	void on_PBwoman_toggled(bool checked);
	void show_students();
	void on_PBben_clicked();
	void on_PBexcelsto_clicked();

private:
	Ui::MainWindow *ui;
	QHBoxLayout *layout = nullptr;
	QLabel *line1 = nullptr;
	QLabel *line2 = nullptr;
	QLabel *line3 = nullptr;
	bool man = false, woman = false;
	DataBase *DB;
};

#endif // MAINWINDOW_H

