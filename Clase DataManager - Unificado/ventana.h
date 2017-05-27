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

    DataManager * dataManager;

private slots:
    void slot_probar();
    void slot_coordenadasRecibidas(QList<QString> lista);
    void slot_lugaresRecibidos(QList<QString> lista);
    void slot_Origen(QString Olat, QString Olng);
    void slot_Destino(QString Dlat, QString Dlng);
};

#endif // VENTANA_H
