#pragma once
#include<QNetworkRequest>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QUrl>
#include<QDebug>
#include<QObject>
#include<QString>
#include<QList>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonArray>
#include<QXmlStreamReader>
#include<QTextStream>
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QDataStream>

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();
    ~DataManager();

    //void getTiempo();
    //void getDistancia();
    void getOrigen(QString start);
    void getDestino(QString end);
    void getCoordinates(QString street);
    void getSites(QString search, QList<QString> coord);

private:
    QNetworkAccessManager *managerCoordinates, *managerSites, *managerDestino, *managerOrigen;

private slots:
    void slot_getCoordinates(QNetworkReply *reply);
    void slot_getSites(QNetworkReply *reply);
    void slot_getTiempo(QNetworkReply *reply);
    void slot_getDistancia(QNetworkReply *reply);
    void slot_getOrigen(QNetworkReply *reply);
    void slot_getDestino(QNetworkReply *reply);


signals:
    void receivedCoordinates(QList<QString>);
    void receivedSites(QList<QString>);
    //void signalTiempo(QString, QString);
   // void signalDistancia(QString, QString);
    void signalOrigen(QString, QString);
    void signalDestino(QString, QString);
};
