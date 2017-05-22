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

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();
    ~DataManager();

    void pedirTiempo();
    void pedirDistancia();
    void pedirPartida();
    void pedirLlegada();
    void getCoordinates(QString street);
    void getSites(QString search, QList<QString> coord);

private:
    QNetworkAccessManager *managerCoordinates, *managerSites, *manager;
    QDomDocument *xmltemporal;

private slots:
    void slot_getCoordinates(QNetworkReply *reply);
    void slot_getSites(QNetworkReply *reply);
    void slot_xmlDownload(QNetworkReply *reply);

signals:
    void receivedCoordinates(QList<QString>);
    void receivedSites(QList<QString>);
    void signaTiempo(QString);
    void signalDistancia(QString);
    void signalPartida(QString);
    void signalLlegada(QString);
};
