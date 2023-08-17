#include "widget_text_document.h"
#include "ui_widget_text_document.h"

widget_text_document::widget_text_document(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_text_document)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);
}

widget_text_document::~widget_text_document()
{
    delete ui;
}

void widget_text_document::mousePressEvent(QMouseEvent *event)
{
    m_current = event->pos();
}

void widget_text_document::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint delta = event->pos() - m_current;
        QPoint newpos = this->parentWidget()->pos() + delta;
        QRect parentGeometry = this->parentWidget()->parentWidget()->geometry();
        qDebug() << "geometry: " << parentGeometry;

        if (newpos.x() >= parentGeometry.left() && newpos.y() >= parentGeometry.top()
                && newpos.x() + width() <= parentGeometry.right() && newpos.y() + height() <= parentGeometry.bottom()) {
                this->parentWidget()->move(newpos);
        }
    }

}






