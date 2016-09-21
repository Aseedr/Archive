#ifndef UNUNION
#define UNUNION
#include "main.h"
#include "dialog_pros.h"

class Ununion : public Dialog_pros {
private:
    string input_name;
    string name_f;
    long long int size_f;
public:
    Ununion();
    Ununion(string);
    Ununion(string, long long int);
    ~Ununion();

    void See(); // просмотр данных

    void Add(double, Dialog_pros &); // пометки

    void Add_out(fstream &); // перезапись
};
#endif // UNUNION

