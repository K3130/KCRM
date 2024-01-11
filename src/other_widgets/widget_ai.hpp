#ifndef WIDGET_AI_HPP
#define WIDGET_AI_HPP

#include "ui_widget_ai.h"
#include <QWidget>
#include <QTextEdit>
#include <QComboBox>

/*!
 * Widget для AI скриптов пока для тестов.
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
        setStyleSheet("background-color: #AAD4F5;");
        m_button1 = new QPushButton("Чат", this);
        m_button2 = new QPushButton("Фото", this);
        m_button3 = new QPushButton("Еще", this);
        m_button4 = new QPushButton("OK", this);
        QString buttonStyle = "QPushButton {border-radius: 5px; background-color: #63A2D8; border-style: outset;"
                        "border-width: 2px; border-color: beige; font: bold 14px; padding: 6px; width: 5px}"
                        "QPushButton:hover { background-color: #AAD4F5; }"
                        "QPushButton:pressed { background-color: #EFF8FF; border-style: inset;}";

        m_textEdit1 = new QTextEdit(this);
        m_textEdit1->setStyleSheet("QTextEdit {border-radius: 0px; width: 50px; background-color: #D4DDE9;}");
        m_textEdit1->hide();

        m_textEdit2 = new QTextEdit(this);
        m_textEdit2->setStyleSheet("QTextEdit {border-radius: 0px; width: 50px; background-color: #D4DDE9;}");
        m_textEdit2->setReadOnly(true);
        m_textEdit2->hide();

        m_comboBox1 = new QComboBox(this);
        m_comboBox1->setStyleSheet("QComboBox {border-radius: 0px; background-color: #D4DDE9;}");
        m_comboBox1->setPlaceholderText("Выбор скрипта:");
        m_comboBox1->hide();

        // Button 1
        m_button1->setGeometry(QRect(40, 40, 170, 40));
        m_button1->setStyleSheet(buttonStyle);
        m_button1->show();
        connect(m_button1, &QPushButton::clicked, this, [&]() {
            hideObj();
            m_textEdit1->setFocus();
            m_isButton1clicked = true;
            m_isButton2clicked = false;
            m_isButton3clicked = false;
            update();
        });

        // Button 2
        m_button2->setGeometry(QRect(40, m_button1->geometry().bottom() + 20, 170, 40));
        m_button2->setStyleSheet(buttonStyle);
        m_button2->show();
        connect(m_button2, &QPushButton::clicked, this, [&]() {
            hideObj();
            m_isButton1clicked = false;
            m_isButton2clicked = true;
            m_isButton3clicked = false;
            update();
        });

        // Button 3
        m_button3->setGeometry(QRect(40, m_button2->geometry().bottom() + 20, 170, 40));
        m_button3->setStyleSheet(buttonStyle);
        m_button3->show();
        connect(m_button3, &QPushButton::clicked, this, [&]() {
            hideObj();
            m_isButton1clicked = false;
            m_isButton2clicked = false;
            m_isButton3clicked = true;
            update();
        });

        // Button 4 Кнопка для отправки сообщения AI
        m_button4->setStyleSheet(buttonStyle);
        m_button4->hide();
        connect(m_button4, &QPushButton::clicked, this, [&]() {


        });
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);

        QRect rect1(0, 0, 250, height());
        painter.setBrush(QColor("#173F5F"));
        //painter.setPen(Qt::NoPen);
        painter.drawRect(rect1);


        QRect rect2(rect1.adjusted(20, 20, -20, -20));
        painter.setBrush(QColor("#20639B"));
        painter.drawRoundedRect(rect2, 10, 10);

        if(m_isButton1clicked)
        {
            QRect rect3(rect2.right() + 40, 20, width() - rect2.right() - 60, height()-40);
            painter.setBrush(QColor("#20639B"));
            painter.drawRoundedRect(rect3, 10, 10);

            // строка ввода
            QRect rect4(rect3.left() + 20, rect3.bottom() - 60, rect3.width() - 170, 40);
            painter.setBrush(QColor("#D4DDE9"));
            painter.drawRoundedRect(rect4, 10, 10);
            m_textEdit1->setGeometry(QRect(rect3.left() + 30, rect3.bottom() - 50, rect4.width()-20, 25));
            m_textEdit1->show();

            // Кнопка ввода
            QRect buttonRect(rect3.width() + 130, rect3.bottom() - 60, 100, 40);
            m_button4->setGeometry(buttonRect);
            m_button4->show();
            //---

            // экран вывода
            QRect rect5(rect3.left() + 20, rect3.top() + 60, rect3.width() - 170, height()-190);
            painter.setBrush(QColor("#D4DDE9"));
            painter.drawRoundedRect(rect5, 10, 10);
            m_textEdit2->setGeometry(QRect(rect3.left() + 30, rect3.top() + 70, rect4.width() - 20, height()-210));
            m_textEdit2->show();


            // комбобокс со скриптами
            QRect rect6(rect3.left() + 20, rect3.top() + 20, 160, 25);
            painter.setBrush(QColor("#D4DDE9"));
            painter.drawRoundedRect(rect6, 10, 10);
            m_comboBox1->setGeometry(rect3.left() + 30, rect3.top() + 23, 140, 20);
            m_comboBox1->show();

        }
        if(m_isButton2clicked)
        {

        }
        if(m_isButton3clicked)
        {

        }



    }
private:
    /*!
     * \brief hideObj
     * Удаляет не используемые в данный момент объекты
     */
    void hideObj()
    {
        // Первая группа
        m_button4->hide();
        m_textEdit1->hide();
        m_textEdit2->hide();
        m_comboBox1->hide();

        // --
    }
private:
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_button3;
    QPushButton *m_button4;
    bool m_isButton1clicked = false;
    bool m_isButton2clicked = false;
    bool m_isButton3clicked = false;
    QTextEdit *m_textEdit1;
    QTextEdit *m_textEdit2;
    QComboBox *m_comboBox1;
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
