#ifndef DIALOG_PROS_H
#define DIALOG_PROS_H

#include <QDialog>

namespace Ui {
class Dialog_pros;
}

class Dialog_pros : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_pros(QWidget *parent = 0);
    ~Dialog_pros();

    void Set_Value(int); // проценты

private:
    Ui::Dialog_pros *ui;
};

#endif // DIALOG_PROS_H
