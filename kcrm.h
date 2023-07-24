#ifndef KCRM_H
#define KCRM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class KCRM; }
QT_END_NAMESPACE

class KCRM : public QMainWindow
{
    Q_OBJECT

public:
    KCRM(QWidget *parent = nullptr);
    ~KCRM();

private:
    Ui::KCRM *ui;
};
#endif // KCRM_H
