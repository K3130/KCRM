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
    QString getLableName();
    void setLableName(const QString& aLable);
    void setText(const QString& aText);
    void changeFileChangedState();
    bool getFileState();
    QString getTextPlainText();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    QPoint m_current;
    bool m_pressed;
    Ui::widget_text_document *ui;
    bool m_file_changed = false;;

signals:
    void signal_window_minimized();
    void signal_window_close();

};

#endif // WIDGET_TEXT_DOCUMENT_H
