#ifndef READXML_H
#define READXML_H

#include <QWidget>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QNetworkAccessManager>
#include <QNetworkReply>
namespace Ui {
class ReadXml;
}

class ReadXml : public QWidget
{
    Q_OBJECT

public:

    explicit ReadXml(QWidget *parent = 0);
    void pedirTiempo();
    void pedirDistancia();
    void pedirPartida();
    void pedirLlegada();

    ~ReadXml();

private:
    Ui::ReadXml *ui;
    QDomDocument *xmltemporal;
    QNetworkAccessManager *manager;
signals:
    void signaTiempo(QString);
    void signalDistancia(QString);
    void signalPartida(QString);
    void signalLlegada(QString);

private slots:
    void slot_abrirXML();
    void slot_xmlDownload(QNetworkReply *reply);
};

#endif // READXML_H
