#ifndef WIDGET_WH_H
#define WIDGET_WH_H

#include "ui_widget_wh.h"
#include "src/data_base/data_base_manager_kcrm.h"
#include <QWidget>

/*!
 * Widget склада.
 * \author Konstantin Smirnov
 *
 */
namespace Ui {
class widget_wh;
}

class widget_wh : public QWidget
{
    Q_OBJECT

public:
    explicit widget_wh(data_base_manager_kcrm *aDbmk, QWidget *parent = nullptr) :
        QWidget(parent), ui(new Ui::widget_wh), m_dbmk(aDbmk)
    {
        ui->setupUi(this);
    }

    ~widget_wh()
    {
        delete ui;
    }

    QString getLableName() {
        return ui->label->text();
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        m_current = event->pos();
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (event->buttons() & Qt::LeftButton)
        {
            QPoint delta = event->pos() - m_current;
            QPoint newpos = this->parentWidget()->pos() + delta;
            QRect parentGeometry = this->parentWidget()->parentWidget()->geometry();


            if (newpos.x() >= parentGeometry.left() && newpos.y() >= parentGeometry.top()
                && newpos.x() + width() <= parentGeometry.right() && newpos.y() + height() <= parentGeometry.bottom()) {
                this->parentWidget()->move(newpos);
            }
        }
    }


private:
    Ui::widget_wh *ui;
    QPoint m_current;
    data_base_manager_kcrm *m_dbmk;

private slots:
    void on_pushButton_clicked()
    {
        emit signal_window_close();
    }

    void on_pushButton_2_clicked()
    {
        this->parentWidget()->showMinimized();
        emit signal_window_minimized();
    }

    void on_pushButton_3_clicked()
    {
        QSize size = this->parentWidget()->minimumSizeHint();
        if(this->parentWidget()->isMaximized())
        {
            this->parentWidget()->resize(size);
            this->parentWidget()->showNormal();
        }
        else
        {
            this->parentWidget()->showMaximized();
        }
    }

signals:
    void signal_window_minimized();
    void signal_window_close();
};

#endif // WIDGET_WH_H
