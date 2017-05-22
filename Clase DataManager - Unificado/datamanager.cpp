#include "datamanager.h"

DataManager::DataManager()
{
    managerCoordinates = new QNetworkAccessManager();
    managerSites = new QNetworkAccessManager();

    connect(managerSites,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getSites(QNetworkReply *)));
    connect(managerCoordinates,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getCoordinates(QNetworkReply *)));
}

DataManager::~DataManager()
{

}

void DataManager::pedirTiempo()
{

}

void DataManager::pedirDistancia()
{

}

void DataManager::pedirPartida()
{

}

void DataManager::pedirLlegada()
{

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

void DataManager::slot_xmlDownload(QNetworkReply *reply)
{

}
