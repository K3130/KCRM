#include "widget_logon.h"
#include "kcrm.h"
#include "data_base/data_base_manager_kcrm.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    data_base_manager_kcrm db;
    widget_logon logon(&db);
    logon.show();

    if(!logon.authorization())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Нет связи с БД.", QMessageBox::Ok);
        qDebug(logger_monitor::logDebug()) << "Ошибка. Нет связи с БД.";
    }
    else
    {
        qDebug(logger_monitor::logDebug()) << "Связь с БД установленна. ";
        logon.set_network_name(db.get_host_string());
        logon.set_port_num(db.get_port_string());

        if(!logon.check_users())
        {
            qDebug(logger_monitor::logDebug()) << "Пользователь по умолчанию не найден, будет создан по умолчанию.";
        }
        else
        {
            qDebug(logger_monitor::logDebug()) << "Пользователь по умолчанию найден.";
        }
    }


    return a.exec();
}
