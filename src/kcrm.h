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
   TABLE_DOCUMENT
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

private:

    void window_minimized(qint32 id);

    void window_close(qint32 id);

public slots:

    void create_text_document();

    void create_table_document();

    void on_actionNewFile_triggered();

    void on_actionOpenFile_triggered();

    void on_actionSaveFile_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private slots:
    void on_actionprintDocument_triggered();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

private:
    Ui::KCRM *ui;
    QVector<window_content> m_widgets;
    Ui::widget_create_file m_wcf;
    bool m_if_one_new_file_widget = false;

};
#endif // KCRM_H
