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
	DB = new DataBase(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT); // DB ���� �Ҵ�

	QPixmap pix("image.png"); // �Ѱ�� �̹��� �ҷ�����
	ui->Lpic->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));
	ui->inID->setPlaceholderText(QString::fromLocal8Bit("  �й� (1�г� 1�� 1�� -> 1101 )"));
	ui->inPW->setPlaceholderText(QString::fromLocal8Bit("  ��й�ȣ"));
	// ���� 2���� �й�, PW �ؽ�Ʈ�ڽ��� �������ϰ� ���ִ°�

	ui->inID->setValidator(new QIntValidator(1201, 3422, this));  //���ڸ� �Է��ϰ� ����
	this->setWindowTitle("Auto-Rental_client"); // ������ Ÿ��Ʋ ����

	pw = "";
}

MainWindow::~MainWindow()
{
	delete DB;
    delete ui;
}

void MainWindow::on_PBapply_clicked() { // ��û��ư �Լ�
	MYSQL_ROW row;
	if (ui->inID->text() == "") { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("�й��� �Է��ϼ���."));
		return;
	}
	if (ui->inPW->text() == "") { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��й�ȣ�� �Է��ϼ���."));
		return;
	}
	if (!DB->DB_select("*", "students", ("id = " + ui->inID->text().toStdString()).c_str())) { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("�˻� ����")); 
		return;
	}
	if (DB->DB_hasNext()) {
		// �˻��� �й��� ����
		row = DB->DB_getRow();
		id = row[0]; sex = row[4]; name = row[5]; duty = row[6] == NULL ? "" : row[6], pw = row[7] == NULL ? "" : row[7]; // ���� ����
	} else { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("�ùٸ� �й��� �Է��ϼ���."));
		ui->inID->setText("");
		ui->inPW->setText("");
		return;
	}

	string message = "��ϵǾ����ϴ�.";
	if (pw == "") { // ���� ��й�ȣ�� �������� ����
		QMessageBox::information(this, QString::fromLocal8Bit("�˸�"), QString::fromLocal8Bit("���䷻Ż�� ó�� �α����ϼ̽��ϴ�.\n��й�ȣ�� �Է��ϰ� ��� ���� ��ư�� �����ּ���."));
		return;
	} else if (pw != ui->inPW->text().toStdString()) { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��й�ȣ�� Ʋ�Ƚ��ϴ�."));
		ui->inPW->setText("");
		return;
	}

	// �α��� ����
	if (!DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str())) {
		// ���̺��� ���� ����
		if (DB->DB_create(getdate(GET_TODAY_TABLE).c_str(), "id smallint, sex enum('man', 'woman'), name char(4)", "id")) { // ����ó��
			if (!DB->DB_insert(getdate(GET_TODAY_TABLE).c_str(), (id + ", '" + sex + "', '" + name + " '").c_str())) {
				QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��� ����"));
				return;
			}
		}
		else { // ����ó��
			QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��� ����"));
			return;
		}
	}
	else {
		// ���̺��� ����
		if (!DB->DB_select("*", getdate(GET_TODAY_TABLE).c_str(), ("id = " + id).c_str())) { // ����ó��
			QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��� ����"));
			return;
		}
		
		if (DB->DB_hasNext()) {
			// �̹� ����� ����
			row = DB->DB_getRow();
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, QString::fromLocal8Bit("�˸�"), QString::fromLocal8Bit("����� ����Ͻðڽ��ϱ�?"), QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes) {  // ��� ���
				if (DB->DB_delete(getdate(GET_TODAY_TABLE).c_str(), ("id = " + id).c_str())) message = "��ҿ� �����߽��ϴ�.";
				else { // ����ó��
					QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��� ����"));
					return;
				}
			} else { // ��� ��� ����
				ui->inID->setText("");
				ui->inPW->setText("");
				return;
			}
		} else {
			// ���� ��� ����
			if (duty == "") { // �������� ����
				message = name + " �л�\n" + message;
				if (!DB->DB_insert(getdate(GET_TODAY_TABLE).c_str(), (id + ", '" + sex + "', '" + name + " '").c_str())) { // ����ó��
					QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��� ����"));
					return;
				}
			}
			else { // ������!
				string dutyday, today;
				for (int i = 0; i < duty.length(); i++) // ���� ������
					if (duty.at(i) != '-') dutyday += duty.at(i);
				string text = getdate(GET_TODAY_DATE); // ���� ��¥
				for (int i = 0; i < getdate(GET_TODAY_DATE).length(); i++)
					if (text.at(i) != '-') today += text.at(i);

				if (atoi(dutyday.c_str()) < atoi(today.c_str())) { // �������� ���� ���
					if (DB->DB_update("students", "duty = NULL", ("id = " + id).c_str())) { // �������� NULL�� �����ϰ�
						text = id + ", '" + sex + "', '" + name + " '";
						if (!DB->DB_insert(getdate(GET_TODAY_TABLE).c_str(), text.c_str())) { // ����ó��
							QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��� ����"));
							return;
						}
						message = name + " �л�\n" + message;
					} else { // ����ó��
						QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("���� ����"));
						return;
					}
				}
				else { // �����Ⱓ
					message = "���� ��Ʈ�� �뿩 ���� �Ⱓ�Դϴ�.\n" + getdate(1, duty) + "���� �뿩�� �����մϴ�.";
				}
			}
		}
	}

	ui->inID->setText("");
	ui->inPW->setText("");
	QMessageBox::information(this, QString::fromLocal8Bit("�˸�"), QString::fromLocal8Bit(message.c_str()));  // �޼��� �ڽ� ����
}

void MainWindow::on_PBapply_2_clicked() { // ������� �Լ�
	MYSQL_ROW row;
	if (ui->inID->text() == "") { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("�й��� �Է��ϼ���."));
		return;
	}
	if (ui->inPW->text() == "") { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("��й�ȣ�� �Է��ϼ���."));
		return;
	}
	if (!DB->DB_select("*", "students", ("id = " + ui->inID->text().toStdString()).c_str())) { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("�˻� ����"));
		return;
	}
	if (DB->DB_hasNext()) {
		// �˻��� �й��� ����
		row = DB->DB_getRow();
		id = row[0]; sex = row[4]; name = row[5]; duty = row[6] == NULL ? "" : row[6]; // ���� ����
	} else { // ����ó��
		QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("�ùٸ� �й��� �Է��ϼ���."));
		ui->inID->setText("");
		ui->inPW->setText("");
		return;
	}

	if (row[7] == NULL) { // ó�� ����������
		if (DB->DB_update("students", ("pw = '" + ui->inPW->text().toStdString() + "'").c_str(), ("id = " + id).c_str())) {
			QMessageBox::information(this, QString::fromLocal8Bit("�˸�"), QString::fromLocal8Bit("��й�ȣ�� ����Ǿ����ϴ�.\n��û ��ư�� ���� ��û���ּ���."));
		}
		else { // ����ó��
			QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("���� ����"));
		}
	} else if (change_check) { // ���� ������ ���ϋ�
		if (DB->DB_update("students", ("pw = '" + ui->inPW->text().toStdString() + "'").c_str(), ("id = " + id).c_str())) {
			QMessageBox::information(this, QString::fromLocal8Bit("�˸�"), QString::fromLocal8Bit("��й�ȣ�� ����Ǿ����ϴ�."));
		}
		else { // ����ó��
			QMessageBox::information(this, QString::fromLocal8Bit("���"), QString::fromLocal8Bit("���� ����"));
		}
		change_check = false;  // ���� ��ġ��, �ٽ� ����ġ ����
	} else if (ui->inPW->text().toStdString() == row[7]) { // ���� Ȯ�� �ϰ�
		change_check = true; // ���� ����
		ui->inPW->setText("");
		QMessageBox::information(this, QString::fromLocal8Bit("�˸�"), QString::fromLocal8Bit("���� Ȯ���� �Ϸ�Ǿ����ϴ�.\nȮ�� ��ư�� ������ �ٲ� ��й�ȣ�� �Է��� ��\n�ٽ� ��� ���� ��ư�� �����ּ���."));
	} else { // ���������� ���� ���� ���� == �Է��� ��й�ȣ�� Ʋ��
		ui->inPW->setText("");
		QMessageBox::information(this, QString::fromLocal8Bit("�˸�"), QString::fromLocal8Bit("��й�ȣ�� Ʋ�Ȱų� ���� ���� Ȯ���� �Ϸ���� �ʾҽ��ϴ�.\n���� ��й�ȣ�� �Է��ϰ� ��� ���� ��ư�� �����ּ���."));
	}
}