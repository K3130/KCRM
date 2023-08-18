#include "kcrm.h"

KCRM::KCRM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KCRM)
{
    ui->setupUi(this);
    ui->plainTextEdit->setMaximumHeight(100);
    ui->plainTextEdit->setMinimumHeight(100);
    ui->label->setMaximumHeight(12);

    ui->mdiArea->viewport()->setMouseTracking(true);


}

KCRM::~KCRM()
{
    delete ui;
}


void KCRM::create_text_document()
{
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i].flag == window_flags::CREATE_FILE)
        {
            m_widgets[i].pWidget->close();
            m_widgets.remove(i);
        }
    }


    QWidget* text_document = new widget_text_document(this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(text_document, Qt::FramelessWindowHint);
    m_widgets.push_back(window_content(window_flags::TEXT_DOCUMENT, sub_window));
    sub_window->setAttribute(Qt::WA_DeleteOnClose);

    int x = (ui->mdiArea->rect().width() - 500) / 2;
    int y = (ui->mdiArea->rect().height() - 400) / 2;
    sub_window->move(x,y);
    sub_window->show();


    connect(dynamic_cast<widget_text_document*>(text_document),
            &widget_text_document::signal_window_minimized,
            this,
            &KCRM::window_minimized);

}

void KCRM::window_minimized()
{
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if(m_widgets[i].pWidget->isMinimized())
        {
            ui->widget->createButton(m_widgets[i].pWidget->windowTitle(), m_widgets[i].pWidget);

        }
    }

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
        Ui::widget_create_file m_wcf;
        QWidget* createnewfile = new QWidget(this);
        m_wcf.setupUi(createnewfile);

        QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(createnewfile, Qt::FramelessWindowHint |
                                                             Qt::CustomizeWindowHint);
        m_widgets.push_back(window_content(window_flags::CREATE_FILE, sub_window));
        sub_window->setAttribute(Qt::WA_DeleteOnClose);

        int x = (ui->mdiArea->rect().width() - 200) / 2;
        int y = (ui->mdiArea->rect().height() - 300) / 2;
        sub_window->move(x,y);
        sub_window->setFixedSize(200, 300);
        sub_window->show();


        connect(m_wcf.pushButton_2, &QPushButton::clicked, this, &KCRM::create_text_document);
        connect(m_wcf.pushButton, &QPushButton::clicked, this, [=]()
        {
            sub_window->close();
            for (size_t i = 0; i < m_widgets.size(); i++)
            {
                if (m_widgets[i].flag == window_flags::CREATE_FILE)
                {
                    m_widgets.remove(i);
                }
            }


        });


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



