#include "ventana.h"
#include "ui_ventana.h"
#include "datamanager.h"

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana){

    ui->setupUi(this);
    data = new Datamanager();
    //data->getCoordenadas("Origenlat", "Origenlng",  "Destinolat",  "Destinolng");

    connect(data,SIGNAL(signal_coordenadas(QStringList)),this,SLOT(slot_coordenadasRecept(QStringList)));
    connect(data,SIGNAL(signal_parametros(QStringList)),this,SLOT(slot_parametros(QStringList)));
    connect (ui->pbBuscar,SIGNAL(clicked(bool)),this,SLOT(slot_buscar()));

}

void Ventana::slot_coordenadasRecept(QStringList listCoordenadas){
        for(int i=0;i<listCoordenadas.size();i++)
        {
            ui->plainTextEdit->appendPlainText(listCoordenadas.at(i));
            qDebug()<<listCoordenadas.at(i);
        }
        ui->plainTextEdit->appendPlainText("\n");
}
void Ventana::slot_buscar(){
    data->getCoordenadas(ui->leOrigenLat->text(),
    ui->leOrigenLng->text(),ui->leDestinoLat->text(),
                         ui->leDestinolng->text());
}

void Ventana::slot_parametros(QStringList listParametros){

    for(int i=0;i<listParametros.size();i++)
    {
        ui->plainTextEdit->appendPlainText(listParametros.at(i));
    }
    ui->plainTextEdit->appendPlainText("\n");
    ui->leTiempo->setText(listParametros.at(0));
    ui->leDistancia->setText(listParametros.at(1));
}
Ventana::~Ventana(){
    delete ui;
}
