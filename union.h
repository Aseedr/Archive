#ifndef UNION
#define UNION
#include "main.h"
#include "dialog_pros.h"

class Union : public Dialog_pros {
private:
    string out_name;
    string name_f;

public:
    Union();
    Union(string, string);
    ~Union();

    void See_out(int, int, int, Dialog_pros &); // пометки

    void Add_into(int, int, int, Dialog_pros &); // перезапись
};
#endif // UNION

