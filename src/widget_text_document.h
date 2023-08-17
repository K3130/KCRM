#ifndef WIDGET_TEXT_DOCUMENT_H
#define WIDGET_TEXT_DOCUMENT_H

#include <QWidget>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QMdiSubWindow>
#include <QFrame>
#include <QDebug>

namespace Ui {
class widget_text_document;
}

class widget_text_document : public QWidget
{
    Q_OBJECT

public:
    explicit widget_text_document(QWidget *parent = nullptr);
    ~widget_text_document();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private:
    QPoint m_current;
    bool m_pressed;
    Ui::widget_text_document *ui;
};

#endif // WIDGET_TEXT_DOCUMENT_H
