#include "widget_telegram.h"
#include "ui_widget_telegram.h"

widget_telegram::widget_telegram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_telegram)
{
    ui->setupUi(this);





}

widget_telegram::~widget_telegram()
{
    delete ui;
}

QString widget_telegram::getLableName()
{
    return ui->label->text();
}

void widget_telegram::on_pushButton_clicked()
{
    emit signal_window_close();
}

void widget_telegram::on_pushButton_2_clicked()
{
    this->parentWidget()->showMinimized();
    emit signal_window_minimized();
}
