#include "widget_logon.h"
#include "kcrm.h"
#include "data_base/data_base_manager_kcrm.h"
#include <QApplication>
#include <QMessageBox>

void open_kcrm()
{
    KCRM w;
    w.show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    widget_logon logon;
    logon.show();

    data_base_manager_kcrm db;
    if(!db.authorization())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Нет связи с БД.", QMessageBox::Ok);
    }
    else
    {
        logon.set_network_name(db.get_host_string());
        logon.set_port_num(db.get_port_string());

        db.check_user_tables();
    }






    return a.exec();
}
