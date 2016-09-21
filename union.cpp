#include "union.h"

Union::Union() : out_name(NULL), name_f(NULL) {}

Union::Union(string str1, string str2) {
    out_name = str1;
    name_f = str2;
}

Union::~Union() {}

void Union::See_out(int kol, int i, int max, Dialog_pros &p) {
    fstream input_file_union;
    fstream output_file_union;

    int x = 0;
    if(i != 0)
        x = max / (kol / i); //подсчет процентов
    if(i + 1 == kol)
        x = max;

    input_file_union.open(out_name, ios::app | ios::binary);
    output_file_union.open(name_f, ios::in | ios::binary);
    long long int koll_sym = 0;

    while (!output_file_union.eof()) {
        output_file_union.get();
        koll_sym++; // количество символов в файле
    }

    input_file_union << name_f << "\r\n"; // пометака
    input_file_union << koll_sym << "\r\n"; // пометка

    input_file_union.close();
    output_file_union.close();

    p.Set_Value(x); // вывод процентов
    //p.exec();
}

void Union::Add_into(int kol, int i, int max, Dialog_pros &p) {
    fstream input_file_union;
    fstream output_file_union;

    int x = max;
    if(i != 0)
        x = max / (kol / i) + max; // подсчет процентов
    if(i + 1 == kol)
        x = max + max;

    input_file_union.open(out_name, ios::app | ios::binary);
    output_file_union.open(name_f, ios::in | ios::binary);

    while (!output_file_union.eof()) {
        wchar_t symbol = output_file_union.get();
        input_file_union.put(symbol); // перезапись дынных
    }

    input_file_union.close();
    output_file_union.close();

    p.Set_Value(x); //вывод процентов
    //p.exec();
}
