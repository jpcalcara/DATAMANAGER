#include "ventana.h"
#include <QApplication>
#include <QNetworkProxyFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    Ventana w;
    w.show();

    return a.exec();
}
