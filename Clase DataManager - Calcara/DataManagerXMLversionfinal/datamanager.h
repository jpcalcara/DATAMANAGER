#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QList>
#include <QImage>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomAttr>
#include <QDomNodeList>

class Datamanager : public QObject
{
    Q_OBJECT
public:

    explicit Datamanager(QObject *parent = 0);
    ~Datamanager();
    /**
     * @brief solicita una consulta a las coordenadas de una direccion
     */
    void getCoordenadas(QString Origenlat, QString Origenlng, QString Destinolat, QString Destinolng);
    //void getMapa(QList<QString> coordenadas);

private:

    QNetworkAccessManager *managerCoor,*managerMapa;

signals:
    /**
     * @brief devuelve un QList<QString> con las dos coordenadas asociadas a la direccion
     * parametrizada por la funcion getCoordenadas.
     */
    void signal_coordenadas(QStringList listCoordenadas);
    void signal_parametros(QStringList listParametros);
    /**
     * @brief devuelve una lista de coordendas correspondientes a las indicaciones de
     * una ruta especifica. Dichas coordendas deben ser tomada de dos en dos como latitud
     * y longitud respectivamente.
     */
     void signal_camino(QList<QString>);
     /**
      * @brief devuelve una Imagen de un mapa con una ruta trazada.
      */
     //void signal_mapa(QImage);


private slots:
    /**
     * @brief recibe y procesa una respuesta xml de las coordenadas asociadas a
     * una direccion. Devuelve las mismas en un signal signal_coordenadas();
     */
    void slot_coordenadas(QNetworkReply *reply);
    void slot_tiempo();
    void slot_distancia();
    //void slot_getMapa(QNetworkReply *reply);

};

#endif // DATAMANAGER_H
