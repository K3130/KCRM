#ifndef WIDGET_TELEGRAM_H
#define WIDGET_TELEGRAM_H

#include <QWidget>

/*
 * Виджет telegram.
*/

namespace Ui {
class widget_telegram;
}

class widget_telegram : public QWidget
{
    Q_OBJECT

public:
    explicit widget_telegram(QWidget *parent = nullptr);
    ~widget_telegram();

    QString getLableName();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::widget_telegram *ui;

signals:
    void signal_window_minimized();
    void signal_window_close();
};

#endif // WIDGET_TELEGRAM_H
