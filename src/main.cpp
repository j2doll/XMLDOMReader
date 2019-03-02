// main.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QIODevice>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QCoreApplication>
#include <QDebug>

#include "Attr.h"
#include "Node.h"
#include "XMLDOMReader.h"
// using namespace XMLDOM;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file(":/chart1.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "failed to load xml";
        file.close();
        return (-1);
    }

    XMLDOM::XMLDOMReader domReader;
    if ( !domReader.load(&file) )
    {
        qDebug() << "failed to load";
        return (-2);
    }

    domReader.debugNodes(); // function for deugging

    XMLDOM::Node* ptrChart = domReader.findNode( 1, "c:chart" );
    if ( NULL != ptrChart )
    {
        for (int cindex = 0 ; cindex < ptrChart->childNode.size() ; cindex ++)
        {
            XMLDOM::Node* pNode = ptrChart->childNode.at( cindex );
            if ( NULL == pNode )
                continue;

            qDebug() << pNode->level << pNode->nodeName << pNode->nodeText ;
        }
    }

    domReader.clear();

    file.close();
    return 0;
}

