#include "dialog.h"
#include "dialog_zip.h"
#include "ui_dialog_zip.h"
#include "dialog_pros.h"
#include "union.h"
#include "main.h"
#include "zip.h"
#include <QMessageBox>
#include <fstream>

Dialog_zip::Dialog_zip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_zip)
{
    ui->setupUi(this);
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(close()));
    ui->radioButton_2->setDisabled(1);
    ui->comboBox_2->setDisabled(1);
    ui->radioButton->click();
    ui->pushButton_2->setDisabled(1);
}

Dialog_zip::~Dialog_zip()
{
    delete ui;
}

void Dialog_zip::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == 0){
        return;
    }

    std::fstream input_file_name;

    QString *qs = new QString(ui->lineEdit->text());
    QByteArray qb = qs->toUtf8();
    delete qs; // перекодировка из qsting в char*
    char *temp = qb.data();

    input_file_name.open(temp, std::ios::in);
    if(!input_file_name){
        QMessageBox::information(this, "Ошибка!", "Файл не найден!");
        return;
    }

    strcpy(mass[kol], temp);
    kol++; // помещение в массив архивации

    input_file_name.close();
    ui->textBrowser->append(ui->lineEdit->text());
    ui->lineEdit->clear();
    ui->pushButton_2->setDisabled(0);
}

void Dialog_zip::on_pushButton_4_clicked()
{
    char temp_mas[MAS_SIZE];
    for(int i = 0; i < kol; i++){
        strcpy(mass[i], temp_mas);
    }
    kol = 0; // очищение массива архивации
    ui->textBrowser->clear();
    ui->pushButton_2->setDisabled(1);
}

void Dialog_zip::Dialog_3(){
    this->setEnabled(false);
    Dialog_pros x;
    x.setWindowTitle("Архивация");
    x.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    x.show();

    if(ui->comboBox->currentText() == "Хаффмана"){
        if(kol == 1){ // выбор последовательности в зависимости от данных
            std::fstream input_union_file; // запись пометок в файл
            input_union_file.open(name_fl, std::ios::app | std::ios::binary);
            input_union_file << "###\r\n";
            input_union_file << mass[0] << "\r\n";
            input_union_file.close();

            x.Set_Value(0); // архивация файла
            Zip *aa; int start = 0;
            aa = new Zip(mass[kol - 1], name_fl);
            aa->create_zip(x, start);
            delete aa;
        }
        else{
            x.Set_Value(0);
            Zip **files; int start = 0; // архивация каждого файла
            files = new Zip*[kol];
            for(int i = 0; i < kol; i++){
                char sss[MAS_SIZE];
                strcpy(sss, mass[i]);
                strcat(sss, ".vix");
                files[i] = new Zip(mass[i], sss);
                files[i]->create_zip(x, start);
                delete files[i];
            }
            delete[] files;

            Union **filess; int max = 50; // объедниение кэша
            std::fstream input_union_file;
            input_union_file.open(name_fl, std::ios::app | std::ios::binary);
            filess = new Union*[kol];
            for(int i = 0; i < kol; i++){
                char sss[MAS_SIZE];
                strcpy(sss, mass[i]);
                strcat(sss, ".vix");
                filess[i] = new Union(name_fl, sss);
                //remove(sss);
            }
            input_union_file << "#####\r\n"; // запись пометок
            input_union_file << kol << "\r\n";
            input_union_file.close();
            x.Set_Value(0);
            for(int i = 0; i < kol; i++)
                filess[i]->See_out(kol, i, max, x);
            for(int i = 0; i < kol; i++)
                filess[i]->Add_into(kol, i, max, x);
            for(int i = 0; i < kol; i++)
                delete filess[i];
            delete[] filess;

            for(int i = 0; i < kol; i++){ // удаление кеша
                char sss[MAS_SIZE];
                strcpy(sss, mass[i]);
                strcat(sss, ".vix");
                remove(sss);
            }
        }
    }
    else{
        Union **files; int max = 50;
        std::fstream input_union_file; // разъединение
        input_union_file.open(name_fl, std::ios::app | std::ios::binary);
        files = new Union*[kol];
        for(int i = 0; i < kol; i++){
            files[i] = new Union(name_fl, mass[i]);
        }
        input_union_file << "#######\r\n";
        input_union_file << kol << "\r\n";
        input_union_file.close();
        x.Set_Value(0);
        for(int i = 0; i < kol; i++)
            files[i]->See_out(kol, i, max, x);
        for(int i = 0; i < kol; i++)
            files[i]->Add_into(kol, i, max, x);
        for(int i = 0; i < kol; i++)
            delete files[i];
        delete[] files;
    }

    x.exec();
    this->setEnabled(true);
    ui->pushButton_3->click();
}

void Dialog_zip::on_pushButton_2_clicked()
{
    if(ui->lineEdit_2->text() == 0){
        QMessageBox::information(this, "Ошибка!", "Введите имя архива!");
        return;
    }

    QString *qs = new QString(ui->lineEdit_2->text());
    QByteArray qb = qs->toUtf8();
    delete qs;
    char *temp = qb.data();
    strcpy(name_fl, temp);
    strcat(name_fl, ".vix"); // добаление расширения архива

    Dialog_3();
    return;
}
