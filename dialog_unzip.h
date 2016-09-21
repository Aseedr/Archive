#ifndef DIALOG_UNZIP_H
#define DIALOG_UNZIP_H

#include <QDialog>
#include <main.h>

namespace Ui {
class Dialog_unzip;
}

class Dialog_unzip : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_unzip(QWidget *parent = 0);
    ~Dialog_unzip();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void Dialog_3(); // распеделение

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Dialog_unzip *ui;
    char mass_in[MAS_SIZE][MAS_SIZE];
    char mass_out[MAS_SIZE][MAS_SIZE];
    string name_nf;
    int kol = 0, count = 0, kol2 = 0;
};

#endif // DIALOG_UNZIP_H
