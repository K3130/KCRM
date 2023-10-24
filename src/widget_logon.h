#ifndef WIDGET_LOGON_H
#define WIDGET_LOGON_H

#include "kcrm.h"
#include "data_base/data_base_manager_kcrm.h"
#include <QWidget>
#include <QMessageBox>

namespace Ui {
class widget_logon;
}
/*!
 * Виджет авторизации
 * \author Konstantin Smirnov
 * \brief The widget_logon class
 */
class widget_logon : public QWidget
{
    Q_OBJECT

public:
    explicit widget_logon(data_base_manager_kcrm *aDbManager,
                          QWidget *parent = nullptr);
    ~widget_logon();
    void set_network_name(const QString& aAddr);
    void set_port_num(const QString& aPort);
    bool check_users();
    bool authorization();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::widget_logon *ui;
    data_base_manager_kcrm *m_dbmk;
    KCRM m_kcrm;

};

#endif // WIDGET_LOGON_H
