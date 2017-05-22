#include<QApplication>
#include "ventana.h"
#include<QNetworkProxyFactory>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    Ventana b;
    b.show();

    return a.exec();
}
