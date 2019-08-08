#include "MainWindow.h"
#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	int WIDTH = 480;
	int HEIGHT = 630;
	w.setFixedSize(WIDTH, HEIGHT); 

	int x = QApplication::desktop()->screenGeometry().width();
	int y = QApplication::desktop()->screenGeometry().height();

	w.move((x - WIDTH) / 2, (y - HEIGHT) / 2);  


	w.show();

	return a.exec();
}


// 여기도 클라이언트 프로젝트와 동일하므로 설명하지 않겠습니다.