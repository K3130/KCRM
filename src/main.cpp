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
    }
    else
    {
        logon.set_network_name(db.get_host_string());
        logon.set_port_num(db.get_port_string());

        if(!logon.check_users())
        {
            qDebug() << "Users not found, generate.";
        }
    }


    return a.exec();
}
