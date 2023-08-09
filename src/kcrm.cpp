#include "kcrm.h"
#include "./ui_kcrm.h"
#include "widget_create_file.h"

KCRM::KCRM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KCRM)
{
    ui->setupUi(this);
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
    bool flag = false;
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i].flag == window_flags::CREATE_FILE)
            flag = true;
    }
    if (flag)
    {
        return;
    }
    else
    {
        QWidget* createnewfile = new QWidget();

        m_widgets.push_back(window_content(window_flags::CREATE_FILE, createnewfile));
        m_wcf.setupUi(createnewfile);
        QMdiSubWindow* subWindow = ui->mdiArea->addSubWindow(createnewfile, Qt::FramelessWindowHint |
                                                             Qt::CustomizeWindowHint);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);

        connect(m_wcf.pushButton, &QPushButton::clicked, this, [&m_widgets = m_widgets, subWindow]() mutable
        {
            subWindow->close();
            for (size_t i = 0; i < m_widgets.size(); i++)
            {
                if (m_widgets[i].flag == window_flags::CREATE_FILE)
                {
                    m_widgets.remove(i);
                }
            }


        });

        int x = (ui->mdiArea->rect().width() - 200) / 2;
        int y = (ui->mdiArea->rect().height() - 300) / 2;
        subWindow->move(x,y);
        subWindow->setFixedSize(200, 300);
        subWindow->show();
    }



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



