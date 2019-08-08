#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include <QDate>
#include <QMessageBox>
#include <QIntValidator>
#include "libxl.h"
#include "header.h"

using namespace libxl;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	layout = new QHBoxLayout;

	line1 = new QLabel(ui->scrollContents);
	line1->setObjectName(QString::fromUtf8("line1"));
	line1->setGeometry(QRect(25, 10, 90, 300));
	line1->setAlignment(Qt::AlignTop);
	line1->setStyleSheet(QString::fromUtf8("font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\ncolor: rgb(0, 0, 0);"));

	line2 = new QLabel(ui->scrollContents);
	line2->setObjectName(QString::fromUtf8("line2"));
	line2->setGeometry(QRect(100, 10, 90, 300));
	line2->setAlignment(Qt::AlignTop);
	line2->setStyleSheet(QString::fromUtf8("font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\ncolor: rgb(0, 0, 0);"));

	line3 = new QLabel(ui->scrollContents);
	line3->setObjectName(QString::fromUtf8("line3"));
	line3->setGeometry(QRect(200, 10, 90, 300));
	line3->setAlignment(Qt::AlignTop);
	line3->setStyleSheet(QString::fromUtf8("font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\ncolor: rgb(0, 0, 0);"));

	layout->addWidget(line1);
	layout->addWidget(line2);
	layout->addWidget(line3);
	ui->scrollContents->setLayout(layout);
	// 위에 잡다한건 한가운데에 학생 정보를 출력할 라벨을 동적으로 선언, 정의한 코드
	// 여기서 선언을 해주지 않고 QT 파일에서 하면 스크롤바가 먹히질 않음

	QDate date = QDate::currentDate();
	QString day = date.toString();
	QString day_text = date.toString("yyyy.MM.dd(ddd)");  // 맨 위의 라벨에 오늘 날짜 출력

	ui->Ldate->setText(day_text);  //현재 시간 출력

	ui->PBman->setCheckable(true);
	ui->PBwoman->setCheckable(true);

	DB = new DataBase(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT); // DB 셋업

	ui->LEclass->setValidator(new QIntValidator(1201, 3422, this));  //숫자만 입력하게 제한
	this->setWindowTitle("Auto-Rental_management");
}


MainWindow::~MainWindow()
{
	delete line1;
	delete line2;
	delete line3;
	delete layout;
	// 동적 할당 메모리 해제
	delete ui;
}


void MainWindow::on_PBman_toggled(bool checked)
{
	if (checked) {
		man = true;
	} else {
		man = false;
	}
	// 출력할 목록에 남자를 추가, 제거
	show_students(); // 이후 변경된 조건문으로 실행
}

void MainWindow::on_PBwoman_toggled(bool checked)
{
	if (checked) {
		woman = true;
	} else {
		woman = false; 
	}
	// 출력할 목록에 여자를 추가, 제거
	show_students(); // 이후 변경된 조건문으로 실행
}

void MainWindow::show_students() { // 남녀 버튼을 누르고 결과 출력하는 함수
	MYSQL_ROW row;
	int stat;
	string where = "";
	if (!man && !woman) { // 에러처리
		line1->setText("");
		line2->setText("");
		line3->setText("");
		return;
	}
	else if (man && !woman) where = "sex = 'man'";
	else if (!man && woman) where = "sex = 'woman'";
	// 조건 저장

	if (where == "") stat = DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str());
	else stat = DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str(), where.c_str());
	// 조건대로 검색

	if (!stat) {
		// 테이블이 없는 상태
		if (DB->DB_create(getdate(GET_TODAY_TABLE).c_str(), "id smallint, sex enum('man', 'woman'), name char(4)", "id")) {
			line1->setText("");
			line2->setText("");
			line3->setText("");
			QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("등록한 학생이 없습니다."));
			return;
		} else { // 에러처리
			QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("테이블 생성 에러"));
			return;
		}
	} else {
		// 테이블 있음!
		string l1 = "", l2 = "", l3 = "";
		if (DB->DB_hasNext()) { // 등록자가 있음. 정보를 라벨에 출력할 스트링에 저장
			row = DB->DB_getRow();
			l1 = l1 + row[0] + "\n";
			l2 = l2 + (!strcmp(row[1], "man") ? "남자" : "여자") + "\n";
			l3 = l3 + row[2] + "\n";
		} else { // 테이블은 있으나, 등록한 학생이 없음
			line1->setText("");
			line2->setText("");
			line3->setText("");
			QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("등록한 학생이 없습니다."));
			return;
		}
		while (DB->DB_hasNext()) { // 등록자가 아직 존재함. 정보를 라벨에 출력할 스트링에 저장
			row = DB->DB_getRow();
			l1 = l1 + row[0] + "\n";
			l2 = l2 + (!strcmp(row[1], "man") ? "남자" : "여자") + "\n";
			l3 = l3 + row[2] + "\n";
		}

		line1->setText(QString::fromLocal8Bit(l1.c_str()));
		line2->setText(QString::fromLocal8Bit(l2.c_str()));
		line3->setText(QString::fromLocal8Bit(l3.c_str()));
		// 저장된 학생들을 출력
	}
}

void MainWindow::on_PBben_clicked() { // 노트북 사용 금지 버튼
	string id = "", name = "";
	if (ui->LEclass->text().toStdString() == "") { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("학번을 입력하세요."));
		return;
	}
	string temp = "id = " + ui->LEclass->text().toStdString();
	if (!DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str(), temp.c_str())) { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("검색 에러")); //잘못 입력시 출력
		return;
	}
	MYSQL_ROW row;
	if (DB->DB_hasNext()) {
		// 검색한 학번이 존재
		row = DB->DB_getRow();
		id = row[0], name = row[2];
	} else { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("존재하지 않는 학번이거나 \n입력한 학번이 등록하지 않았습니다."));
		ui->LEclass->setText("");
		return;
	}

	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit((name + " 학생을 금지시키겠습니까?").c_str()), QMessageBox::Yes | QMessageBox::No); // Yes, No의 선택 메세지 박스
	if (reply == QMessageBox::Yes) { // Yes를 선택함 == 금지시킴
		id = "id = " + id;
		if (DB->DB_update("students", ("duty = '" + getdate(GET_NEXT_MONTH) + "'").c_str(), id.c_str())) {
			if (DB->DB_delete(getdate(GET_TODAY_TABLE).c_str(), id.c_str())) {
				QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("금지, 삭제되었습니다."));
				show_students();
			} else { // 에러처리
				QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("삭제 실패")); 
			}
		} else { // 에러처리
			QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("금지 실패"));
		}
	}
	// no를 선택하면 아무일도 일어나지 않으므로, 처리x

	ui->LEclass->setText("");
}

void MainWindow::on_PBexcelsto_clicked() {  // 엑셀 저장 버튼 눌렀을떄
	MYSQL_ROW row;
	int stat;
	string where = "";
	if (!man && !woman) { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("등록한 학생이 없습니다."));
		return;
	}

	else if (man && !woman) where = "sex = 'man'";
	else if (!man && woman) where = "sex = 'woman'";
	// 조건 저장

	if (where == "") stat = DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str());
	else stat = DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str(), where.c_str());
	// 조건대로 검색

	if (stat) {
		int row_num = 1; MYSQL_ROW row;
		if (!DB->DB_hasNext()) { // 조건이 맞는 등록학생 x
			QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("등록한 학생이 없습니다."));
			return;
		}
		// 학생이 등록함!
		Book* book = xlCreateBook(); // 엑셀 파일 생성
		if (book) { // 생성 성공
			Sheet* sheet = book->addSheet("대여자 명단");

			if (sheet) {
				sheet->setCol(0, 0, 10); // 1번 컬럼 사이즈 조절
				sheet->setCol(1, 1, 20); // 2번 컬럼 사이즈 조절

				// 폰트
				Font* textFont = book->addFont();
				textFont->setSize(12);

				Font* bordFont = book->addFont(textFont);
				bordFont->setBold();

				Font* TitleFont = book->addFont(bordFont);
				TitleFont->setSize(15);

				// 포맷: 각 입력값의 스타일들
				Format* textFormat = book->addFormat();
				textFormat->setFont(textFont);
				textFormat->setBorder();

				Format* rightFormat = book->addFormat(textFormat);
				rightFormat->setAlignH(ALIGNH_RIGHT);

				Format* bordFormat = book->addFormat();
				bordFormat->setFont(bordFont);
				bordFormat->setBorder();

				Format* TitleFormat = book->addFormat();
				TitleFormat->setFont(TitleFont);
				TitleFormat->setBorder();

				Format* right_TitleFormat = book->addFormat(TitleFormat);
				right_TitleFormat->setAlignH(ALIGNH_RIGHT);

				sheet->writeStr(row_num, 0, "학번", TitleFormat); // 라벨링
				sheet->writeStr(row_num, 1, "이름", right_TitleFormat);
				
				do {
					row_num++; //작성할 칸 내리기
					row = DB->DB_getRow();
					sheet->writeStr(row_num, 0, row[0], textFormat); // 학번 저장
					sheet->writeStr(row_num, 1, row[2], rightFormat); // 이름 저장
				} while (DB->DB_hasNext());
				row_num++;

				sheet->writeStr(row_num, 0, "합계", bordFormat);// 라벨링
				sheet->writeNum(row_num, 1, row_num - 2, bordFormat);// 총 신청자 수 저장
			} else { // 에러처리
				QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("엑셀 파일 에러"));
				return;
			}
			book->save((getdate(GET_TODAY_TABLE) + ".xls").c_str());// 경로 설정
			book->release(); // 저장
			QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit((getdate(GET_TODAY_TABLE) + "파일을 생성했습니다.").c_str()));
		} else { // 에러처리
			QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("엑셀 파일 생성 실패"));
		}
	}
	else { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("학생 검색 실패"));
	}
}