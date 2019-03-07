// test.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QIODevice>
#include <QFile>
#include <QDebug>
#include <QVector>
#include <QList>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNamedNodeMap>

#include "xdattr.h"
#include "xdnode.h"
#include "xdxmldomreader.h"
//

int test(QVector<QString> args)
{
    QFile file(":/chart1.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "failed to load xml";
        file.close();
        return (-1);
    }

    using namespace XMLDOM;

    XMLDOMReader domReader;
    if ( !domReader.load(&file) )
    {
        qDebug() << "failed to load";
        return (-2);
    }

    QVector<QString> node1stList = domReader.enumerateNodeName( 1 );
    qDebug() << node1stList;

    Node* ptrChart = domReader.findNode( 1, "c:chart" );
    if ( NULL != ptrChart )
    {
        QVector<QString> nodeList = domReader.enumerateNodeName( ptrChart );
        qDebug() << nodeList;

        // Node* ptrNode = domReader.findNode( ptrChart, "c:plotArea" );
    }

    domReader.clear();

    file.close();
}
