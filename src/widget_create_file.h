#ifndef WIDGET_CREATE_FILE_H
#define WIDGET_CREATE_FILE_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

namespace Ui {
class widget_create_file;
}

class widget_create_file : public QWidget
{
    Q_OBJECT

public:
    explicit widget_create_file(QWidget *parent = nullptr);
    ~widget_create_file();

protected:
    void mouseMoveEvent(QMouseEvent* event) override
    {
        QRect availableGeometry = QApplication::desktop()->availableGeometry();

        int newX = event->globalX();
        int newY = event->globalY();


        if (newX < availableGeometry.left()) {
            newX = availableGeometry.left();
        } else if (newX > availableGeometry.right() - width()) {
            newX = availableGeometry.right() - width();
        }

        if (newY < availableGeometry.top()) {
            newY = availableGeometry.top();
        } else if (newY > availableGeometry.bottom() - height()) {
            newY = availableGeometry.bottom() - height();
        }

        move(newX, newY);
    }
    void mousePressEvent(QMouseEvent* event) override
        {
            if (event->button() == Qt::LeftButton) {

                setCursor(Qt::ClosedHandCursor);
                event->accept();
            }
        }

    void mouseReleaseEvent(QMouseEvent* event) override
        {
            if (event->button() == Qt::LeftButton) {

                setCursor(Qt::ArrowCursor);
                event->accept();
            }
        }
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::widget_create_file *ui;

};

#endif // WIDGET_CREATE_FILE_H
