#include "kcrm.h"

KCRM::KCRM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KCRM)
{
    ui->setupUi(this);
    ui->mdiArea->viewport()->setMouseTracking(true);

    qInstallMessageHandler(logger_monitor::messageHandler);
}

KCRM::~KCRM()
{
    delete ui;
}

void KCRM::set_user_role(const QString &aRole)
{
    // Разрешено все что не запрещено.
    if (aRole == "admin") {
        m_role = user_role::ADMIN_USER;
    }
    else if (aRole == "manager") {
        m_role = user_role::MANAGER_USER;
        // Ограничения менеджеров
    }
    else
    {
        m_role = user_role::OTHER_USER;
        // Ограничение всех пользователей
    }
}

void KCRM::set_data_base_manager(data_base_manager_kcrm *aDbmk)
{
    m_dbmk = aDbmk;
}

void KCRM::create_text_document()
{
    QWidget* text_document = new widget_text_document(this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(text_document, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
    QPushButton* button = new QPushButton();
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
                button->setText(dynamic_cast<widget_text_document*>(text_document)->getLableName());
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
    QWidget* table_document = new widget_table_document(this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(table_document, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
    QPushButton* button = new QPushButton();
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
                button->setText(dynamic_cast<widget_table_document*>(table_document)->getLableName());
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

void KCRM::window_resize(qint32 id)
{
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if(m_widgets[i].id == id)
        {
            if (!m_widgets[i].pWidget->isMinimized())
            {
                QSize mdiAreaSize = ui->mdiArea->size();
                int width = mdiAreaSize.width();
                int height = mdiAreaSize.height();
                m_widgets[i].pWidget->resize(width, height);
            }
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

             } else if (m_widgets[i].type == window_type::TABLE_DOCUMENT) {
                widget_table_document *pwtd = dynamic_cast<widget_table_document*>(ui->mdiArea->activeSubWindow()->widget());
                file_is_changed = pwtd->getFileState();
             } else {
             }

            if (file_is_changed)
            {
                QMessageBox mb(this);
                mb.setText("Сохранить файл?");
                mb.setWindowTitle(" ");
                mb.addButton("Да", QMessageBox::YesRole);
                mb.addButton("Нет", QMessageBox::NoRole);

                int res = mb.exec();
                if (res == QMessageBox::Yes)
                {
                    on_actionSaveFile_triggered();
                }
            }

            m_widgets[i].pWidget->close();
            delete m_widgets[i].pButton;
            m_widgets.remove(i);
        }
    }
}


void KCRM::on_actionNewFile_triggered()
{
    if (m_if_one_new_file_widget)
    {
        return;
    }
    else
    {
        m_if_one_new_file_widget = true;
        QWidget* createnewfile = new QWidget(this);
        m_wcf.setupUi(createnewfile);

        QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(createnewfile, Qt::FramelessWindowHint |
                                                             Qt::CustomizeWindowHint);
        m_widgets.push_back(window_content(0, window_type::CREATE_FILE, sub_window, nullptr));
        sub_window->setAttribute(Qt::WA_DeleteOnClose);

        int x = (ui->mdiArea->rect().width() - 200) / 2;
        int y = (ui->mdiArea->rect().height() - 300) / 2;
        sub_window->move(x,y);
        sub_window->setFixedSize(200, 300);
        sub_window->show();


        connect(m_wcf.pushButton_2, &QPushButton::clicked, this, [=]()
        {
            create_text_document();
            m_if_one_new_file_widget = false;
            sub_window->close();
            for (size_t i = 0; i < m_widgets.size(); i++)
            {
                if (m_widgets[i].type == window_type::CREATE_FILE)
                {
                    m_widgets.remove(i);
                }
            }
        });
        connect(m_wcf.pushButton_3, &QPushButton::clicked, this, [=]()
        {
            create_table_document();
            m_if_one_new_file_widget = false;
            sub_window->close();
            for (size_t i = 0; i < m_widgets.size(); i++)
            {
                if (m_widgets[i].type == window_type::CREATE_FILE)
                {
                    m_widgets.remove(i);
                }
            }
        });
        connect(m_wcf.pushButton, &QPushButton::clicked, this, [=]()
        {
            m_if_one_new_file_widget = false;
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
       if (extension == "txt" || extension == "log")
       {          
           create_text_document();
           widget_text_document *pwtd = dynamic_cast<widget_text_document*>(ui->mdiArea->activeSubWindow()->widget());

           QFile file(filename);
           if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           {
               qDebug(logger_monitor::logDebug()) << "Невозможно открыть файл: " + fileInfo.fileName();
               ui->plainTextEdit->appendPlainText("Невозможно открыть файл: " + fileInfo.fileName());
           } else
           {
               QTextStream ReadFile(&file);
               pwtd->setText(ReadFile.readAll());
               pwtd->changeFileChangedState();
               pwtd->setLableName(fileInfo.fileName());
               qDebug(logger_monitor::logDebug()) << "Открыт файл: " + fileInfo.fileName();
           }
       } else if (extension == "xlsx")
       {
           create_table_document();
           widget_table_document *pwtd = dynamic_cast<widget_table_document*>(ui->mdiArea->activeSubWindow()->widget());

           QXlsx::Document xlsx(filename);

           const int rowCount = xlsx.dimension().rowCount();
           const int columnCount = xlsx.dimension().columnCount();

           for (int row = 1; row <= rowCount; ++row)
           {
               QModelIndex parentIndex = pwtd->getModel()->index(row -1, 0);
               for (int col = 1; col <= columnCount; ++col)
               {
                   QString cellValue = xlsx.read(row, col).toString();
                   QModelIndex index = pwtd->getModel()->index(row - 1, col -1, parentIndex);
                   pwtd->getModel()->setData(index, cellValue);
                }
            }
            pwtd->changeFileChangedState();
            pwtd->setLableName(fileInfo.fileName());

       } else
       {
           ui->plainTextEdit->appendPlainText("Неподдерживаемое расширение файла: " + extension);
           qDebug(logger_monitor::logDebug()) << "Неподдерживаемое расширение файла: " + extension;
       }


   }
}


void KCRM::on_actionSaveFile_triggered()
{    
    for (size_t i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i].pWidget->widget() == ui->mdiArea->activeSubWindow()->widget())
        {
            if (m_widgets[i].type == window_type::TEXT_DOCUMENT)
            {
                widget_text_document *pwtd = dynamic_cast<widget_text_document*>(m_widgets[i].pWidget->widget());
                QString suffix = "Text Files (*.txt)";
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

                        pwtd->setLableName(fileInfo.fileName());
                    } else {
                        ui->plainTextEdit->appendPlainText("Неудалось сохранить файл.");
                        qDebug(logger_monitor::logDebug()) << "Неудалось сохранить файл.";
                    }
                }
            }

            if (m_widgets[i].type == window_type::TABLE_DOCUMENT)
            {
                widget_table_document *pwtd = dynamic_cast<widget_table_document*>(m_widgets[i].pWidget->widget());
                QString suffix = "Table Files (*.xlsx)";
                QString filename = QFileDialog::getSaveFileName(this, "Save File", pwtd->getLableName(), suffix);
                QFileInfo fileInfo(filename);
                if (!filename.isEmpty())
                {
                    QXlsx::Document xlsx;
                    for(int row = 0; row < pwtd->getModel()->rowCount(); row++)
                    {
                        for(int col = 0; col < pwtd->getModel()->columnCount(); col++)
                        {
                            QModelIndex index = pwtd->getModel()->index(row, col);
                            QVariant value = pwtd->getModel()->data(index);
                            QString strValue = value.toString();
                            int excelRow = row + 2; // Нумерация строк в Excel начинается с 1
                            int excelCol = col + 1; // Нумерация колонок в Excel начинается с 1
                            xlsx.write(excelRow, excelCol, strValue);
                        }
                    }
                    xlsx.saveAs(filename);
                    pwtd->setLableName(fileInfo.fileName());

                }

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

void KCRM::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    emit windowResized();
}


void KCRM::on_actionprintDocument_triggered()
{
    if (ui->mdiArea->activeSubWindow() && m_if_one_new_file_widget == false)
    {
        QPrinter printer;
        QPrintDialog dialog(&printer, this);
        if (dialog.exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);
            ui->mdiArea->activeSubWindow()->widget()->render(&painter);
        }
    }

}


void KCRM::on_actiontelegram_triggered()
{
    if (m_if_telegram_open)
    {
        ui->plainTextEdit->appendPlainText("Телеграм уже открыт.");
        return;
    }
    else
    {
        m_if_telegram_open = true;
        QWidget* telegram = new widget_telegram(this);
        QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(telegram, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
        qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
        QPushButton* button = new QPushButton();
        m_widgets.push_back(window_content(id ,window_type::OTHER, sub_window, button));
        sub_window->setAttribute(Qt::WA_DeleteOnClose);
        //Приклеиваем телеграм к правой стороне на всю высоту
        QRect mdiRect = ui->mdiArea->geometry();
        QRect subWindowRect = sub_window->geometry();
        int newX = mdiRect.right() - subWindowRect.width();
        int newY = subWindowRect.y();
        int newHeight = mdiRect.height();
        sub_window->setGeometry(newX, newY, subWindowRect.width(), newHeight);

        sub_window->show();

        connect(dynamic_cast<widget_telegram*>(telegram),
                &widget_telegram::signal_window_minimized,
                this,
                [=](){
                    button->setText(dynamic_cast<widget_telegram*>(telegram)->getLableName());
                    window_minimized(id);
                });

        connect(dynamic_cast<widget_telegram*>(telegram),
                &widget_telegram::signal_window_close,
                this,
                [=](){
                    m_if_telegram_open = false;
                    window_close(id);
                });
        //Обновляем размеры телеграм при изменении размеров главного окна
        connect(this, &KCRM::windowResized,
                this,
                [=](){
                    QRect mdiRect = ui->mdiArea->geometry();
                    QRect subWindowRect = sub_window->geometry();
                    int newX = mdiRect.right() - subWindowRect.width();
                    int newY = subWindowRect.y();
                    int newHeight = mdiRect.height();
                    sub_window->setGeometry(newX, newY, subWindowRect.width(), newHeight);
                });

    }


}

void KCRM::on_action_5_triggered()
{
    QWidget* users_table = new widget_users(m_dbmk, this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(users_table, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
    QPushButton* button = new QPushButton();
    m_widgets.push_back(window_content(id ,window_type::OTHER, sub_window, button));
    sub_window->setAttribute(Qt::WA_DeleteOnClose);
    int x = (ui->mdiArea->rect().width() - 500) / 2;
    int y = (ui->mdiArea->rect().height() - 400) / 2;
    sub_window->move(x,y);
    sub_window->show();

    connect(dynamic_cast<widget_users*>(users_table),
            &widget_users::signal_window_minimized,
            this,
            [=](){
                button->setText(dynamic_cast<widget_users*>(users_table)->getLableName());
                window_minimized(id);
            });

    connect(dynamic_cast<widget_users*>(users_table),
            &widget_users::signal_window_close,
            this,
            [=](){
                window_close(id);
            });
}


void KCRM::on_actionai_triggered()
{
    QWidget* ai_control = new widget_ai(this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(ai_control, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
    QPushButton* button = new QPushButton();
    m_widgets.push_back(window_content(id ,window_type::OTHER, sub_window, button));
    sub_window->setAttribute(Qt::WA_DeleteOnClose);
    //Сразу на всю область
    QSize mdiAreaSize = ui->mdiArea->size();
    int width = mdiAreaSize.width();
    int height = mdiAreaSize.height();
    sub_window->resize(width, height);
    sub_window->show();

    connect(dynamic_cast<widget_ai*>(ai_control),
            &widget_ai::signal_window_minimized,
            this,
            [=](){
                button->setText(dynamic_cast<widget_ai*>(ai_control)->getLableName());
                window_minimized(id);
            });

    connect(dynamic_cast<widget_ai*>(ai_control),
            &widget_ai::signal_window_close,
            this,
            [=](){
                window_close(id);
            });
    //Обновляем размеры при изменении размеров главного окна
    connect(this, &KCRM::windowResized,
            this,
            [=](){
                window_resize(id);
            });
}


void KCRM::on_actionwarehouse_triggered()
{
    QWidget* wh_widget = new widget_wh(m_dbmk, this);
    QMdiSubWindow* sub_window = ui->mdiArea->addSubWindow(wh_widget, Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    qint32 id = QRandomGenerator::global()->bounded(0, 853323747);
    QPushButton* button = new QPushButton();
    m_widgets.push_back(window_content(id ,window_type::OTHER, sub_window, button));
    sub_window->setAttribute(Qt::WA_DeleteOnClose);
    int x = (ui->mdiArea->rect().width() - 500) / 2;
    int y = (ui->mdiArea->rect().height() - 400) / 2;
    sub_window->move(x,y);
    sub_window->show();

    connect(dynamic_cast<widget_wh*>(wh_widget),
            &widget_wh::signal_window_minimized,
            this,
            [=](){
                button->setText(dynamic_cast<widget_wh*>(wh_widget)->getLableName());
                window_minimized(id);
            });

    connect(dynamic_cast<widget_wh*>(wh_widget),
            &widget_wh::signal_window_close,
            this,
            [=](){
                window_close(id);
            });

}

