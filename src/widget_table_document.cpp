#include "widget_table_document.h"
#include "ui_widget_table_document.h"
#include <QStandardItemModel>

widget_table_document::widget_table_document(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_table_document)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);

    m_model = new widget_table_model(30, 30, this);
    ui->tableView->setModel(m_model);
    ui->tableView->show();

    QScrollBar *horizontalScrollBar = ui->tableView->horizontalScrollBar();
    connect(horizontalScrollBar, &QScrollBar::valueChanged, this, &widget_table_document::scrollHandler);
    QScrollBar *verticalScrollBar = ui->tableView->verticalScrollBar();
    connect(verticalScrollBar, &QScrollBar::valueChanged, this, &widget_table_document::scrollHandler);

    connect(m_model, &widget_table_model::dataChanged, this, [=](){ m_file_changed = true; });
}

widget_table_document::~widget_table_document()
{
    delete ui;
}

void widget_table_document::mousePressEvent(QMouseEvent *event)
{
    m_current = event->pos();
}

void widget_table_document::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint delta = event->pos() - m_current;
        QPoint newpos = this->parentWidget()->pos() + delta;
        QRect parentGeometry = this->parentWidget()->parentWidget()->geometry();


        if (newpos.x() >= parentGeometry.left() && newpos.y() >= parentGeometry.top()
                && newpos.x() + width() <= parentGeometry.right() && newpos.y() + height() <= parentGeometry.bottom()) {
                this->parentWidget()->move(newpos);
        }
    }
}

QString widget_table_document::getLableName()
{
    return ui->label->text();
}

void widget_table_document::setLableName(const QString &aLable)
{
    ui->label->setText(aLable);
}

void widget_table_document::changeFileChangedState()
{
    m_file_changed = false;
}

bool widget_table_document::getFileState()
{
    return m_file_changed;
}

void widget_table_document::scrollHandler(int aValue)
{
    QScrollBar *scrollBar = qobject_cast<QScrollBar*>(sender());
    if (scrollBar->orientation() == Qt::Horizontal) {
        int maximum = m_model->columnCount();
        if (aValue == scrollBar->maximum() && maximum < MAX_COLUMNS) {
                m_model->insertColumn(maximum);
                //ui->tableView->setColumnWidth(maximum, COLUMN_WIDTH);
                scrollBar->setValue(aValue - 1);
        }
    } else {
        int maximum = m_model->rowCount();
        if (aValue == scrollBar->maximum() && maximum < MAX_ROWS) {
                m_model->insertRow(maximum);
                scrollBar->setValue(aValue - 1);
        }
    }
}

void widget_table_document::on_pushButton_clicked()
{
    emit signal_window_close();
}

void widget_table_document::on_pushButton_3_clicked()
{
    QSize size = this->parentWidget()->minimumSizeHint();
    if(this->parentWidget()->isMaximized())
    {
        this->parentWidget()->resize(size);
        this->parentWidget()->showNormal();
    }
    else
    {
        this->parentWidget()->showMaximized();
    }
}

void widget_table_document::on_pushButton_2_clicked()
{
    this->parentWidget()->showMinimized();
    emit signal_window_minimized();
}

void widget_table_document::table_changed()
{
    qDebug("dsadsa");
}
