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
#include <QVariant>
#include <QVector>
#include <QScrollBar>

/*
 * Виджет табличного документа.
*/

#define MAX_COLUMNS 1000
#define MAX_ROWS 1000
#define COLUMN_WIDTH 10

class widget_table_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    widget_table_model(int aRow, int aCol, QObject *aParent = nullptr) : QAbstractTableModel(aParent),
        m_data(aRow, QVector<QVariant>(aCol))
    {

    }

    int rowCount(const QModelIndex &aParent = QModelIndex()) const override {
        return m_data.size();
    }

    int columnCount(const QModelIndex &aParent = QModelIndex()) const override {
        return m_data.empty() ? 0 : m_data[0].size();
    }

    QVariant data(const QModelIndex &aIndex, int aRole = Qt::DisplayRole) const override {
        if (!aIndex.isValid() || aRole != Qt::DisplayRole)
            return QVariant();
        return m_data[aIndex.row()][aIndex.column()];
    }

    bool setData(const QModelIndex &aIndex, const QVariant &aValue, int aRole = Qt::EditRole) override {
        if (aIndex.isValid() && aRole == Qt::EditRole) {
            m_data[aIndex.row()][aIndex.column()] = aValue;
            return true;
        }
        return false;
    }

    Qt::ItemFlags flags(const QModelIndex &aIndex) const override
    {
        if (!aIndex.isValid())
            return Qt::NoItemFlags;
        return Qt::ItemIsEditable | QAbstractTableModel::flags(aIndex);
    }

    bool insertRow(int aPosition, const QModelIndex &aParent = QModelIndex()) {
        beginInsertRows(aParent, aPosition, aPosition);
        QVector<QVariant> newRow(columnCount());
        m_data.insert(aPosition, newRow);
        endInsertRows();
        return true;
    }

    bool insertColumn(int aPosition, const QModelIndex &aParent = QModelIndex()) {
        beginInsertColumns(aParent, aPosition, aPosition);
        for (int i = 0; i < rowCount(); i++) {
            m_data[i].insert(aPosition, QVariant());
        }
        endInsertColumns();
        return true;
    }

private:
    QVector<QVector<QVariant>> m_data;
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
    void scrollHandler(int aValue);
    const widget_table_model* getModel() const{
        return m_model;
    }

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    QPoint m_current;
    Ui::widget_table_document *ui;
    widget_table_model *m_model;
    bool m_file_changed = false;

signals:
    void signal_window_minimized();
    void signal_window_close();
};

#endif // WIDGET_TABLE_DOCUMENT_H
