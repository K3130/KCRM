#ifndef WIDGET_LOGON_H
#define WIDGET_LOGON_H

#include <QWidget>

namespace Ui {
class widget_logon;
}

class widget_logon : public QWidget
{
    Q_OBJECT

public:
    explicit widget_logon(QWidget *parent = nullptr);
    ~widget_logon();

private:
    Ui::widget_logon *ui;
};

#endif // WIDGET_LOGON_H
