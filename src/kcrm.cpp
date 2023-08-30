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
        if (m_widgets[i].type == window_type::CREATE_FILE)
        {
            m_widgets[i].pWidget->close();
            m_widgets.remove(i);
        }
    }

    QWidget* text_document = new widget_text_document(this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(text_document, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
    QPushButton* button = new QPushButton();
    button->setText(dynamic_cast<widget_text_document*>(text_document)->getLableName());
    m_widgets.push_back(window_content(id ,window_type::TEXT_DOCUMENT, sub_window, button));
    sub_window->setAttribute(Qt::WA_DeleteOnClose);
    int x = (ui->mdiArea->rect().width() - 500) / 2;
    int y = (ui->mdiArea->rect().height() - 400) / 2;
    sub_window->move(x,y);
    sub_window->show();

    connect(dynamic_cast<widget_text_document*>(text_document),
            &widget_text_document::signal_window_minimized,
            this,
            [=](){
                window_minimized(id);
            });

    connect(dynamic_cast<widget_text_document*>(text_document),
            &widget_text_document::signal_window_close,
            this,
            [=](){
               window_close(id);
            });

}

void KCRM::create_table_document()
{
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i].type == window_type::CREATE_FILE)
        {
            m_widgets[i].pWidget->close();
            m_widgets.remove(i);
        }
    }

    QWidget* table_document = new widget_table_document(this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(table_document, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
    QPushButton* button = new QPushButton();
    button->setText(dynamic_cast<widget_table_document*>(table_document)->getLableName());
    m_widgets.push_back(window_content(id ,window_type::TABLE_DOCUMENT, sub_window, button));
    sub_window->setAttribute(Qt::WA_DeleteOnClose);
    int x = (ui->mdiArea->rect().width() - 500) / 2;
    int y = (ui->mdiArea->rect().height() - 400) / 2;
    sub_window->move(x,y);
    sub_window->show();

    connect(dynamic_cast<widget_table_document*>(table_document),
            &widget_table_document::signal_window_minimized,
            this,
            [=](){
                window_minimized(id);
            });

    connect(dynamic_cast<widget_table_document*>(table_document),
            &widget_table_document::signal_window_close,
            this,
            [=](){
               window_close(id);
            });
}

void KCRM::window_minimized(qint32 id)
{    
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if(m_widgets[i].id == id)
        {
            ui->widget->createButton(m_widgets[i].pButton, m_widgets[i].pWidget);
        }
    }

}

void KCRM::window_close(qint32 id)
{
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i].id == id)
        {
            bool file_is_changed = false;
            if (m_widgets[i].type == window_type::TEXT_DOCUMENT)
            {
                widget_text_document *pwtd = dynamic_cast<widget_text_document*>(ui->mdiArea->activeSubWindow()->widget());
                file_is_changed = pwtd->getFileState();
                if (file_is_changed)
                {
                    QMessageBox mb;
                    mb.setText("Сохранить файл?");
                    mb.setWindowTitle(" ");
                    mb.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    mb.setDefaultButton(QMessageBox::No);
                    mb.setButtonText(QMessageBox::Yes, "Да");
                    mb.setButtonText(QMessageBox::No, "Нет");

                    int res = mb.exec();
                    if (res == QMessageBox::Yes)
                    {
                        QString filename = QFileDialog::getSaveFileName(this, "Save File", pwtd->getLableName(), "Text Files (*.txt)");
                        if (!filename.isEmpty())
                        {
                            QFile file(filename);
                            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                            {
                                QTextStream out(&file);
                                out << pwtd->getTextPlainText();
                                file.close();
                            } else {
                                ui->plainTextEdit->appendPlainText("Неудалось сохранить файл.");
                            }
                        }
                    }
                }

            } else if (m_widgets[i].type == window_type::TABLE_DOCUMENT) {

                widget_table_document *pwtd = dynamic_cast<widget_table_document*>(ui->mdiArea->activeSubWindow()->widget());
                file_is_changed = pwtd->getFileState();
                if (file_is_changed)
                {
                    QMessageBox mb;
                    mb.setText("Сохранить файл?");
                    mb.setWindowTitle(" ");
                    mb.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    mb.setDefaultButton(QMessageBox::No);
                    mb.setButtonText(QMessageBox::Yes, "Да");
                    mb.setButtonText(QMessageBox::No, "Нет");

                    int res = mb.exec();
                    if (res == QMessageBox::Yes)
                    {
                        QString filename = QFileDialog::getSaveFileName(this, "Save File", pwtd->getLableName(), "Table Files (*.xls)");
                        if (!filename.isEmpty())
                        {
                            QFile file(filename);
                            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                            {
                                QTextStream out(&file);
                                //out << pwtd->getTextPlainText();
                                file.close();
                            } else {
                                ui->plainTextEdit->appendPlainText("Неудалось сохранить файл.");
                            }
                        }
                    }
                }

            } else {

            }

            m_widgets[i].pWidget->close();
            delete m_widgets[i].pButton;
            m_widgets.remove(i);
        }
    }
}


void KCRM::on_actionNewFile_triggered()
{
    bool flag = false;
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i].type == window_type::CREATE_FILE)
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
        QRandomGenerator generator;
        qint32 id = generator.generate() & std::numeric_limits<qint32>::max();
        m_widgets.push_back(window_content(id, window_type::CREATE_FILE, sub_window, nullptr));
        sub_window->setAttribute(Qt::WA_DeleteOnClose);

        int x = (ui->mdiArea->rect().width() - 200) / 2;
        int y = (ui->mdiArea->rect().height() - 300) / 2;
        sub_window->move(x,y);
        sub_window->setFixedSize(200, 300);
        sub_window->show();


        connect(m_wcf.pushButton_2, &QPushButton::clicked, this, &KCRM::create_text_document);
        connect(m_wcf.pushButton_3, &QPushButton::clicked, this, &KCRM::create_table_document);
        connect(m_wcf.pushButton, &QPushButton::clicked, this, [=]()
        {
            sub_window->close();
            for (size_t i = 0; i < m_widgets.size(); i++)
            {
                if (m_widgets[i].type == window_type::CREATE_FILE)
                {
                    m_widgets.remove(i);
                }
            }
        });
    }
}


void KCRM::on_actionOpenFile_triggered()
{
   for (size_t i = 0; i < m_widgets.size(); i++)
   {
       if (m_widgets[i].type == window_type::CREATE_FILE)
       {
           m_widgets[i].pWidget->close();
           m_widgets.remove(i);
       }
   }
   QString filename = QFileDialog::getOpenFileName(this, "Выбор файла", QDir::homePath());
   if (!filename.isEmpty())
   {
       QFileInfo fileInfo(filename);
       QString extension = fileInfo.suffix();
       if (extension == "txt")
       {
           QWidget* text_document = new widget_text_document(this);
           QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(text_document, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
           qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
           QPushButton* button = new QPushButton();
           button->setText(fileInfo.fileName());
           m_widgets.push_back(window_content(id ,window_type::TEXT_DOCUMENT, sub_window, button));
           sub_window->setAttribute(Qt::WA_DeleteOnClose);
           int x = (ui->mdiArea->rect().width() - 500) / 2;
           int y = (ui->mdiArea->rect().height() - 400) / 2;
           sub_window->move(x,y);
           sub_window->show();

           widget_text_document *pwtd = dynamic_cast<widget_text_document*>(text_document);
           pwtd->setLableName(fileInfo.fileName());

           QFile file(filename);
           if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           {
               ui->plainTextEdit->appendPlainText("Невозможно открыть файл: " + fileInfo.fileName());
           } else
           {
               QTextStream ReadFile(&file);
               pwtd->setText(ReadFile.readAll());
               pwtd->changeFileChangedState();
           }

           connect(dynamic_cast<widget_text_document*>(text_document),
                   &widget_text_document::signal_window_minimized,
                   this,
                   [=](){
                       window_minimized(id);
                   });

           connect(dynamic_cast<widget_text_document*>(text_document),
                   &widget_text_document::signal_window_close,
                   this,
                   [=](){
                      window_close(id);
                   });

       } else if (extension == "xlsx" || extension == "xls")
       {

       } else
       {
           ui->plainTextEdit->appendPlainText("Неизвестное расширение файла: " + extension);
       }


   }
}


void KCRM::on_actionSaveFile_triggered()
{    
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i].pWidget->widget() == ui->mdiArea->activeSubWindow()->widget())
        {
            if (m_widgets[i].type == window_type::TEXT_DOCUMENT ||
                    m_widgets[i].type == window_type::TABLE_DOCUMENT)
            {
                widget_text_document *pwtd = dynamic_cast<widget_text_document*>(m_widgets[i].pWidget->widget());
                QString suffix;
                if ( m_widgets[i].type == window_type::TEXT_DOCUMENT )
                    suffix = "Text Files (*.txt)";
                else if (m_widgets[i].type == window_type::TABLE_DOCUMENT)
                    suffix = "Table Files (*.xls)";
                else {

                }

                QString filename = QFileDialog::getSaveFileName(this, "Save File", pwtd->getLableName(), suffix);
                if (!filename.isEmpty())
                {
                    QFile file(filename);
                    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        QTextStream out(&file);
                        out << pwtd->getTextPlainText();

                        QFileInfo fileInfo(file.fileName());

                        file.close();
                        m_widgets[i].pWidget->close();
                        delete m_widgets[i].pButton;
                        m_widgets.remove(i);

                        QString extension = fileInfo.suffix();
                        if (extension == "txt")
                        {
                            QWidget* text_document = new widget_text_document(this);
                            QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(text_document, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
                            qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
                            QPushButton* button = new QPushButton();
                            button->setText(fileInfo.fileName());
                            m_widgets.push_back(window_content(id ,window_type::TEXT_DOCUMENT, sub_window, button));
                            sub_window->setAttribute(Qt::WA_DeleteOnClose);
                            int x = (ui->mdiArea->rect().width() - 500) / 2;
                            int y = (ui->mdiArea->rect().height() - 400) / 2;
                            sub_window->move(x,y);
                            sub_window->show();

                            widget_text_document *pwtd = dynamic_cast<widget_text_document*>(text_document);
                            pwtd->setLableName(fileInfo.fileName());

                            QFile file(filename);
                            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                            {
                                ui->plainTextEdit->appendPlainText("Невозможно открыть файл: " + fileInfo.fileName());
                            } else
                            {
                                QTextStream ReadFile(&file);
                                pwtd->setText(ReadFile.readAll());
                                pwtd->changeFileChangedState();
                            }

                            connect(dynamic_cast<widget_text_document*>(text_document),
                                    &widget_text_document::signal_window_minimized,
                                    this,
                                    [=](){
                                        window_minimized(id);
                                    });

                            connect(dynamic_cast<widget_text_document*>(text_document),
                                    &widget_text_document::signal_window_close,
                                    this,
                                    [=](){
                                       window_close(id);
                                    });
                        } else if (extension == "xlsx" || extension == "xls")
                        {

                        } else
                        {

                        }




                    } else {
                        ui->plainTextEdit->appendPlainText("Неудалось сохранить файл.");
                    }
                }
            }else {

            }

            }

    }


}


void KCRM::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{

}




void KCRM::on_action_triggered()
{
    on_actionNewFile_triggered();
}


void KCRM::on_action_2_triggered()
{
    on_actionOpenFile_triggered();
}


void KCRM::on_action_3_triggered()
{
    on_actionSaveFile_triggered();
}

