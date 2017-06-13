#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include "datamanager.h"

namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();

private:
    Ui::Ventana *ui;
    Datamanager *data;
private slots:
    void slot_coordenadasRecept(QStringList listCoordenadas);
    void slot_buscar();
    void slot_parametros(QStringList listParametros);

};

#endif // VENTANA_H
