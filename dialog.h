#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void Dialog_1(); // окно архивации
    void Dialog_2(); // окно разархивации
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
