#ifndef WIDGET_TEXT_DOCUMENT_H
#define WIDGET_TEXT_DOCUMENT_H

#include <QWidget>

namespace Ui {
class widget_text_document;
}

class widget_text_document : public QWidget
{
    Q_OBJECT

public:
    explicit widget_text_document(QWidget *parent = nullptr);
    ~widget_text_document();

private:
    Ui::widget_text_document *ui;
};

#endif // WIDGET_TEXT_DOCUMENT_H
