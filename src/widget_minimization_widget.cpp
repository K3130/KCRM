#include "widget_minimization_widget.h"
#include "ui_widget_minimization_widget.h"

widget_minimization_widget::widget_minimization_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_minimization_widget)
{
    ui->setupUi(this);
    ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout->setSpacing(0);
    //ui->horizontalLayout->addStretch();
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);


    //QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding);
    //ui->horizontalLayout->addSpacerItem(item);



}

widget_minimization_widget::~widget_minimization_widget()
{
    delete ui;
}

void widget_minimization_widget::createButton(QPushButton* aButton, QWidget* aWidget)
{
    if (aButton != nullptr && aWidget != nullptr)
    {
        for (int i = 0; i < ui->horizontalLayout->count(); ++i)
        {
            QWidget *widget = ui->horizontalLayout->itemAt(i)->widget();
            if (widget == aButton)
            {
                return;
            }
        }

        aButton->setStyleSheet("font-size: 10pt;"
                               "font-weight: bold;"
                               "color: #eb4c3b;"
                               "min-width: 5em;");

        connect(aButton, &QPushButton::clicked, this, [=]{ handleButtonClick(aWidget); });
        connect(aWidget, &QWidget::destroyed, this, [=]{ delete_button(aButton); });
        ui->horizontalLayout->addWidget(aButton);
    }
}

void widget_minimization_widget::delete_button(QPushButton* aButton)
{
    //ui->horizontalLayout->removeWidget(aButton);
    ui->horizontalLayout->update();

}

void widget_minimization_widget::handleButtonClick(QWidget* aWidget)
{
    if (aWidget != nullptr)
    {
        QSize size = aWidget->minimumSizeHint();
        aWidget->resize(size);
        aWidget->showNormal();
    }

}


void widget_minimization_widget::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
      o.initFrom(this);
      QPainter p(this);
      style()->drawPrimitive(
        QStyle::PE_Widget, &o, &p, this);
}
