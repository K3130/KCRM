#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QDebug>

enum class TYPE_FIELD
{
    INTEGER,
    DECIMAL,
    TINYINT,
    BOOL,
    FLOAT,
    TEXT,
    VARCHAR_255,
    VARCHAR_30,
    DATE,
    TIME,
    DATETIME,
    BLOB,
    LARGEBLOB
};

static const char *T_F[] =
    { "INTEGER", "DECIMAL", "TINYINT",
      "BOOL" , "FLOAT", "TEXT", "VARCHAR(255)",
      "VARCHAR(30)", "DATE", "TIME", "DATETIME", "BLOB", "LARGEBLOB" };

enum class ATTRIBUTES_CONSTRAINTS
{
    NO_ATTR,
    PRIMARY_KEY,
    NOT_NULL,
    DEFAULT,
    AUTO_INCREMENT,
    PRIMARY_KEY_AUTOINCREMENT,
    UNIQUE
};

static const char *A_C[] =
    { "", "PRIMARY KEY", "NOT NULL", "DEFAULT",
          "AUTO_INCREMENT", "PRIMARY KEY AUTOINCREMENT", "UNIQUE" };

struct ColumnSettings
{
    TYPE_FIELD m_type;
    ATTRIBUTES_CONSTRAINTS m_attr;
    QString m_columnName;
};

/*!
 * API для работы с базой postgres SQL
 * \author Konstantin Smirnov
 * \brief The data_base class
 */

class data_base : public QObject
{
    Q_OBJECT
public:
    data_base();
    /*!
     * \brief Открытие базы
     */
    bool openDataBase(QSqlDatabase &aDataBase,
                      const QString &aFileName,
                      const QString &aHostName,
                      quint32 aPort,
                      const QString &aUserName,
                      const QString &aPassword);
    /*!
     * \brief Закрытие базы
     */
    bool closeDataBase(QSqlDatabase &aDataBase, const QString &aFileName);
    /*!
     * \brief Создание таблицы с произвольным количеством столбцов
     */
    bool createTable(QSqlDatabase &aDataBase,
                     const QString &aTableName,
                     const QVector<ColumnSettings> &aColumns);
    /*!
     * \brief Вставка строки в базу
     */
    bool InsertRow(QSqlDatabase &aDataBase,
                   const QString &aTableName,
                   const QVector<QString> &aColumns,
                   const QVector<QVariant> &aValues);
    /*!
     * \brief Вернуть последнюю ошибку
     */
    QString getLastError() { return m_last_error; }
    /*!
     * \brief Произвольный запрос
     */
    bool randomQuery(QSqlDatabase &aDataBase, const QString &aQuery);
    /*!
     * \brief Произвольный запрос, получить значение из таблицы
     */
    QVariant randomQueryGetValue(QSqlDatabase &aDataBase, const QString &aQuery);
    /*!
     * \brief Получить все значения из одного столбца
     */
    QVector<QVariant> getAllValuesOfOneColumn(QSqlDatabase &aDataBase, const QString &aNameTable, const QString &aNameColumn);
private:
    QString m_last_error;
};

#endif // DATA_BASE_H
