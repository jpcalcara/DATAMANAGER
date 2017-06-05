#include "datamanager.h"
#include <QFile>

DataManager::DataManager()
{
    managerCoordinates = new QNetworkAccessManager();
    managerSites = new QNetworkAccessManager();
    managerDestino = new QNetworkAccessManager();
    managerOrigen = new QNetworkAccessManager();

    connect(managerSites,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getSites(QNetworkReply *)));
    connect(managerCoordinates,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getCoordinates(QNetworkReply *)));
    connect(managerOrigen,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getOrigen(QNetworkReply *)));//obtenemos origen 
    connect(managerDestino,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getDestino(QNetworkReply *)));//obtnemos destino
}

DataManager::~DataManager()
{

}
// se obtiene desde la url el contenido de destino
void DataManager::getDestino(QString end){

    QString destino = "&destination=";
    destino += end;
    destino += "&key=AIzaSyAIUs8bUuj4nvBIMi2onO3qkrQsSnML8mk";

    managerDestino->get(QNetworkRequest(QUrl(destino)));

}
// se obtiene desde la url el contenido de origen
void DataManager::getOrigen(QString start){

    QString origen = "https://maps.googleapis.com/maps/api/directions/xml?origin=";
    origen += start;
    origen += "&key=AIzaSyAIUs8bUuj4nvBIMi2onO3qkrQsSnML8mk";

    managerOrigen->get(QNetworkRequest(QUrl(origen)));
}

/* Devuelve en un SIGNAL receivedCoordinates() un QList con las dos
* coordenadas de la direccion que se paso como parametro */
void DataManager::getCoordinates(QString street)
{
    QString base = "https://maps.googleapis.com/maps/api/geocode/json?address=";

    base += street;
    base += "&key=AIzaSyCnRcVd391QIPAa7i7tkfHrpP-BuehQ5FE";

    managerCoordinates->get(QNetworkRequest(QUrl(base)));
}

/* Devuelve en un signal receivedCoordinates() un QList con todas
   las direcciones que encuentra en un radio de 2km de la direccion pasada
   como parametro. Requiere tambien las coordenadas de dicho punto.
   Para eso usar getCoordinate */
void DataManager::getSites(QString search, QList<QString> coord)
{
    QString base = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=";
    base.append(coord.at(0)+","+coord.at(1)+"&radius=2000&keyword="+search);
    base.append("&key=AIzaSyCWkS32Vvd6wBepLJkNJfRxELfXQOw8NFg");

    managerSites->get(QNetworkRequest(QUrl(base)));
}

void DataManager::slot_getCoordinates(QNetworkReply *reply)
{
    QJsonDocument a = QJsonDocument::fromJson(reply->readAll());
    QJsonObject b = a.object().value("results").toArray().first().toObject();
    QJsonValue e = b.take("geometry").toObject().take("location");
    QList<QString> list;
    list.append(QString::number(e.toObject().take("lat").toDouble()));
    list.append(QString::number(e.toObject().take("lng").toDouble()));

    emit receivedCoordinates(list);
}

void DataManager::slot_getSites(QNetworkReply *reply)
{
    QList<QString> list;
    QJsonDocument a = QJsonDocument::fromJson(reply->readAll());
    QJsonArray b = a.object().value("results").toArray();

    for(int i=0; i<b.size();i++)
    {
        QJsonValue c = b.at(i).toObject().take("vicinity");
        list.append(c.toString());
    }

    emit  receivedSites(list);
}
//Se emiten los parametros de latitud(Origen) y longitud(Origen) obtenidos luego de la lectura del XML
void DataManager::slot_getOrigen(QNetworkReply *reply){

    QByteArray ba = reply->readAll();
    QString origen;

    if(ba.indexOf("<start_location>") && ba.indexOf("</start_location>") )

    origen = ba.mid(871,93);
    //qDebug()<< origen; // muestra todo el <start_location>

    origen.indexOf("<lat>");qDebug()<<origen.indexOf("<lat>");//muestra el indice de comienzo
    origen.indexOf("</lat>");qDebug()<<origen.indexOf("</lat>");//muestra el indice de final
    QString Olat = origen.mid(27,10);// guardo en un string la latitud origen
    qDebug()<<Olat;

    origen.indexOf("<lng>");qDebug()<<origen.indexOf("<lng>");//muestra el indice de comienzo
    origen.indexOf("</lng>");qDebug()<<origen.indexOf("</lng>");//muestra el indice de final
    QString Olng = origen.mid(54,11);
    qDebug()<<Olng;

   // qDebug()<< "---PUNTO DE ORIGEN---";
    //qDebug()<< "-LATITUD: "+Olat;
    //qDebug()<< "-LONGITUD: "+Olng;
    //qDebug()<< "---------------------";

    //ui->pteTexto->appendPlainText("---PUNTO DE ORIGEN---");
    //ui->pteTexto->appendPlainText("-LATITUD: "+Olat);
    //ui->pteTexto->appendPlainText("-LONGITUD: "+Olng);
   // ui->pteTexto->appendPlainText("---------------------");

    emit signalOrigen(Olat,Olng);

}

//se emiten los parametros de latitud(Destino) y longitud(Destino) obtenidos luego de la lectura del XML
void DataManager::slot_getDestino(QNetworkReply *reply){

    QByteArray ba = reply->readAll();
    QString destino;

    destino = ba.mid(969,89);
    //qDebug()<< destino;//muestra todo el <end_location>

    destino.indexOf("<lat>");qDebug()<<destino.indexOf("<lat>");//muestra el indice de comienzo
    destino.indexOf("</lat>");qDebug()<<destino.indexOf("</lat>");//muestra el indice de final
    QString Dlat = destino.mid(25,10);//guardo en un string la latitud destino
    qDebug()<<Dlat;

    destino.indexOf("<lng>");qDebug()<<destino.indexOf("<lng>");//muestra el indice de comienzo
    destino.indexOf("</lng>");qDebug()<<destino.indexOf("</lng>");//muestra el indice de final
    QString Dlng = destino.mid(52,11);//guardo en un string la longitud destino
    qDebug()<<Dlng;

   // qDebug()<< "---PUNTO DE DESTINO---";
    //qDebug()<< "-LATITUD: "+Dlat;
    //qDebug()<< "-LONGITUD: "+Dlng;
    //qDebug()<< "---------------------";
/*
    ui->pteTexto->appendPlainText("---PUNTO DE DESTINO---");
    ui->pteTexto->appendPlainText("-LATITUD: "+Dlat);
    ui->pteTexto->appendPlainText("-LONGITUD: "+Dlng);
    ui->pteTexto->appendPlainText("----------------------");
*/
    emit signalDestino(Dlat,Dlng);
    
    //OTRA FORMA D E  OBTENER LOS PARAMETROS DE LAT Y LONG
    /*
    QDomDocument doc;
    QByteArray xml = doc.toByteArray();
    xml = reply->readAll();
    
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

     emit signalOrigen(lat,lng);
     qDebug()<<"-Latitud :"+lat;
     qDebug()<<"-Longitud :"+lng;
     */
}
void DataManager::slot_getMaps(QNetworkReply *reply)
{
    QImage im = QImage::fromData(reply->readAll());
    
    emit signalMaps(im);
}
