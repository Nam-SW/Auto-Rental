#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	int WIDTH = 480;
	int HEIGHT = 630;
	w.setFixedSize(WIDTH, HEIGHT); // 윈도우 크기 고정

    int x = QApplication::desktop()->screenGeometry().width();
    int y = QApplication::desktop()->screenGeometry().height();

    w.move((x- WIDTH)/2, (y - HEIGHT)/2);  // 윈도우 화면 중앙에 생성

    w.show(); // 화면 보여주기

    return a.exec();
}
