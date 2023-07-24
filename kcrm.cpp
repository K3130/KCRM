#include "kcrm.h"
#include "./ui_kcrm.h"

KCRM::KCRM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KCRM)
{
    ui->setupUi(this);
}

KCRM::~KCRM()
{
    delete ui;
}

