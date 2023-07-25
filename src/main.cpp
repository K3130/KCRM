#include "kcrm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KCRM w;
    w.show();
    return a.exec();
}
