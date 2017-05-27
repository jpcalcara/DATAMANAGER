#include <QApplication>
#include "leerxml.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LeerXML w;
    w.show();
    w.setWindowTitle("XML Reader");

    return a.exec();
}

