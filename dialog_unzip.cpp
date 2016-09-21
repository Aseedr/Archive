#include "dialog_unzip.h"
#include "ui_dialog_unzip.h"
#include "dialog_pros.h"
#include "main.h"
#include "ununion.h"
#include "unzip.h"
#include <fstream>
#include <QMessageBox>


Dialog_unzip::Dialog_unzip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_unzip)
{
    ui->setupUi(this);
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(close()));
    ui->radioButton_2->setDisabled(1);
    ui->radioButton->click();
    ui->lineEdit_2->setDisabled(1);
    ui->pushButton_2->setDisabled(1);
    ui->pushButton_3->setDisabled(1);
    ui->pushButton_4->setDisabled(1);
    ui->lineEdit_3->setDisabled(1);
    ui->lineEdit_4->setDisabled(1);
    ui->lineEdit_5->setDisabled(1);
}

Dialog_unzip::~Dialog_unzip()
{
    delete ui;
}

void Dialog_unzip::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == 0){
        return;
    }
    std::fstream input_file_name;

    QString *qs = new QString(ui->lineEdit->text());
    QByteArray qb = qs->toUtf8();
    delete qs; // перекодировка из qstring в char*
    char *temp = qb.data();

    input_file_name.open(temp, std::ios::in | std::ios::binary);
    if(!input_file_name){
        QMessageBox::information(this, "Ошибка!", "Файл не найден!");
        return;
    }
    name_nf = temp;

    for (int i = 0; i < SIZE; i++) {
        if (input_file_name.get() == '#')
            count++; // считывание пометок
    }

    input_file_name.clear();
    input_file_name.seekg(0);

    if(count == 3){ // выбираем тип архива
        ui->lineEdit_5->setText("Средняя");
        ui->lineEdit_4->setText("Хаффмана");
        for(int i = 0; i < 3; i++)
            input_file_name.get();
        kol = 1;
        input_file_name >> mass_in[kol - 1];
        ui->textBrowser_2->append(mass_in[kol - 1]);
    }
    if(count == 5){ // выбираем тип архива
        ui->lineEdit_5->setText("Средняя");
        ui->lineEdit_4->setText("Хаффмана");
        for(int i = 0; i < 5; i++)
            input_file_name.get();
        input_file_name >> kol;
        int buuff = 0;
        for(int i = 0; i < kol; i++){
            input_file_name >> mass_in[i];
            input_file_name >> buuff;
            ui->textBrowser_2->append(mass_in[i]);
        }
    }
    if(count == 7){ // выбираем тип архива
        ui->lineEdit_5->setText("Нет");
        ui->lineEdit_4->setText("Нет");
        int buff = 0;
        for(int i = 0; i < 7; i++)
            input_file_name.get();

        input_file_name >> kol;

        for(int i = 0; i < kol; i++){
            input_file_name >> mass_in[i];
            input_file_name >> buff;
            ui->textBrowser_2->append(mass_in[i]);
        }
    }

    input_file_name.close();

    ui->lineEdit_3->setText(ui->lineEdit->text());
    ui->lineEdit->clear();
    // блокировка и разлокировка определенных клавиш
    ui->lineEdit->setDisabled(1);
    ui->pushButton->setDisabled(1);

    ui->lineEdit_2->setDisabled(0);
    ui->pushButton_2->setDisabled(0);
    ui->pushButton_3->setDisabled(0);
}

void Dialog_unzip::on_pushButton_3_clicked()
{
    char temp_mas[MAS_SIZE];
    for(int i = 0; i < kol2; i++){
        strcpy(mass_out[i], temp_mas);
    } // очищение массива выходных файлов
    kol2 = 0;
    ui->textBrowser->clear();
    ui->pushButton_4->setDisabled(1);
}

void Dialog_unzip::Dialog_3(){
    this->setEnabled(false);
    Dialog_pros x; // окно процессса
    x.setWindowTitle("Разархивация");
    x.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    x.show();

    if(count == 3){ // выбор действия взависимости от данных
        x.Set_Value(0);
        Unzip *u; int start = 0; // разархирация
        u = new Unzip(mass_out[kol2 - 1], name_nf);
        u->create_unzip(count, x, start);
        delete u;
    }
    if(count == 5){
        x.Set_Value(0);

        double max = 50;
        Ununion *p; // разделение
        p = new Ununion(name_nf);
        p->Add(max, x);
        delete p;

        Unzip **files; int start = 50; // разархивация
        files = new Unzip*[kol2];
        for(int i = 0; i < kol2; i++){
            char sss[MAS_SIZE];
            strcpy(sss, mass_out[i]);
            int size_mt = strlen(sss);
            size_mt = size_mt - 4;
            sss[size_mt] = '\0';
            files[i] = new Unzip(sss, mass_out[i]);
            files[i]->create_unzip(count, x, start);
            delete files[i];
            remove(mass_out[i]); // удаление кэша
        }
        delete[] files;

        bool flag = 0; // удаление кэша
        for(int i = 0; i < kol; i++){
            flag = 0;
            for(int k = 0; k < kol2; k++){
                if(strcmp(mass_in[i], mass_out[k]) == 0)
                    flag = 1;
            }
            if(flag == 0){
                remove(mass_in[i]);
            }
        }
    }
    if(count == 7){
        double max = 100;
        Ununion *p; // разделение
        p = new Ununion(name_nf);
        p->Add(max, x);
        delete p;

        bool flag = 0; // удаление кэша
        for(int i = 0; i < kol; i++){
            flag = 0;
            for(int k = 0; k < kol2; k++){
                if(strcmp(mass_in[i], mass_out[k]) == 0)
                    flag = 1;
            }
            if(flag == 0){
                remove(mass_in[i]);
            }
        }
    }

    x.exec();
    this->setEnabled(true);
    ui->pushButton_5->click();
}

void Dialog_unzip::on_pushButton_2_clicked()
{
    if(ui->lineEdit_2->text() == 0){
        return;
    }

    QString *qs = new QString(ui->lineEdit_2->text());
    QByteArray qb = qs->toUtf8();
    delete qs;
    char *temp = qb.data();

    if(ui->lineEdit_2->text() == "all"){
        ui->pushButton_3->click(); // функция all
        kol2 = kol;
        for(int i = 0; i < kol; i++){
            strcpy(mass_out[i], mass_in[i]);
            ui->textBrowser->append(mass_in[i]);
        }
        ui->lineEdit_2->clear();
        ui->pushButton_4->setDisabled(0);
        return;
    }

    bool flag = 0, flag2 = 1;

    for(int i = 0; i < kol; i++){
        if(strcmp(temp, mass_in[i]) == 0){
            if(kol2 > 0){
                for(int k = 0; k < kol2; k++){ //добавление в массив выходных файлов
                    if(strcmp(mass_out[k], temp) == 0){
                        flag = 0; flag2 = 0;
                    }
                }
            }
            if(flag2 == 0)
                break;
            kol2++;
            strcpy(mass_out[kol2 - 1], mass_in[i]);
            flag = 1;
        }
    }
    if(flag == 1){
        ui->textBrowser->append(ui->lineEdit_2->text());
        ui->lineEdit_2->clear();
        ui->pushButton_4->setDisabled(0);
    }
    else{
        QMessageBox::information(this, "Ошибка!", "Файл не найден, либо уже добавлен!"); //окошко ошибки
        return;
    }
}

void Dialog_unzip::on_pushButton_4_clicked()
{
    Dialog_3();
}
