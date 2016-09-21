#include "unzip.h"
#include "creating_nodes.h"

Unzip::Unzip() : input_name(NULL), output_name(NULL) {}

Unzip::Unzip(string str1, string str2) {
    input_name = str1;
    output_name = str2;
}

Unzip::~Unzip() {}

void Unzip::create_unzip(int count, Dialog_pros &x, int start) const {
    fstream input_file;
    fstream output_file;
    int table_size = 0;
    output_file.open(output_name, ios::in | ios::binary);
    input_file.open(input_name, ios::app | ios::binary);

    if(count == 3){ // смещние по файлу
        char temp_mass[MAS_SIZE];
        for(int i = 0; i < 3; i++)
            output_file.get();
        output_file >> temp_mass;
    }

    map<wchar_t, int> character_count;

    output_file >> table_size;
    output_file.get();

    for (int i = 0; i < table_size; i++) {
        wchar_t symbol = output_file.get();
        int num = 0; // считывание символов из файла
        output_file >> num;
        output_file.get(); // создание map символ-встреч
        character_count.insert(pair<wchar_t, int>(symbol, num));
    }
    map<wchar_t, int>::iterator itr_map;
    creating_tree(character_count, itr_map, input_file,
                  output_file, x, start); // переход на дерево
}

void Unzip::creating_tree(map<wchar_t, int> &character_count,
    map<wchar_t, int>::iterator &itr_map, fstream &input_file,
    fstream &output_file, Dialog_pros &x, int start) const {

    int result = 0, result1 = 0;
    double count = character_count.size(), max = 20, flag = 0;

    list<Creating_nodes*> node;
    for (itr_map = character_count.begin();
    itr_map != character_count.end(); itr_map++) {
        Creating_nodes *pointer = new Creating_nodes(itr_map->first,
            itr_map->second); // создние списка из указателей элементов дерева
        node.push_back(pointer);
        flag++;
        if(flag != 0){ // вывод процентов
            result = max / (count / flag);
            if(result > 0 && result > start && result > result1){
                result1 = result;
                x.Set_Value(result);
                //x.exec();
            }
        }
    }

    result = 0; result1 = 0;
    count = character_count.size() - 1, max = 90, flag = 0;

    while (node.size() != 1) { // создание дерева
        node.sort(Creating_nodes::Compare());
        Creating_nodes *left_side = node.front();
        node.pop_front();
        Creating_nodes *right_side = node.front();
        node.pop_front();
        Creating_nodes *side = new Creating_nodes(left_side, right_side);
        node.push_back(side);
        flag++;
        if(flag != 0){ // вывод процентов
            result = max / (count / flag);
            if(result > 20 && result > start && result > result1){
                result1 = result;
                x.Set_Value(result);
                //x.exec();
            }
        }
    }
    Creating_nodes *vertex = node.front();

    write(input_file, output_file, vertex, x, start); // перехо на запись
}

void Unzip::write(fstream &input_file, fstream &output_file, Creating_nodes *vertex,
                  Dialog_pros &x, int start) const {
    Creating_nodes *bypass = vertex;
    int count = 0;
    wchar_t syml;
    syml = output_file.get();
    while (!output_file.eof()) {
        unzip(input_file, output_file, // перекодирование символов
            syml, count, vertex, bypass); // и запись в файл
    }

    start = 100;
    x.Set_Value(start); // вывод процентов

    input_file.close();
    output_file.close();

    Delete(vertex); // удаление дерева
}
