#include "widget_minimization_widget.h"
#include "ui_widget_minimization_widget.h"

widget_minimization_widget::widget_minimization_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_minimization_widget)
{
    ui->setupUi(this);

    ui->horizontalLayout->setMargin(0);
    ui->horizontalLayout->setSpacing(0);
    ui->horizontalLayout->addStretch();


    QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding);
    ui->horizontalLayout->addSpacerItem(item);

    connect(this, &widget_minimization_widget::signal_button_adds, this, &widget_minimization_widget::draw_button);

}

widget_minimization_widget::~widget_minimization_widget()
{
    delete ui;
}

void widget_minimization_widget::createButton(const QString &aName, QWidget *aWidget)
{
    bool ifExist = false;
    for (int i = 0; i < m_buttons.size(); ++i)
    {
        if(aWidget == m_buttons[i].m_o)
            ifExist = true;
    }
    //#eb4c3b
    if(!ifExist)
    {
        button_object b;
        b.m_b = new QPushButton(aName, this);


        b.m_b->setStyleSheet("font-size: 15pt;"
                             "font-weight: bold;"
                             "color: #eb4c3b;"
                             "min-width: 5em;");


        b.m_o = aWidget;
        m_buttons.append(b);
        emit signal_button_adds();
    }
}

void widget_minimization_widget::handleButtonClick(int buttonIndex)
{
    QSize size = m_buttons[buttonIndex].m_o->minimumSizeHint();
    m_buttons[buttonIndex].m_o->resize(size);
    m_buttons[buttonIndex].m_o->showNormal();
}

void widget_minimization_widget::draw_button()
{
    for (int i = 0; i < m_buttons.size(); ++i)
    {
        connect(m_buttons[i].m_b, &QPushButton::clicked, this, [=]{ handleButtonClick(i); });

        ui->horizontalLayout->insertWidget(i, m_buttons[i].m_b);


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
