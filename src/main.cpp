#include "widget_logon.h"
#include "kcrm.h"
#include <QApplication>

void open_kcrm()
{
    KCRM w;
    w.show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Auth
    widget_logon logon;
    logon.show();
    QObject::connect(&logon, &widget_logon::verify_succes, open_kcrm);



    return a.exec();
}
