#ifndef WIDGET_LOGON_H
#define WIDGET_LOGON_H

#include <QWidget>

/*
 * Виджет входа в систему.
*/

namespace Ui {
class widget_logon;
}

class widget_logon : public QWidget
{
    Q_OBJECT

public:
    explicit widget_logon(QWidget *parent = nullptr);
    ~widget_logon();

private slots:
    void on_pushButton_clicked();


private:
    Ui::widget_logon *ui;

private:
    bool verify();
signals:
    void verify_succes();

};

#endif // WIDGET_LOGON_H
