#ifndef WIDGET_CREATE_FILE_H
#define WIDGET_CREATE_FILE_H

#include <QWidget>

namespace Ui {
class widget_create_file;
}

class widget_create_file : public QWidget
{
    Q_OBJECT

public:
    explicit widget_create_file(QWidget *parent = nullptr);
    ~widget_create_file();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::widget_create_file *ui;

};

#endif // WIDGET_CREATE_FILE_H
