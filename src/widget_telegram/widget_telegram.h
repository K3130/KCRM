#ifndef WIDGET_TELEGRAM_H
#define WIDGET_TELEGRAM_H

#include <QWidget>

namespace Ui {
class widget_telegram;
}

class widget_telegram : public QWidget
{
    Q_OBJECT

public:
    explicit widget_telegram(QWidget *parent = nullptr);
    ~widget_telegram();

private:
    Ui::widget_telegram *ui;
};

#endif // WIDGET_TELEGRAM_H
