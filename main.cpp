#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("Архиватор VIX");
    //w.setWindowFlags(w.windowFlags() & ~Qt::WindowContextHelpButtonHint); //скрыть кнопку помощи
    w.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint); //скрыть все кнопки
    w.show();

    return a.exec();
}
