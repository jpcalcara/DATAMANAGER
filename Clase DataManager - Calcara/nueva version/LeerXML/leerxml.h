#ifndef LEERXML_H
#define LEERXML_H

#include <QWidget>
#include <QDomDocument>
#include <QXmlStreamReader>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


namespace Ui {
class LeerXML;
}

class LeerXML : public QWidget
{
    Q_OBJECT

public:
    explicit LeerXML(QWidget *parent = 0);
    ~LeerXML();
    void getTime(QString time);
    void getDistance(QString dis);
    void getStart(QString start);
    void getEnd(QString end);

private:
    Ui::LeerXML *ui;
    QNetworkAccessManager *manager;


public slots:

    void slot_readXML();
private slots:
 //   void slot_getTime(QNetworkReply *reply);
   // void slot_getStart(QNetworkReply *reply);
signals:
    void signalTime(QString);
    void signalDistance(QString);
    void signalStart(QString,QString);
    void signalEnd(QString);
};

#endif // LEERXML_H
