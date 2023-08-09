#ifndef KCRM_H
#define KCRM_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QVector>
#include "ui_widget_create_file.h"

enum class window_flags
{
   CREATE_FILE,
   TEXT_DOCUMENT,
   TABLE_DOCUMENT
};

struct window_content
{
    window_flags flag;
    QWidget* pWidget;
    window_content(window_flags f, QWidget* w) : flag(f), pWidget(w){}
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

public slots:
    void on_actionNewFile_triggered();

    void on_actionOpenFile_triggered();

    void on_actionSaveFile_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private:
    Ui::KCRM *ui;
    Ui::widget_create_file m_wcf;
    QVector<window_content> m_widgets;
};
#endif // KCRM_H
