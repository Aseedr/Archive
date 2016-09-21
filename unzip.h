#ifndef UNZIP
#define UNZIP
#include "main.h"
#include "creating_nodes.h"
#include "dialog_pros.h"
#include "dialog_unzip.h"

class Unzip : public Creating_nodes, public Dialog_pros {
private:
    string input_name;
    string output_name;

public:

    Unzip();

    Unzip(string, string);

    ~Unzip();

    void create_unzip(int, Dialog_pros &, int) const; // начало

    void creating_tree(map<wchar_t, int> &, // дерево
        map<wchar_t, int>::iterator &, fstream &,
        fstream &, Dialog_pros &, int) const;

    void write(fstream &, fstream &, Creating_nodes *,
               Dialog_pros &, int) const; // запись
};
#endif // UNZIP

