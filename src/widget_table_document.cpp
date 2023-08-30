#include "widget_table_document.h"
#include "ui_widget_table_document.h"

widget_table_document::widget_table_document(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_table_document)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);
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
