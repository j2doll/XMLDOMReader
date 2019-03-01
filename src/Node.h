#ifndef NODE_H
#define NODE_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QList>
#include <QMap>

#include "Attr.h"

namespace XMLDOM {

class Node
{
public:
    explicit Node();
    ~Node();
public:
    int level; // (-1) means n statement. 0 means root node.
    QString nodeName;
    QString nodeText;
    QList< Attr* > attrList;
public:
    Node* parentNode;
    QList< Node* > childNode;
};

}
#endif // NODE_H
