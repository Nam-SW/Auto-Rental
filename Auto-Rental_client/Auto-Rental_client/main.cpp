#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	int WIDTH = 480;
	int HEIGHT = 630;
	w.setFixedSize(WIDTH, HEIGHT); // ������ ũ�� ����

    int x = QApplication::desktop()->screenGeometry().width();
    int y = QApplication::desktop()->screenGeometry().height();

    w.move((x- WIDTH)/2, (y - HEIGHT)/2);  // ������ ȭ�� �߾ӿ� ����

    w.show(); // ȭ�� �����ֱ�

    return a.exec();
}
