#ifndef ZIP
#define ZIP
#include "main.h"
#include "creating_nodes.h"
#include "dialog_pros.h"

class Zip : public Creating_nodes, public Dialog_pros {
private:
    string input_name;
    string output_name;

public:

    Zip();

    Zip(string, string);

    ~Zip();

    void create_zip(Dialog_pros &, int) const; // начало

    void creating_tree(map<wchar_t, int> &, // дерево
        map<wchar_t, int>::iterator &, fstream &,
        fstream &, Dialog_pros &, int, double) const;

    void write(fstream &, fstream &, Creating_nodes *&,
               Dialog_pros &, int, double) const; // запись

};
#endif // ZIP
