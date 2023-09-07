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
