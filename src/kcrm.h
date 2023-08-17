#ifndef KCRM_H
#define KCRM_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QVector>
#include <QDebug>
#include "ui_widget_create_file.h"
#include "widget_create_file.h"
#include "widget_text_document.h"
#include "ui_widget_text_document.h"
#include "./ui_kcrm.h"

enum class window_flags
{
   CREATE_FILE,
   TEXT_DOCUMENT,
   TABLE_DOCUMENT
};

struct window_content
{
    window_flags flag;
    QMdiSubWindow* pWidget;
    window_content(window_flags f, QMdiSubWindow* w) : flag(f), pWidget(w){}
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


private slots:
    void create_text_document();

public slots:
    void on_actionNewFile_triggered();

    void on_actionOpenFile_triggered();

    void on_actionSaveFile_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private:
    Ui::KCRM *ui;
    Ui::widget_create_file m_wcf;
    Ui::widget_text_document m_wtd;
    QVector<window_content> m_widgets;

};
#endif // KCRM_H
