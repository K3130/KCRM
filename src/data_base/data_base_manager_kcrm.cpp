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
