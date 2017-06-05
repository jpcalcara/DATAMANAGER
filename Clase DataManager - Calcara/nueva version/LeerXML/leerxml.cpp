#include "leerxml.h"
#include "ui_leerxml.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QString>


LeerXML::LeerXML(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeerXML)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager;
    connect(ui->pbAbrir,SIGNAL(clicked()),this,SLOT(slot_readXML()));
   // connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getStart(QNetworkReply*)));
}

LeerXML::~LeerXML()
{
    delete ui;
}

/*void LeerXML::getStart(QString start){

    QByteArray ba = reply.readAll();

    QString origen = "https://maps.googleapis.com/maps/api/directions/xml?origin=";
    origen += start;
    origen += "&key=AIzaSyAIUs8bUuj4nvBIMi2onO3qkrQsSnML8mk";

    manager->get(QNetworkRequest(QUrl(origen)));
}
*/

void LeerXML::slot_readXML()
{
    QString filename = QFileDialog::getOpenFileName(this, "Abrir", "./", "XML (*.xml)");
    qDebug()<< filename;
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QByteArray ba = file.readAll();
    QString origen;
    QString destino;
    QString distancia;
    QString tiempo;

        if(ba.indexOf("<start_location>") && ba.indexOf("</start_location>") ){

        origen = ba.mid(871,93);
        qDebug()<< origen; // muestra todo el <start_location>

        origen.indexOf("<lat>");qDebug()<<origen.indexOf("<lat>");//muestra el indice de comienzo
        origen.indexOf("</lat>");qDebug()<<origen.indexOf("</lat>");//muestra el indice de final
        QString Olat = origen.mid(27,10);// guardo en un string la latitud origen
        qDebug()<<Olat;

        origen.indexOf("<lng>");qDebug()<<origen.indexOf("<lng>");//muestra el indice de comienzo
        origen.indexOf("</lng>");qDebug()<<origen.indexOf("</lng>");//muestra el indice de final
        QString Olng = origen.mid(54,11);
        qDebug()<<Olng;


        qDebug()<< "---PUNTO DE ORIGEN---";
        qDebug()<< "-LATITUD: "+Olat;
        qDebug()<< "-LONGITUD: "+Olng;
        qDebug()<< "---------------------";

        ui->pteTexto->appendPlainText("---PUNTO DE ORIGEN---");
        ui->pteTexto->appendPlainText("-LATITUD: "+Olat);
        ui->pteTexto->appendPlainText("-LONGITUD: "+Olng);
        ui->pteTexto->appendPlainText("---------------------");


        destino = ba.mid(969,89);
        qDebug()<< destino;//muestra todo el <end_location>

        destino.indexOf("<lat>");qDebug()<<destino.indexOf("<lat>");//muestra el indice de comienzo
        destino.indexOf("</lat>");qDebug()<<destino.indexOf("</lat>");//muestra el indice de final
        QString Dlat = destino.mid(25,10);//guardo en un string la latitud destino
        qDebug()<<Dlat;

        destino.indexOf("<lng>");qDebug()<<destino.indexOf("<lng>");//muestra el indice de comienzo
        destino.indexOf("</lng>");qDebug()<<destino.indexOf("</lng>");//muestra el indice de final
        QString Dlng = destino.mid(52,11);//guardo en un string la longitud destino
        qDebug()<<Dlng;

        qDebug()<< "---PUNTO DE DESTINO---";
        qDebug()<< "-LATITUD: "+Dlat;
        qDebug()<< "-LONGITUD: "+Dlng;
        qDebug()<< "---------------------";

        ui->pteTexto->appendPlainText("---PUNTO DE DESTINO---");
        ui->pteTexto->appendPlainText("-LATITUD: "+Dlat);
        ui->pteTexto->appendPlainText("-LONGITUD: "+Dlng);
        ui->pteTexto->appendPlainText("----------------------");

        tiempo.indexOf(("<duration>")); qDebug()<<tiempo.indexOf(("</duration>"));
        tiempo = ba.mid(1133,73);
        qDebug()<<tiempo;

        tiempo.indexOf("<value>");qDebug()<<tiempo.indexOf("<value>");//muestra el indice de comienzo
        tiempo.indexOf("</value>");qDebug()<<tiempo.indexOf("</value>");//muestra el indice de final
        QString Tvalue = tiempo.mid(23,2);
        qDebug()<<Tvalue;

        tiempo.indexOf("<text>");qDebug()<<tiempo.indexOf("<text>");//muestra el indice de comienzo
        tiempo.indexOf("</text>");qDebug()<<tiempo.indexOf("</text>");//muestra el indice de final
        QString Ttext = tiempo.mid(45,5);
        qDebug()<<Ttext;

        qDebug()<< "--------TTEMPO-------";
        qDebug()<<Tvalue+" "+Ttext;
        qDebug()<< "---------------------";

        ui->pteTexto->appendPlainText("-TIEMPO: "+Tvalue + Ttext);

        distancia.indexOf(("<distance>")); qDebug()<<distancia.indexOf(("</distance>"));
        distancia = ba.mid(1319,76);
        qDebug()<<distancia;

        distancia.indexOf("<value>");qDebug()<<distancia.indexOf("<value>");//muestra el indice de comienzo
        distancia.indexOf("</value>");qDebug()<<distancia.indexOf("</value>");//muestra el indice de final
        QString Dvalue = distancia.mid(24,3);
        qDebug()<<Dvalue;

        distancia.indexOf("<text>");qDebug()<<distancia.indexOf("<text>");//muestra el indice de comienzo
        distancia.indexOf("</text>");qDebug()<<distancia.indexOf("</text>");//muestra el indice de final
        QString Dtext = distancia.mid(47,6);
        qDebug()<<Dtext;

        qDebug()<< "------DISTANCIA------";
        qDebug()<<Dvalue+" "+Dtext;
        qDebug()<< "---------------------";

        ui->pteTexto->appendPlainText("-DISTANCIA: "+Dvalue + Dtext);

    }//fin del if


  /*  QDomDocument doc;
    doc.setContent(&file);
    //file.close();
  //  qDebug()<< file.size();

    QDomElement root = doc.documentElement();//se extrae la Raiz
    //QString nameRoot = root.tagName(); //obtengo nombre de la raiz
    //QString Board=root.attribute("");// atributo de la raiz
    QDomElement childRoot = root.firstChild().toElement();//obtengo el primer hijo de la raiz

    QString latitud;
    QString longitud;
    QString Dvalue;//distacia
    QString Dtext;//distancia
    QString Tvalue;//tiempo
    QString Ttext;//tiempo
    */
/*
    //mientras exista un hijo
    while(!childRoot.isNull())
    {
        if(childRoot.tagName()=="start_location"){
            //obtento el primer hijo de "star_location"
            QDomElement child = childRoot.firstChild().toElement();

            //leo cada hijo
            while(!child.isNull())
            {
                //leo el latitud y longitud
                if(child.tagName()=="lat"){
                    latitud = child.firstChild().toText().data();
                    if(child.tagName()=="lng"){
                    longitud = child.firstChild().toText().data();
                    }
                }
                //pasa al siguiente hijo del hijo
                //child = child.nextSibling().toElement();
            }
            qDebug()<<"DATOS DE ORIGEN";
            qDebug()<<"-Latitud: "+latitud;
            qDebug()<<"-Longitud: "+longitud;
        }
       if(childRoot.tagName()=="end_location"){
            QDomElement child = childRoot.firstChild().toElement();

            //leo cada hijo
            while(!child.isNull())
            {
                //leo el latitud y longitud
                if(child.tagName()=="lat"){
                    latitud = child.firstChild().toText().data();
                }
                if(child.tagName()=="lng"){
                    longitud = child.firstChild().toText().data();
                }

            }//fin del while
            qDebug()<<"DATOS DE DESTINO";
            qDebug()<<"-Latitud: "+latitud;
            qDebug()<<"-Longitud: "+longitud;
        }
       if(childRoot.tagName()=="duration"){
            QDomElement child = childRoot.firstChild().toElement();

            while(!child.isNull())
            {
                if(child.tagName()=="value"){
                    Dvalue = child.firstChild().toText().data();
                }
                if(child.tagName()=="text"){
                    Dtext = child.firstChild().toText().data();
                }
            }//fin del while
            qDebug()<<"TIEMPO";
            qDebug()<<Dvalue+" "+Dtext;

        }
       if(childRoot.tagName()=="distance"){
            QDomElement child = childRoot.firstChild().toElement();

            while(!child.isNull())
            {
                if(child.tagName()=="value"){
                    Tvalue = child.firstChild().toText().data();
                }
                if(child.tagName()=="text"){
                    Ttext = child.firstChild().toText().data();
                }
            }//fin del while

            qDebug()<<"DISTANCIA";
            qDebug()<<Tvalue+" "+Ttext;
        }
        //para leer el siguiente start_location
       childRoot = childRoot.nextSibling().toElement();

    }*/

}

