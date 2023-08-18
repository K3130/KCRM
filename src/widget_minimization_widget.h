#ifndef WIDGET_MINIMIZATION_WIDGET_H
#define WIDGET_MINIMIZATION_WIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QLayout>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>

struct button_object
{
    QPushButton* m_b;
    QWidget* m_o;
};

namespace Ui {
class widget_minimization_widget;
}

class widget_minimization_widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget_minimization_widget(QWidget *parent = nullptr);
    ~widget_minimization_widget();

    void createButton(const QString& aName, QWidget* aWidget);

private:
    Ui::widget_minimization_widget *ui;
    QVector<button_object> m_buttons;

private slots:
  void handleButtonClick(int buttonIndex);

signals:
  void signal_button_adds();

public slots:
  void draw_button();
protected:
  void paintEvent(QPaintEvent *pe);
};

#endif // WIDGET_MINIMIZATION_WIDGET_H
