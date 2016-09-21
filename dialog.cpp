#include "dialog.h"
#include "ui_dialog.h"
#include "dialog_zip.h"
#include "dialog_unzip.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(Dialog_1()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Dialog_2()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Dialog_1(){
    this->setEnabled(false);
    Dialog_zip z; // диалоговое окно архивации
    z.setWindowTitle("Архивация VIX");
    //w.setWindowFlags(w.windowFlags() & ~Qt::WindowContextHelpButtonHint); //скрыть кнопку помощи
    z.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint); //скрыть все кнопки
    z.show();
    z.exec();
    this->setEnabled(true);
}

void Dialog::Dialog_2(){
    this->setEnabled(false);
    Dialog_unzip y; // диалоговое окно разархивации
    y.setWindowTitle("Разархивация VIX");
    y.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    y.show();
    y.exec();
    this->setEnabled(true);
}
