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
    //test
    verify();
}

widget_logon::~widget_logon()
{
    delete ui;
}

void widget_logon::on_pushButton_clicked()
{
    this->close();
}

bool widget_logon::verify()
{
    bool test = true;
    if(test)
    {
        emit verify_succes();
        return true;
    }
    return false;
}


