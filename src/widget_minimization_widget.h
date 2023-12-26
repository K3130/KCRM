#ifndef WIDGET_MINIMIZATION_WIDGET_H
#define WIDGET_MINIMIZATION_WIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QLayout>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include "widget_text_document.h"

/*
 * Виджет прдставления сворачивания окна.
 * Представляется в предсталении сворачивания окна в низ.
 * При нажатии на кнопку разварачивает окно или делает его активным.
 *
*/

namespace Ui {
class widget_minimization_widget;
}

class widget_minimization_widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget_minimization_widget(QWidget *parent = nullptr);
    ~widget_minimization_widget();

    void createButton(QPushButton* aButton, QWidget* aWidget);
    void delete_button(QPushButton* aButton);
    void handleButtonClick(QWidget* aWidget);

private:
    Ui::widget_minimization_widget *ui;
    QPushButton* m_button = nullptr;

protected:
  void paintEvent(QPaintEvent *pe);
};

#endif // WIDGET_MINIMIZATION_WIDGET_H
