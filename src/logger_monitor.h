#ifndef LOGGER_MONITOR_H
#define LOGGER_MONITOR_H

#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QLoggingCategory>

/*!
 * \author Konstantin Smirnov
 * Основной логер монитор, не разделенный лог, в будующем надо разделять конечно.
 */
namespace logger_monitor
{
    Q_DECLARE_LOGGING_CATEGORY(logDebug)
    Q_DECLARE_LOGGING_CATEGORY(logInfo)
    Q_DECLARE_LOGGING_CATEGORY(logWarning)
    Q_DECLARE_LOGGING_CATEGORY(logCritical)

    void messageHandler(QtMsgType aType, const QMessageLogContext &aContext, const QString &aMsg);
}

#endif // LOGGER_MONITOR_H
