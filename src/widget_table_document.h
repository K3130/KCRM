#ifndef WIDGET_TABLE_DOCUMENT_H
#define WIDGET_TABLE_DOCUMENT_H

#include <QWidget>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QMdiSubWindow>
#include <QFrame>
#include <QDebug>
#include <QModelIndex>
#include <QAbstractTableModel>

class widget_table_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    widget_table_model(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

};

namespace Ui {
class widget_table_document;
}

class widget_table_document : public QWidget
{
    Q_OBJECT

public:
    explicit widget_table_document(QWidget *parent = nullptr);
    ~widget_table_document();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    QString getLableName();
    void setLableName(const QString& aLable);
    void changeFileChangedState();
    bool getFileState();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    QPoint m_current;
    Ui::widget_table_document *ui;
    bool m_file_changed = false;

signals:
    void signal_window_minimized();
    void signal_window_close();
};

#endif // WIDGET_TABLE_DOCUMENT_H
