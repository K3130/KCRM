#ifndef DATA_BASE_MANAGER_KCRM_H
#define DATA_BASE_MANAGER_KCRM_H

#include "data_base.h"
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
/*!
 * \author Konstantin Smirnov
 * \brief Класс для взаимодействия с базой
*/

class data_base_manager_kcrm : public QObject
{
    Q_OBJECT
public:
    data_base_manager_kcrm();
    /*!
     * Подключение к серверу БД
     * \brief authorization
     * \return результат проверки.
     */
    bool authorization();
    /*!
     * Проверяет есть ли в базе таблица users
     * если ее нет, создает таблицу и
     * пользователя Admin по умолчанию
     * \brief check_user_tables
     * \return результат проверки.
     */
    bool check_user_tables();
    /*!
     * Проверка пользователя и пароля
     * \brief user_verify
     * \return результат проверки
     */
    bool user_verify(const QString &aLogin, const QString &aPass);
    bool add_new_user(const QString &aLogin, const QString &aPass,
                      const QString &aRole, const QString &aPosition);
    void delete_user(const QString &aLogin);
    QString get_host_string() {return m_host;}
    QString get_port_string() {return m_port;}

public:
    QString get_user_role(const QString& aLogin);
    QVector<QString> get_all_users_name();
    QVector<QString> get_all_users_role();
    QVector<QString> get_all_users_position();
private:
    data_base m_db;
    QSqlDatabase m_qsdb;
    QString m_host;
    QString m_port;
};

#endif // DATA_BASE_MANAGER_KCRM_H
