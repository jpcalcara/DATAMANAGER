#include "datamanager.h"
#include <QString>
#include <QDebug>
#include <QByteArray>

Datamanager::Datamanager(QObject *parent) : QObject(parent)
{
    managerCoor = new QNetworkAccessManager();

    connect(managerCoor,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_coordenadas(QNetworkReply *)));
}

Datamanager::~Datamanager(){

}

void Datamanager::getCoordenadas(QString Origenlat, QString Origenlng, QString Destinolat, QString Destinolng){

    QString base = "https://maps.googleapis.com/maps/api/directions/xml?";
    QString coor = "origin=" + Origenlat + "," + Origenlng + "&destination=" + Destinolat + "," + Destinolng;
    coor += "&key=AIzaSyAIUs8bUuj4nvBIMi2onO3qkrQsSnML8mk";
    base += coor;
    managerCoor->get(QNetworkRequest(QUrl(base)));
}
void Datamanager::slot_coordenadas(QNetworkReply *reply){

     QByteArray ba = reply->readAll();
     QStringList listCoordenadas;
     QStringList listParametros;
     QDomDocument  doc;
     doc.setContent(ba);

         QDomElement root = doc.documentElement();//se extrae la Raiz //<DirectionsResponse>
         QDomElement childRoot1 = root.firstChild().toElement();//obtengo el primer hijo de la raiz //<route>
         QDomElement childRoot2 = root.firstChild().nextSibling().toElement(); // <route>
         QDomElement childRoute2 = childRoot2.firstChild().nextSibling().toElement(); // <leg>
         QDomElement childLeg1 = childRoute2.firstChild().toElement(); //<step>
         QDomElement childStart = childLeg1.firstChild().nextSibling().toElement();//start

         QString lat,lat2,lng,lng2,time,dist;
         QDomElement childEnd = childLeg1.firstChild().nextSibling().nextSibling().toElement();//end
         QDomElement childTime = childEnd.nextSibling().nextSibling().toElement(); //duration
         QDomElement childDistance = childTime.nextSibling().nextSibling().toElement(); //distance

          while(!childLeg1.isNull()){

           if(childLeg1.tagName() == "start_location"){
                 lat = childStart.firstChild().toElement().text();
                 lng = childStart.firstChild().nextSibling().toElement().text();
            }


           if(childLeg1.tagName() == "end_location"){
               lat2 = childEnd.firstChild().toElement().text();
               lng2 = childEnd.firstChild().nextSibling().toElement().text();

            }

           if(childLeg1.tagName() == "duration"){
               time = childTime.firstChild().nextSibling().toElement().text();

            }
           if(childLeg1.tagName() == "distance"){
               dist = childDistance.firstChild().nextSibling().toElement().text();
            }
             childLeg1 = childLeg1.nextSibling().toElement();

         }
        /* qDebug()<< "----ORIGEN----";
         qDebug()<< "-LATITUD: " +lat;
         qDebug()<< "-LONGITUD: " +lng;

         qDebug()<< "----DESTINO----";
         qDebug()<< "-LATITUD: " +lat2;
         qDebug()<< "-LONGITUD: " +lng2;
         qDebug()<< "----------------";
         qDebug()<<"-TIEMPO: "+time;
         qDebug()<<"-DISTANCIA: "+dist;
         */
         listCoordenadas<<lat<<lng<<lat2<<lng2;
         listParametros<<time<<dist;

         emit signal_coordenadas(listCoordenadas);
         emit signal_parametros(listParametros);
}

void Datamanager::slot_tiempo(){

}

void Datamanager::slot_distancia(){

}
     //QDomNode root = doc.firstChild(); // raiz

     //if(root.isElement()){
         /*QDomElement e = root.toElement();
         QDomNodeList n1 = e.toElement().elementsByTagName("DirectionsResponse");
         for(int i=0; i<n1.size(); i++){


             QDomElement e1 = n1.at(i).toElement();
             QString nose = e1.text();
             qDebug()<<nose;

            // QDomNodeList n2 = e1.elementsByTagName("leg");

            /* for(int j=0;j<n2.count();j++){

                QDomElement e2 = n2.at(j).toElement();
                QDomNodeList n3 = e2.elementsByTagName("step");

                for(int k=0; k<n3.count(); k++){

                    QDomElement e3 = n3.at(k).toElement();
                    QDomNodeList n4 = e3.elementsByTagName("Start_location");

                    for(int l=0; l<n4.count(); l++){

                        QDomElement e4 = n4.at(l).toElement();
                        elementos = e4.tagName();
                        QString ver = e4.text();
                        qDebug()<<ver;
                    }
                }
             }*/
