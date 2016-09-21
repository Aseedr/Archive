#include "ununion.h"

Ununion::Ununion() : input_name(NULL), name_f(NULL), size_f(0) {}

Ununion::Ununion(string str) {
    input_name = str;
}

Ununion::Ununion(string str, long long int kol) {
    name_f = str;
    size_f = kol;
}

Ununion::~Ununion() {}

void Ununion::See() {
    cout << name_f << endl;
    cout << size_f << endl;
}

void Ununion::Add(double max, Dialog_pros &x) {
    int koll_files = 0;
    Ununion **file;

    fstream input_file_ununion;
    input_file_ununion.open(input_name, ios::in | ios::binary);
    string temp;
    long long int buff;
    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        if (input_file_ununion.get() == '#')
            count++; // сичитывания количества ключевых пометок
    }
    if(count == 5){
        input_file_ununion.seekg(0);
        for (int i = 0; i < 5; i++) {
            if (input_file_ununion.get() == '#')
                count++; // сичитывания количества ключевых пометок
        }
        count = SIZE;
    }
    if (count == SIZE) {
        input_file_ununion >> koll_files;
        file = new Ununion*[koll_files];
        for (int i = 0; i < koll_files; i++) {
            input_file_ununion >> temp; // считывание пометок
            input_file_ununion >> buff; //  счиьывание пометок
            file[i] = new Ununion(temp, buff);
        }
        input_file_ununion.get();
        for (int i = 0; i < koll_files; i++) {
            file[i]->Add_out(input_file_ununion);
            delete file[i]; // очищение данных

            x.Set_Value(max / (koll_files / (i + 1))); // вывод процентов
            //x.exec();
        }
        delete[] file; // очищение данных
    }

    input_file_ununion.close();
    return;
}

void Ununion::Add_out(fstream &input_file_ununion) {
    fstream output_file_ununion;
    output_file_ununion.open(name_f, ios::app | ios::binary);

    for (int i = 0; i < size_f; i++) {
        wchar_t temp = input_file_ununion.get();
        if (i != 0 && temp != 0)
            output_file_ununion.put(temp); // перезапись
    }

    output_file_ununion.close();
}
