#include "kcrm.h"
#include "./ui_kcrm.h"

KCRM::KCRM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KCRM)
{
    ui->setupUi(this);
    ui->mdiArea->setMinimumHeight(500);
    ui->mdiArea->setMaximumHeight(1000);
    ui->plainTextEdit->setMaximumHeight(100);
    ui->plainTextEdit->setMinimumHeight(100);
    ui->label->setMaximumHeight(12);

}

KCRM::~KCRM()
{
    delete ui;
}


void KCRM::on_actionNewFile_triggered()
{

}


void KCRM::on_actionOpenFile_triggered()
{

}


void KCRM::on_actionSaveFile_triggered()
{

}


void KCRM::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{

}

