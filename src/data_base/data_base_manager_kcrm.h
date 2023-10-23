#ifndef DATA_BASE_MANAGER_KCRM_H
#define DATA_BASE_MANAGER_KCRM_H

#include "data_base.h"
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
/*
 * Класс для взаимодействия с базой
*/

class data_base_manager_kcrm : public QObject
{
    Q_OBJECT
public:
    data_base_manager_kcrm();
    bool authorization();
    bool check_user_tables();
    QString get_host_string() {return m_host;}
    QString get_port_string() {return m_port;}
private:
    data_base m_db;
    QSqlDatabase m_qsdb;
    QString m_host;
    QString m_port;
};

#endif // DATA_BASE_MANAGER_KCRM_H
