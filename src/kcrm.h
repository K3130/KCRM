#ifndef KCRM_H
#define KCRM_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QRandomGenerator>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include "ui_widget_create_file.h"
#include "widget_create_file.h"
#include "widget_text_document.h"
#include "ui_widget_text_document.h"
#include "widget_table_document.h"
#include "ui_widget_table_document.h"
#include "./ui_kcrm.h"
#include "widget_telegram/widget_telegram.h"
#include "data_base/data_base_manager_kcrm.h"
#include "logger_monitor.h"
#include "other_widgets/widget_users.hpp"
#include "other_widgets/widget_ai.hpp"

//xls
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx;
//--

/*
 * Главный виджет. QMdiArea в которой запускаются остальные виджеты subwindow.
*/

enum class window_type
{
   CREATE_FILE,
   TEXT_DOCUMENT,
   TABLE_DOCUMENT,
   OTHER
};

enum class user_role
{
    ADMIN_USER,
    MANAGER_USER,
    OTHER_USER
};

struct window_content
{
    qint32 id;
    window_type type;
    QMdiSubWindow* pWidget;
    QPushButton* pButton;
    window_content(int i, window_type t, QMdiSubWindow* w, QPushButton* b)
        : id(i), type(t), pWidget(w), pButton(b){}
};

QT_BEGIN_NAMESPACE
namespace Ui { class KCRM; }
QT_END_NAMESPACE

class KCRM : public QMainWindow
{
    Q_OBJECT

public:
    KCRM(QWidget *parent = nullptr);
    ~KCRM();
    void set_user_role(const QString& aRole);
    void set_data_base_manager(data_base_manager_kcrm *aDbmk);

private:

    void window_minimized(qint32 id);

    void window_close(qint32 id);

    void window_resize(qint32 id);

public slots:

    void create_text_document();

    void create_table_document();

    void on_actionNewFile_triggered();

    void on_actionOpenFile_triggered();

    void on_actionSaveFile_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private slots:
    void on_actiontelegram_triggered();

private slots:
    void on_actionprintDocument_triggered();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_5_triggered();

    void on_actionai_triggered();

signals:
    void windowResized();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::KCRM *ui;
    user_role m_role;
    QVector<window_content> m_widgets;
    Ui::widget_create_file m_wcf;
    bool m_if_one_new_file_widget = false;
    bool m_if_telegram_open = false;
    data_base_manager_kcrm *m_dbmk = nullptr;

};
#endif // KCRM_H
