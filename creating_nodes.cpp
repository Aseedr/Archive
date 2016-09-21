#include "creating_nodes.h"

Creating_nodes::Creating_nodes(wchar_t s, int num) {
    symbol = s;
    number_of_occurrences = num;
    left = NULL;
    right = NULL;
}

Creating_nodes::Creating_nodes(Creating_nodes *l, Creating_nodes *r) {
    left = l;
    right = r;
    number_of_occurrences = l->number_of_occurrences +
        r->number_of_occurrences;
    symbol = 0;
}

Creating_nodes::Creating_nodes() : number_of_occurrences(0), symbol(0),
left(NULL), right(NULL) {}

Creating_nodes::~Creating_nodes() {}

bool Creating_nodes::Compare::operator()(Creating_nodes *left, Creating_nodes *right) const {
    return left->number_of_occurrences < right->number_of_occurrences;
} // сравнение двух членок калсса

void Creating_nodes::Bild_table_code(Creating_nodes *vertex, vector<bool> &code,
    map<wchar_t, vector<bool> > &code_table) { // создание асациативного массива
    if (vertex->left != NULL) { // прохождение по ветвям
        code.push_back(0);
        Bild_table_code(vertex->left, code, code_table);
    }
    if (vertex->right != NULL) { // прохождение по ветвям
        code.push_back(1);
        Bild_table_code(vertex->right, code, code_table);
    }
    if (vertex->symbol) {
        code_table[vertex->symbol] = code;
    }
    if (code.size() != 0) {
        code.pop_back();
    }
}

void Creating_nodes::print(Creating_nodes *vertex, unsigned k = 0) { // просмотр дерева
    fstream temp;
    temp.open("tree.txt", ios::app);
    if (vertex != NULL) { // прохождение по ветвям
        if(vertex->left != NULL){
            print(vertex->left, k + 3);
        }
        for (unsigned i = 0; i < k; i++) {
            temp << "  ";
        }
        if (vertex->symbol) {
            temp << vertex->number_of_occurrences <<
                " (" << vertex->symbol << ")" << endl;
        }
        else {
            temp << vertex->number_of_occurrences << endl;
        }
        if(vertex->right != NULL){
            print(vertex->right, k + 3);
        }
    }
}

void Creating_nodes::Delete(Creating_nodes *vertex) { // удалние дерева
    if (vertex != NULL) {
        Delete(vertex->left);
        Delete(vertex->right);
        delete(vertex);
    }
}

void Creating_nodes::unzip(fstream &input_file, fstream &output_file,
    wchar_t &syml, int &count, Creating_nodes *vertex,
    Creating_nodes *&bypass) { // разархивация
    output_file.clear();
    bool buff = syml & (1 << (BYTE_SIZE - 1 - count));
    //cout << buff;
    //system("pause");
    if (buff)
        bypass = bypass->right;
    else
        bypass = bypass->left;
    if (bypass->left == NULL && bypass->right == NULL) {
        //input_file << bypass->symbol;
        input_file.put(bypass->symbol);
        bypass = vertex; // доходим до символа
    }
    count++;
    if (count == BYTE_SIZE) {
        count = 0; // перекодировка и вывод в файл
        syml = output_file.get();
        //cout << syml;
        //system("pause");
    }
}
