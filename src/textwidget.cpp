#include "textwidget.h"

TextWidget::TextWidget(QWidget *parent)
    : QWidget{parent}
{
    QTextEdit textEdit;
        textEdit.show();
}
