#include "readxml.h"
#include "ui_readxml.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QTextDocument>

ReadXml::ReadXml(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadXml)
{
    ui->setupUi(this);
    //para generar un archivo XML nuevo
   /* QFile xml("nuevo.xml");
    xml.open(QIODevice::WriteOnly);
    QXmlStreamWriter escritorXml(&xml);
    QXmlStreamReader lectorXml(&xml);

    escritorXml.writeStartDocument();
    escritorXml.writeEndDocument();

    QFile salida("nuevo.xml");
    salida.open(QIODevice::ReadOnly);
    QTextStream leer(&salida);
    salida.close();
*/
    connect(ui->pbAbrir, SIGNAL(clicked()), this, SLOT(slot_abrirXML()));

}

ReadXml::~ReadXml()
{
    delete ui;
}

void ReadXml::slot_abrirXML()
{
    /*QString files = QFileDialog::getOpenFileName(this, "Abrir", "./", "XML (*.xml)");
    QFile *file = new QFile(files);
    if ( !file->open (QIODevice::ReadOnly | QIODevice::Text) )
        return;
     while ( !file->atEnd() )  {
         QByteArray linea = file->readAll();
         qDebug() << linea;
       }
*/

    auto filename = QFileDialog::getOpenFileName(this, "Abrir", "./", "XML (*.xml)");
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QDomDocument doc;
    doc.setContent(&file);
    file.close();
    auto root = doc.firstChildElement("maps");
    auto ix = root.firstChildElement("start_location");

    if (!ix.isNull()){
        auto lat = ix.firstChild().toElement().text();
        auto lng = ix.firstChild().nextSibling().toElement().text();

        ix = ix.nextSibling().toElement(); //pasa al siguiente elemento
        qDebug() <<"****PUNTO DE PARTIDA****";
        qDebug() << "-Latitud: " +lat;
        qDebug() << "-Longitud: "+lng;
        qDebug() <<"************************";
    }
        auto root1 = doc.firstChildElement("maps");
        auto ix1 = root.firstChildElement("distance");

        if(!ix1.isNull()){
            auto value = ix.firstChild().nextSibling().toElement().text();
            auto text = ix.firstChild().nextSibling().nextSibling().toElement().text();

        qDebug() << "-Distancia: "+value+text;

        }

        auto root2 = doc.firstChildElement("maps");
        auto ix2 = root.firstChildElement("duration");

        if(!ix1.isNull()){
            auto value = ix2.firstChild().nextSibling().toElement().text();
            auto text = ix2.firstChild().nextSibling().nextSibling().toElement().text();

        qDebug() << "-Duracion: "+value+text;

        }
        auto root3 = doc.firstChildElement("maps");
        auto ix3 = root.firstChildElement("end_location");

        if (!ix3.isNull()){
            auto lat = ix3.firstChild().toElement().text();
            auto lng = ix3.firstChild().nextSibling().toElement().text();

            qDebug() <<"****PUNTO DE LLEGADA****";
            qDebug() << "-Latitud: " +lat;
            qDebug() << "-Longitud: "+lng;
        }
       // QByteArray linea = file.readAll();
        //qDebug() << linea.size();

}
