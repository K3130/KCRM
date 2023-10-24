#include "data_base.h"

QString convertTypeFieldToString(int aVal)
{
    QString enumToStr(T_F[aVal]);
    return enumToStr;
}


QString convertAttrConstToString(int aVal)
{
    QString enumToStr(A_C[aVal]);
    return enumToStr;
}

data_base::data_base()
{

}

bool data_base::openDataBase(QSqlDatabase &aDataBase, const QString &aFileName, const QString &aHostName, quint32 aPort, const QString &aUserName, const QString &aPassword)
{
    aDataBase = QSqlDatabase::addDatabase("QPSQL");
    aDataBase.setDatabaseName(aFileName);
    aDataBase.setHostName(aHostName);
    aDataBase.setPort(aPort);
    aDataBase.setUserName(aUserName);
    aDataBase.setPassword(aPassword);
    if(!aDataBase.open())
    {
        m_last_error = aDataBase.lastError().text();
        return false;
    }
    return true;
}

bool data_base::closeDataBase(QSqlDatabase &aDataBase, const QString &aFileName)
{
    aDataBase.close();
    QSqlDatabase::removeDatabase(aFileName);
    return true;
}

bool data_base::createTable(QSqlDatabase &aDataBase, const QString &aTableName, const QVector<ColumnSettings> &aColumns)
{
    QSqlQuery query(aDataBase);

    QString str = "CREATE TABLE " + aTableName + " (";

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        str += "    ";
        str += aColumns[i].m_columnName + "    "
               + convertTypeFieldToString((int)aColumns[i].m_type) + "     "
               + convertAttrConstToString((int)aColumns[i].m_attr) + ",";
    }

    str.chop(1);
    str += ");";

    if(!query.exec(str))
    {
        m_last_error =  query.lastError().text();
        return false;
    }
    return true;
}

bool data_base::InsertRow(QSqlDatabase &aDataBase, const QString &aTableName, const QVector<QString> &aColumns, const QVector<QVariant> &aValues)
{
    if (aColumns.size() != aValues.size())
    {
        qDebug() <<  "Quantities and values are not equal!";
        return false;
    }

    QSqlQuery query(aDataBase);

    QString str = "INSERT INTO " + aTableName + "(";

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        str += " ";
        str += aColumns[i] + ",";
    }
    str.chop(1);
    str += ") ";
    str += "   VALUES(";

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        str += ":" + aColumns[i]  + ",";
    }
    str.chop(1);
    str += ")";

    query.prepare(str);

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        query.bindValue(":" + aColumns[i], aValues[i]);
    }

    if(!query.exec())
    {
        qDebug() <<  query.lastError().text() << '\n' << query.lastQuery();
        return false;
    }
    qDebug() << "Insert row: " << aTableName << Qt::endl;

    return true;
}

bool data_base::randomQuery(QSqlDatabase &aDataBase, const QString &aQuery)
{
    QSqlQuery query(aDataBase);

    if(!query.exec(aQuery))
    {
        qDebug() <<  query.lastError().text() << '\n' << query.lastQuery();
        return false;
    }

    if(!query.next())
    {
        return false;
    }

    qDebug() << "Random query successfully: " << query.lastQuery() << Qt::endl;
    return true;
}
