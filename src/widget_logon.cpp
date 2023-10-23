#include "widget_logon.h"
#include "ui_widget_logon.h"

widget_logon::widget_logon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_logon)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::CustomizeWindowHint);
    this->setWindowIcon(QIcon("./res/favicon.ico"));
    QPalette p;
    p.setBrush(this->backgroundRole(), QBrush(QPixmap("./res/ship.png")));
    this->setPalette(p);

    ui->label_2->setStyleSheet("QLabel { color : red; font-size : 15pt; }");
    ui->label_3->setStyleSheet("QLabel { color : red; font-size : 15pt; }");

    ui->lineEdit->setPlaceholderText(QString("Login"));
    ui->lineEdit->setFocus();
    ui->lineEdit_2->setPlaceholderText(QString("Password"));
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
}

widget_logon::~widget_logon()
{
    delete ui;
}

void widget_logon::set_network_name(const QString &aAddr)
{
    ui->lineEdit_4->setText(aAddr);
}

void widget_logon::set_port_num(const QString &aPort)
{
    ui->lineEdit_3->setText(aPort);
}

void widget_logon::on_pushButton_clicked()
{
    this->close();
}




