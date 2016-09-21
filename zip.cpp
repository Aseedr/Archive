#include "creating_nodes.h"
#include "zip.h"


Zip::Zip() : input_name(NULL), output_name(NULL) {}

Zip::Zip(string str1, string str2) {
    input_name = str1;
    output_name = str2;
}

Zip::~Zip() {}

void Zip::create_zip(Dialog_pros &x, int start) const { // считывание
    fstream input_file;
    fstream output_file;
    double kooll = 0;
    output_file.open(output_name, ios::app | ios::binary);
    input_file.open(input_name, ios::in | ios::binary);

    map<wchar_t, int> character_count;

    while (!input_file.eof()) {
        wchar_t symbol = input_file.get();
        kooll++; // счетчит количество символов в файле
        character_count[symbol]++;
    }

    int result = 0, result1 = 0;
    double count = character_count.size(), max = 20, flag = 0;

    output_file << character_count.size() << endl; // размер map массива
    map<wchar_t, int>::iterator itr_map;
    for (itr_map = character_count.begin();
    itr_map != character_count.end(); itr_map++) { // вывод сим - вход
        //cout << int(itr_map->first) << ":";
        //output_file << itr_map->first; //***
        output_file.put(itr_map->first);
        //cout << itr_map->second << endl;
        output_file << itr_map->second << endl;//***
        //output_file.put(itr_map->second);
        //output_file.put(10);
        flag++;
        if(flag != 0){ // вывод процентов
            result = max / (count / flag);
            if(result > 0 && result > start && result > result1){
                result1 = result;
                x.Set_Value(result);
                x.exec();
            }
        }
    }
    creating_tree(character_count, itr_map, input_file,
                  output_file,x, start, kooll); // переход на дерево
}

void Zip::creating_tree(map<wchar_t, int> &character_count,
    map<wchar_t, int>::iterator &itr_map, fstream &input_file,
    fstream &output_file, Dialog_pros &x, int start, double kooll) const {

    int result = 0, result1 = 0;
    double count = character_count.size(), max = 40, flag = 0;

    list<Creating_nodes*> node;
    for (itr_map = character_count.begin();
    itr_map != character_count.end(); itr_map++) {
        Creating_nodes *pointer = new Creating_nodes(itr_map->first,
            itr_map->second); // список из указателей на элементы дерева
        node.push_back(pointer);
        flag++;
        if(flag != 0){ // вывод процентов
            result = max / (count / flag);
            if(result > 20 && result > start && result > result1){
                result1 = result;
                x.Set_Value(result);
                x.exec();
            }
        }
    }

    result = 0; result1 = 0;
    count = character_count.size() - 1, max = 60, flag = 0;

    while (node.size() != 1) { // создание дерева
        node.sort(Compare());
        Creating_nodes *left_side = node.front();
        node.pop_front();
        Creating_nodes *right_side = node.front();
        node.pop_front();
        Creating_nodes *side = new Creating_nodes(left_side, right_side);
        node.push_back(side);
        flag++;
        if(flag != 0){ // вывод процентов
            result = max / (count / flag);
            if(result > 40 && result > start && result > result1){
                result1 = result;
                x.Set_Value(result);
                x.exec();
            }
        }
    }
    Creating_nodes *vertex = node.front(); // начало дерева
    //print(vertex, 0); // просмотр дерева

    write(input_file, output_file, vertex, x,
          start, kooll); //переход на запись
}

void Zip::write(fstream &input_file, fstream &output_file,
                Creating_nodes *&vertex, Dialog_pros &x,
                int start, double kooll) const {
    vector<bool> code;
    map<wchar_t, vector<bool> > code_table; // map  символ-код
    Bild_table_code(vertex, code, code_table); // создание map

    int result = 0, result1 = 0;
    double flag = 0, max = 100;

    int count = 0; wchar_t buff = 0;
    input_file.clear();
    input_file.seekg(0);
    while (!input_file.eof()) { // запись в файл
        wchar_t symbol = input_file.get();
        flag++;
        vector<bool> code = code_table[symbol];

        for (unsigned int i = 0; i < code.size(); i++) {
            buff = buff | code[i] << (BYTE_SIZE - 1 - count);
            count++;
            if (count == BYTE_SIZE) {
                count = 0;
                //output_file << buff;
                output_file.put(buff); //запись символа в файл
                buff = 0;
            }
        }
        if(flag != 0){ // вывод процентов
            result = max / (kooll / flag);
            if(result > 60 && result > start && result > result1){
                result1 = result;
                x.Set_Value(result);
                x.exec();
            }
        }
    }

    input_file.close();
    output_file.close();
    Delete(vertex); // очищение дерева
}
