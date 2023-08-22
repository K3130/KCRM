#include "widget_create_file.h"
#include "ui_widget_create_file.h"

widget_create_file::widget_create_file(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_create_file)
{
    ui->setupUi(this);
}

widget_create_file::~widget_create_file()
{
    delete ui;
}


