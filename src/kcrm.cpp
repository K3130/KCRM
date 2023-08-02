#include "kcrm.h"
#include "./ui_kcrm.h"
#include "widget_create_file.h"

KCRM::KCRM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KCRM)
{
    ui->setupUi(this);
    //ui->mdiArea->setMinimumHeight(500);
    //ui->mdiArea->setMaximumHeight(1000);


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
    QWidget* createnewfile = new QWidget();
    Ui::widget_create_file* test = new Ui::widget_create_file();
    test->setupUi(createnewfile);


    QMdiSubWindow* subWindow = ui->mdiArea->addSubWindow(createnewfile, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);


//    ui->mdiArea->setStyleSheet("QWidget::title {"
//                                        "background-color: #007cad;"
//                                        "border: 4px;"

//                               "}"

//                               "QWidget {"
//                                    "min-height: 300px;"
//                                    "min-width: 290px;"
//                                    "background-color: white;"
//                                    "border: none;"
//                                "}"

//                               "QWidget::close-button {"
//                                    "border: 5px;"

//                                    "background-color: #0095b6;"
//                                    "color: white;"
//                                    "padding: 4px;"
//                                    "font-size: 12px;"
//                                    "width: 5px;"
//                                    "height: 5px;"
//                               "}"


//                               );





    int x = (ui->mdiArea->rect().width() - 290) / 2;
    int y = (ui->mdiArea->rect().height() - 300) / 2;
    subWindow->move(x,y);





    //createnewfile.setWindowTitle("Выбор нового документа");

    subWindow->show();
    //createnewfile.show();
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

