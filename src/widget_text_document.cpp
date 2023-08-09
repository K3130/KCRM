#include "widget_text_document.h"
#include "ui_widget_text_document.h"

widget_text_document::widget_text_document(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_text_document)
{
    ui->setupUi(this);
}

widget_text_document::~widget_text_document()
{
    delete ui;
}
