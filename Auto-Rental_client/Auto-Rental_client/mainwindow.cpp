#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include "header.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	DB = new DataBase(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT); // DB 변수 할당

	QPixmap pix("image.png"); // 한가운데 이미지 불러오기
	ui->Lpic->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));
	ui->inID->setPlaceholderText(QString::fromLocal8Bit("  학번 (1학년 1반 1번 -> 1101 )"));
	ui->inPW->setPlaceholderText(QString::fromLocal8Bit("  비밀번호"));
	// 위에 2개는 학번, PW 텍스트박스에 반투명하게 써주는거

	ui->inID->setValidator(new QIntValidator(1201, 3422, this));  //숫자만 입력하게 제한
	this->setWindowTitle("Auto-Rental_client"); // 윈도우 타이틀 지정

	pw = "";
}

MainWindow::~MainWindow()
{
	delete DB;
    delete ui;
}

void MainWindow::on_PBapply_clicked() { // 신청버튼 함수
	MYSQL_ROW row;
	if (ui->inID->text() == "") { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("학번을 입력하세요."));
		return;
	}
	if (ui->inPW->text() == "") { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("비밀번호를 입력하세요."));
		return;
	}
	if (!DB->DB_select("*", "students", ("id = " + ui->inID->text().toStdString()).c_str())) { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("검색 에러")); 
		return;
	}
	if (DB->DB_hasNext()) {
		// 검색한 학번이 존재
		row = DB->DB_getRow();
		id = row[0]; sex = row[4]; name = row[5]; duty = row[6] == NULL ? "" : row[6], pw = row[7] == NULL ? "" : row[7]; // 정보 저장
	} else { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("올바른 학번을 입력하세요."));
		ui->inID->setText("");
		ui->inPW->setText("");
		return;
	}

	string message = "등록되었습니다.";
	if (pw == "") { // 아직 비밀번호가 지정되지 않음
		QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("오토렌탈에 처음 로그인하셨습니다.\n비밀번호를 입력하고 비번 변경 버튼을 눌러주세요."));
		return;
	} else if (pw != ui->inPW->text().toStdString()) { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("비밀번호가 틀렸습니다."));
		ui->inPW->setText("");
		return;
	}

	// 로그인 성공
	if (!DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str())) {
		// 테이블이 없는 상태
		if (DB->DB_create(getdate(GET_TODAY_TABLE).c_str(), "id smallint, sex enum('man', 'woman'), name char(4)", "id")) { // 에러처리
			if (!DB->DB_insert(getdate(GET_TODAY_TABLE).c_str(), (id + ", '" + sex + "', '" + name + " '").c_str())) {
				QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("등록 에러"));
				return;
			}
		}
		else { // 에러처리
			QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("등록 에러"));
			return;
		}
	}
	else {
		// 테이블은 있음
		if (!DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str(), ("id = " + id).c_str())) { // 에러처리
			QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("등록 에러"));
			return;
		}
		
		if (DB->DB_hasNext()) {
			// 이미 등록한 상태
			row = DB->DB_getRow();
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("등록을 취소하시겠습니까?"), QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes) {  // 등록 취소
				if (DB->DB_delete(getdate(GET_TODAY_TABLE).c_str(), ("id = " + id).c_str())) message = "취소에 성공했습니다.";
				else { // 에러처리
					QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("취소 실패"));
					return;
				}
			} else { // 등록 취소 안함
				ui->inID->setText("");
				ui->inPW->setText("");
				return;
			}
		} else {
			// 아직 등록 안함
			if (duty == "") { // 금지되지 않음
				message = name + " 학생\n" + message;
				if (!DB->DB_insert(getdate(GET_TODAY_TABLE).c_str(), (id + ", '" + sex + "', '" + name + " '").c_str())) { // 에러처리
					QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("등록 에러"));
					return;
				}
			}
			else { // 금지됨!
				string dutyday, today;
				for (int i = 0; i < duty.length(); i++) // 금지 종료일
					if (duty.at(i) != '-') dutyday += duty.at(i);
				string text = getdate(GET_TODAY_DATE); // 오늘 날짜
				for (int i = 0; i < getdate(GET_TODAY_DATE).length(); i++)
					if (text.at(i) != '-') today += text.at(i);

				if (atoi(dutyday.c_str()) < atoi(today.c_str())) { // 만기일이 지난 경우
					if (DB->DB_update("students", "duty = NULL", ("id = " + id).c_str())) { // 만기일을 NULL로 설정하고
						text = id + ", '" + sex + "', '" + name + " '";
						if (!DB->DB_insert(getdate(GET_TODAY_TABLE).c_str(), text.c_str())) { // 에러처리
							QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("등록 에러"));
							return;
						}
						message = name + " 학생\n" + message;
					} else { // 에러처리
						QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("변경 에러"));
						return;
					}
				}
				else { // 금지기간
					message = "현재 노트북 대여 금지 기간입니다.\n" + getdate(1, duty) + "부터 대여가 가능합니다.";
				}
			}
		}
	}

	ui->inID->setText("");
	ui->inPW->setText("");
	QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit(message.c_str()));  // 메세지 박스 띄우기
}

void MainWindow::on_PBapply_2_clicked() { // 비번변경 함수
	MYSQL_ROW row;
	if (ui->inID->text() == "") { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("학번을 입력하세요."));
		return;
	}
	if (ui->inPW->text() == "") { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("비밀번호를 입력하세요."));
		return;
	}
	if (!DB->DB_select("*", "students", ("id = " + ui->inID->text().toStdString()).c_str())) { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("검색 에러"));
		return;
	}
	if (DB->DB_hasNext()) {
		// 검색한 학번이 존재
		row = DB->DB_getRow();
		id = row[0]; sex = row[4]; name = row[5]; duty = row[6] == NULL ? "" : row[6]; // 정보 저장
	} else { // 에러처리
		QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("올바른 학번을 입력하세요."));
		ui->inID->setText("");
		ui->inPW->setText("");
		return;
	}

	if (row[7] == NULL) { // 처음 접속했을때
		if (DB->DB_update("students", ("pw = '" + ui->inPW->text().toStdString() + "'").c_str(), ("id = " + id).c_str())) {
			QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("비밀번호가 변경되었습니다.\n신청 버튼을 눌러 신청해주세요."));
		}
		else { // 에러처리
			QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("변경 실패"));
		}
	} else if (change_check) { // 변경 승인이 참일떄
		if (DB->DB_update("students", ("pw = '" + ui->inPW->text().toStdString() + "'").c_str(), ("id = " + id).c_str())) {
			QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("비밀번호가 변경되었습니다."));
		}
		else { // 에러처리
			QMessageBox::information(this, QString::fromLocal8Bit("경고"), QString::fromLocal8Bit("변경 실패"));
		}
		change_check = false;  // 변경 마치고, 다시 스위치 끄기
	} else if (ui->inPW->text().toStdString() == row[7]) { // 본인 확인 하고
		change_check = true; // 변경 승인
		ui->inPW->setText("");
		QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("본인 확인이 완료되었습니다.\n확인 버튼을 누르고 바꿀 비밀번호를 입력한 후\n다시 비번 변경 버튼을 눌러주세요."));
	} else { // 본인인증을 받지 않은 상태 == 입력한 비밀번호가 틀림
		ui->inPW->setText("");
		QMessageBox::information(this, QString::fromLocal8Bit("알림"), QString::fromLocal8Bit("비밀번호가 틀렸거나 아직 본인 확인이 완료되지 않았습니다.\n현재 비밀번호를 입력하고 비번 변경 버튼을 눌러주세요."));
	}
}