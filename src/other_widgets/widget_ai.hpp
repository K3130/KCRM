#ifndef WIDGET_AI_HPP
#define WIDGET_AI_HPP

#include "ui_widget_ai.h"
#include <QWidget>

/*!
 * Widget для AI скриптов пока для тестов
 * \author Konstantin Smirnov
 */

namespace Ui {
class widget_ai;
}


/*!
 * \brief Рисую свой виджет...
 *
 */

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setStyleSheet("background-color: #F8F9FA;");
        m_button1 = new QPushButton("Чат", this);
        m_button2 = new QPushButton("Фото", this);
        m_button3 = new QPushButton("Еще", this);
        m_buttonStyle = "QPushButton {border-radius: 5px; background-color: #63A2D8; border-style: outset;"
                        "border-width: 2px; border-color: beige; font: bold 14px; padding: 6px; width: 5px}"
                        "QPushButton:hover { background-color: #AAD4F5; }"
                        "QPushButton:pressed { background-color: #EFF8FF; border-style: inset;}";

        // Button 1
        m_button1->setGeometry(QRect(40, 40, 170, 40));
        m_button1->setStyleSheet(m_buttonStyle);
        m_button1->show();

        // Button 2
        m_button2->setGeometry(QRect(40, m_button1->geometry().bottom() + 20, 170, 40));
        m_button2->setStyleSheet(m_buttonStyle);
        m_button2->show();

        // Button 3
        m_button3->setGeometry(QRect(40, m_button2->geometry().bottom() + 20, 170, 40));
        m_button3->setStyleSheet(m_buttonStyle);
        m_button3->show();
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);

        // 1st rect
        QRect rect1(0, 0, 250, height());
        painter.setBrush(QColor("#173F5F"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect1);

        // 2 rect
        QRect rect2(rect1.adjusted(20, 20, -20, -20));
        painter.setBrush(QColor("#20639B"));
        painter.drawRoundedRect(rect2, 10, 10);

    }
private:
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_button3;
    QString m_buttonStyle;
    QRect m_rect1;
    QRect m_rect2;

};

class widget_ai : public QWidget
{
    Q_OBJECT

public:
    explicit widget_ai(QWidget *parent = nullptr) : QWidget(parent), ui(new Ui::widget_ai)
    {
        ui->setupUi(this);

        MyWidget *w = new MyWidget(this);
        ui->verticalLayout->addWidget(w);


    }

    ~widget_ai()
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
    Ui::widget_ai *ui;
    QPoint m_current;

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


signals:
    void signal_window_minimized();
    void signal_window_close();
};

#endif // WIDGET_AI_HPP
