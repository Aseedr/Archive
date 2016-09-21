#include "dialog_pros.h"
#include "ui_dialog_pros.h"

Dialog_pros::Dialog_pros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_pros)
{
    ui->setupUi(this);
    ui->pushButton->setDisabled(1);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
}

Dialog_pros::~Dialog_pros()
{
    delete ui;
}

void Dialog_pros::Set_Value(int value){
    ui->progressBar->setValue(value);
    if(value == 100){ // проценты
        ui->label->setText("Завершено");
        ui->pushButton->setDisabled(0);
    }
}
