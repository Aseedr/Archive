#ifndef DIALOG_ZIP_H
#define DIALOG_ZIP_H

#include <QDialog>
#include "main.h"

namespace Ui {
class Dialog_zip;
}

class Dialog_zip : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_zip(QWidget *parent = 0);
    ~Dialog_zip();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void Dialog_3(); // распределение
    void on_pushButton_2_clicked();

private:
    Ui::Dialog_zip *ui;
    char mass[MAS_SIZE][MAS_SIZE];
    char name_fl[MAS_SIZE];
    int kol = 0;
};

#endif // DIALOG_ZIP_H
