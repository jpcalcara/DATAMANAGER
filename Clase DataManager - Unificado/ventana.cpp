#include "ventana.h"
#include "ui_ventana.h"

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);

    dataManager = new DataManager;

    connect(ui->pbDireccion, SIGNAL(pressed()), this, SLOT(slot_probar()));
    connect(dataManager, SIGNAL(receivedCoordinates(QList<QString>)),
            this, SLOT(slot_coordenadasRecibidas(QList<QString>)));
    connect(dataManager,SIGNAL(receivedSites(QList<QString>)),
            this,SLOT(slot_lugaresRecibidos(QList<QString>)));
    connect(dataManager,SIGNAL(receivedSites(QList<QString>)),
            this,SLOT(slot_Origen(QString,QString)));
    connect(dataManager,SIGNAL(receivedSites(QList<QString>)),
            this,SLOT(slot_Destino(QString,QString)));
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::slot_probar()
{
    ui->pteMostrar->clear();
    dataManager->getCoordinates(ui->leDireccion->text());

    dataManager->getOrigen(ui->lePartida->text());
    dataManager->getDestino(ui->leLlegada->text());
}

void Ventana::slot_coordenadasRecibidas(QList<QString> lista)
{
    ui->pteMostrar->appendPlainText("Lista de Coordenadas - \n");

    for(int i=0;i<lista.size();i++)
    {
        ui->pteMostrar->appendPlainText(lista.at(i));
    }

    ui->pteMostrar->appendPlainText("\n");

    //insertamos en la busqueda de lugares, las coordenadas que acabamos de obtener
    dataManager->getSites(ui->leBusqueda->text(),lista);
}

void Ventana::slot_lugaresRecibidos(QList<QString> lista)
{
    ui->pteMostrar->appendPlainText("Lista de Lugares Encontrados - \n");

    for(int i=0;i<lista.size();i++)
    {
        ui->pteMostrar->appendPlainText(lista.at(i));
    }

    ui->pteMostrar->appendPlainText("\n");
}

void Ventana::slot_Origen(QString Olat, QString Olng){

    ui->pteMostrar->appendPlainText("-Coordenadas de ORIGEN: \n");

    ui->pteMostrar->appendPlainText("-LATITUD: "+Olat);
    ui->pteMostrar->appendPlainText("-LONGITUD: "+Olng);

}

void Ventana::slot_Destino(QString Dlat, QString Dlng){

    ui->pteMostrar->appendPlainText("-Coordenadas de DESTINO: \n");

    ui->pteMostrar->appendPlainText("-LATITUD: "+Dlat);
    ui->pteMostrar->appendPlainText("-LONGITUD: "+Dlng);

}
