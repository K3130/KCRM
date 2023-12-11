#include "data_base_manager_kcrm.h"

data_base_manager_kcrm::data_base_manager_kcrm()
{

}

bool data_base_manager_kcrm::authorization()
{
    QFile file("./network_settings.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Json file couldn't found";
        return false;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();
    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);

    if(parseError.error != QJsonParseError::NoError)
    {
        qDebug() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return false;
    }
    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();

    if(!m_db.openDataBase(m_qsdb, jsonObj.value("db_name").toString(),
                           jsonObj.value("db_host").toString(),
                           jsonObj.value("db_port").toString().toInt(),
                           jsonObj.value("db_login").toString(),
                           jsonObj.value("db_pass").toString()))
    {
        qDebug() << "Error open db: " << m_db.getLastError();
        return false;
    }
    m_host = jsonObj.value("db_host").toString();
    m_port = jsonObj.value("db_port").toString();
    return true;
}

bool data_base_manager_kcrm::check_user_tables()
{
    if(!m_qsdb.tables().contains(QLatin1String("users")))
    {
        QVector<ColumnSettings> columns;
        ColumnSettings c1;
        c1.m_type = TYPE_FIELD::TEXT;
        c1.m_attr = ATTRIBUTES_CONSTRAINTS::UNIQUE;
        c1.m_columnName = "Login";
        columns.push_back(c1);

        ColumnSettings c2;
        c2.m_type = TYPE_FIELD::TEXT;
        c2.m_attr = ATTRIBUTES_CONSTRAINTS::NOT_NULL;
        c2.m_columnName = "Password";
        columns.push_back(c2);

        ColumnSettings c3;
        c3.m_type = TYPE_FIELD::TEXT;
        c3.m_attr = ATTRIBUTES_CONSTRAINTS::NOT_NULL;
        c3.m_columnName = "Role";
        columns.push_back(c3);

        ColumnSettings c4;
        c4.m_type = TYPE_FIELD::TEXT;
        c4.m_attr = ATTRIBUTES_CONSTRAINTS::NOT_NULL;
        c4.m_columnName = "Position";
        columns.push_back(c4);

        if(!m_db.createTable(m_qsdb, "users", columns))
        {
            qDebug() << "table not create";
        }

        QVector<QString> col{"Login", "Password", "Role", "Position"};
        QVector<QVariant> row{"Admin", "kcrm", "admin", "Administrator"};
        if(!m_db.InsertRow(m_qsdb, "users", col, row))
        {
            qDebug() << "user no create";
        }

        qDebug() << "not contains";
    }
    return true;
}

bool data_base_manager_kcrm::user_verify(const QString& aLogin, const QString& aPass)
{
    QString query = QString("SELECT * FROM users WHERE login = '%1' AND password = '%2'")
                           .arg(aLogin)
                           .arg(aPass);
    if(!m_db.randomQuery(m_qsdb, query))
    {
        qDebug() << "Error authorization from " << aLogin;
        return false;
    }
    return true;
}

QString data_base_manager_kcrm::get_user_role(const QString& aLogin)
{
    QString query = QString("SELECT role FROM users WHERE login = '%1'").arg(aLogin);
    return m_db.randomQueryGetValue(m_qsdb, query).toString();
}

QVector<QString> data_base_manager_kcrm::get_all_users_name()
{
    QVector<QString> names;
    QVector<QVariant> v = m_db.getAllValuesOfOneColumn(m_qsdb, "users", "login");
    for (size_t i = 0; i < v.size(); i++) {
        names.push_back(v[i].toString());
    }
    return names;
}

QVector<QString> data_base_manager_kcrm::get_all_users_role()
{
    QVector<QString> roles;
    QVector<QVariant> v = m_db.getAllValuesOfOneColumn(m_qsdb, "users", "role");
    for (size_t i = 0; i < v.size(); i++) {
        roles.push_back(v[i].toString());
    }
    return roles;
}

QVector<QString> data_base_manager_kcrm::get_all_users_position()
{
    QVector<QString> pos;
    QVector<QVariant> v = m_db.getAllValuesOfOneColumn(m_qsdb, "users", "position");
    for (size_t i = 0; i < v.size(); i++) {
        pos.push_back(v[i].toString());
    }
    return pos;
}

bool data_base_manager_kcrm::add_new_user(const QString &aLogin, const QString &aPass, const QString &aRole, const QString &aPosition)
{
    QVector<QString> col{"Login", "Password", "Role", "Position"};
    QVector<QVariant> row{aLogin, aPass, aRole, aPosition};

    if(!m_db.InsertRow(m_qsdb, "users", col, row))
    {
        qWarning() << m_db.getLastError();
        return false;
    }
    return true;
}

void data_base_manager_kcrm::delete_user(const QString &aLogin)
{
    QString query = QString("DELETE FROM users WHERE login = '%1'")
                        .arg(aLogin);
    m_db.randomQuery(m_qsdb, query);
}
























