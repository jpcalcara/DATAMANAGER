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

    //agregara aca los connects correspondientes que faltan
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::slot_probar()
{
    ui->pteMostrar->clear();
    dataManager->getCoordinates(ui->leDireccion->text());

    //agregar aca los pedidos get para obtener datos
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
