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

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();
    ~DataManager();

    void getCoordinates(QString street);
    void getSites(QString search, QList<QString> coord);

private:
    QNetworkAccessManager *managerCoordinates, *managerSites;

private slots:
    void slot_getCoordinates(QNetworkReply *reply);
    void slot_getSites(QNetworkReply *reply);

signals:
    void receivedCoordinates(QList<QString>);
    void receivedSites(QList<QString>);
};
