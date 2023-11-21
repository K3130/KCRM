#ifndef WIDGET_USERS_HPP
#define WIDGET_USERS_HPP
#include "ui_widget_users.h"
#include "src/data_base/data_base_manager_kcrm.h"
#include <QWidget>
#include <QCommonStyle>

namespace Ui {
class widget_users;
}

class widget_users : public QWidget
{
    Q_OBJECT

public:
    explicit widget_users(data_base_manager_kcrm *aDbmk, QWidget *parent = nullptr) :
        QWidget(parent),  ui(new Ui::widget_users), m_dbmk(aDbmk)
    {
        ui->setupUi(this);

        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels({" № ", "Пользователь", "Роль", "Должность"});
        ui->tableWidget->show();

        QCommonStyle style;
        ui->pushButton_4->setText("Добавить");
        ui->pushButton_5->setText("Удалить");
        ui->pushButton_6->setText("");
        ui->pushButton_6->setIcon(style.standardIcon(QStyle::SP_BrowserReload));

        fillTable();

    }
    ~widget_users() {
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
    void fillTable()
    {
        QVector<QString> users = m_dbmk->get_all_users_name();
        QVector<QString> roles = m_dbmk->get_all_users_role();
        QVector<QString> pos = m_dbmk->get_all_users_position();

        ui->tableWidget->setRowCount(users.size());

        for (size_t i = 0; i < users.size(); i++)
        {
            QTableWidgetItem *userNum = new QTableWidgetItem(QString::number(i));
            QTableWidgetItem *userItem = new QTableWidgetItem(users[i]);
            QTableWidgetItem *roleItem = new QTableWidgetItem(roles[i]);
            QTableWidgetItem *posItem = new QTableWidgetItem(pos[i]);
            ui->tableWidget->setItem(i, 0, userNum);
            ui->tableWidget->setItem(i, 1, userItem);
            ui->tableWidget->setItem(i, 2, roleItem);
            ui->tableWidget->setItem(i, 3, posItem);
        }
        ui->tableWidget->update();
    }

private slots:
    void on_pushButton_clicked()
    {
        emit signal_window_close();
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

    void on_pushButton_2_clicked()
    {
        this->parentWidget()->showMinimized();
        emit signal_window_minimized();
    }

    void on_pushButton_4_clicked()
    {

    }
    void on_pushButton_5_clicked()
    {

    }

    void on_pushButton_6_clicked()
    {
        fillTable();
    }

private:
    QPoint m_current;
    Ui::widget_users *ui;
    data_base_manager_kcrm *m_dbmk;

signals:
    void signal_window_minimized();
    void signal_window_close();
};

#endif // WIDGET_USERS_HPP
