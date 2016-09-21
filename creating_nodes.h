#ifndef CREATING_NODES
#define CREATING_NODES
#include "main.h"


class Creating_nodes {
private:
    int number_of_occurrences;
    wchar_t symbol;
    Creating_nodes *left;
    Creating_nodes *right;

public:
    Creating_nodes(wchar_t, int); // создания ячейки дерева

    Creating_nodes(Creating_nodes *,
                   Creating_nodes *); // расположение в дереве

    Creating_nodes();

    ~Creating_nodes();

    class Compare { // класс для сравнения
    public: // возвращает меньший элемент
        bool operator()(Creating_nodes *, Creating_nodes *) const;
    };

    static void Bild_table_code(Creating_nodes *, vector<bool> &,
        map<wchar_t, vector<bool> > &); // построения таблицы символ-код

    static void print(Creating_nodes *, unsigned); // просмотр дерева

    static void Delete(Creating_nodes *); // очищение дерева

    static void unzip(fstream &, fstream &,
        wchar_t &, int &, Creating_nodes *,
        Creating_nodes *&); // функция перевода в другую кодировку
};
#endif // CREATING_NODES

