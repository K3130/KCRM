#ifndef WIDGET_USERS_HPP
#define WIDGET_USERS_HPP
#include "ui_widget_users.h"
#include "src/data_base/data_base_manager_kcrm.h"
#include <QWidget>
#include <QCommonStyle>
#include <QComboBox>
#include <QLineEdit>
#include <QPainter>
#include <QBitmap>
#include <QPainterPath>
#include <QRegion>

/*!
 * Widget для просмотра всех учетных записей из БД
 * \author Konstantin Smirnov
 */

namespace Ui {
class widget_users;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        loginLineEdit = new QLineEdit(this);
        loginLineEdit->setPlaceholderText(QString("Login"));
        passwordLineEdit = new QLineEdit(this);
        passwordLineEdit->setPlaceholderText(QString("Password"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        positionLineEdit = new QLineEdit(this);
        positionLineEdit->setPlaceholderText("Position");
        roleComboBox = new QComboBox(this);
        roleComboBox->addItem("admin");
        roleComboBox->addItem("manager");
        roleComboBox->addItem("other");
        okButton = new QPushButton("OK", this);
        cancelButton = new QPushButton("Cancel", this);
        connect(okButton, &QPushButton::clicked, this, &Dialog::onAcceptedClicked);
        connect(cancelButton, &QPushButton::clicked, this, &Dialog::onCancelledClicked);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(loginLineEdit);
        layout->addWidget(passwordLineEdit);
        layout->addWidget(positionLineEdit);
        layout->addWidget(roleComboBox);
        layout->addWidget(okButton);
        layout->addWidget(cancelButton);
        setLayout(layout);
    }
signals:
    void accepted(QString login, QString password, QString role, QString position);
private slots:
    void onAcceptedClicked()
    {
        QString login = loginLineEdit->text();
        QString password = passwordLineEdit->text();
        QString position = positionLineEdit->text();
        QString role = roleComboBox->currentText();
        emit accepted(login, password, role, position);
        accept();
    }
    void onCancelledClicked() { reject(); }
private:
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *positionLineEdit;
    QComboBox *roleComboBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

class widget_users : public QWidget
{
    Q_OBJECT

public:
    explicit widget_users(data_base_manager_kcrm *aDbmk, QWidget *parent = nullptr) :
        QWidget(parent),  ui(new Ui::widget_users), m_dbmk(aDbmk)
    {
        ui->setupUi(this);

        // Оформление таблицы
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels({" № ", "Пользователь", "Роль", "Должность"});
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QString tableStyleSheet = "QTableView { background-color: #F8F9FA; color: #212934; }"
                                  "QHeaderView::section { background-color: #B8C4CE; padding: 4px; font-size: 8pt; border-style: none; border-bottom: 1px solid #fffff8; border-right: 1px solid #fffff8; height: 15px;}"
                                  "QTableWidget { gridline-color: #B8C4CE; font-size: 12pt; }"
                                  "QTableWidget QTableCornerButton::section { background-color: #646464; border: 1px solid #fffff8; }";
        ui->tableWidget->setStyleSheet(tableStyleSheet);


        // При нажатии выделять всю строку
        connect(ui->tableWidget, &QTableWidget::cellClicked, [&](int row, int column) {
            for (int col = 0; col < ui->tableWidget->columnCount(); col++) {
                ui->tableWidget->item(row, col)->setSelected(true);
            }
        });

        ui->tableWidget->show();

        // Кнопки
        QString buttonStyle("QPushButton {border-radius: 5px; background-color: #63A2D8; border-style: outset;"
                            "border-width: 2px; border-color: beige; font: bold 14px; padding: 6px; width: 5px}"
                            "QPushButton:hover { background-color: #AAD4F5; }"
                            "QPushButton:pressed { background-color: #EFF8FF; border-style: inset;}");
        QCommonStyle style;
        ui->pushButton_4->setText("Добавить");
        ui->pushButton_4->setStyleSheet(buttonStyle);

        ui->pushButton_5->setText("Удалить");
        ui->pushButton_5->setStyleSheet(buttonStyle);

        ui->pushButton_6->setText("");
        ui->pushButton_6->setStyleSheet(buttonStyle);
        ui->pushButton_6->setIcon(style.standardIcon(QStyle::SP_BrowserReload));

        fillTable();

        int rowHeight = 20;
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
            ui->tableWidget->setRowHeight(i, rowHeight);
        }
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
        Dialog* dialog = new Dialog(this);
        dialog->setModal(true);
        dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
        QObject::connect(dialog, &Dialog::accepted, [&](QString login, QString password, QString role, QString position) {
            m_dbmk->add_new_user(login, password, role, position);

        });
        dialog->show();
    }
    void on_pushButton_5_clicked()
    {
        if (ui->tableWidget->item(ui->tableWidget->currentRow(), 1) != nullptr) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, " ",
                "Вы точно хотите удалить пользователя: " + ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text() + "?",
                                                                                     QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    m_dbmk->delete_user(ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text());

                }
        }
    }

    void on_pushButton_6_clicked()
    {

        fillTable();
        int rowHeight = 20;
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
                ui->tableWidget->setRowHeight(i, rowHeight);
        }
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
