#ifndef READXML_H
#define READXML_H

#include <QWidget>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

namespace Ui {
class ReadXml;
}

class ReadXml : public QWidget
{
    Q_OBJECT

public:
    explicit ReadXml(QWidget *parent = 0);
    ~ReadXml();

private:
    Ui::ReadXml *ui;
    QDomDocument *xmltemporal;
public slots:
    void slot_abrirXML();
};

#endif // READXML_H
