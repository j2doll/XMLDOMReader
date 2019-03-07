// xdxmldomreader.h
// https://github.com/j2doll/XMLDOMReader

#ifndef XMLDOMREADER_H
#define XMLDOMREADER_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QIODevice>
#include <QFile>
#include <QVector>
#include <QList>
#include <QDebug>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNamedNodeMap>

#include "xdattr.h"
#include "xdnode.h"

namespace XMLDOM {

class XMLDOMReader
{
public:
    XMLDOMReader();
    ~XMLDOMReader();
public:
    bool load(QIODevice* ioDevice);
    void clear();
public:
    void debugNodes();
    Node* findNode(int level, QString nodeName);
    Node* findNode(Node* parentNode, QString nodeName);

    QVector<QString> enumerateNodeName(int level);
    QVector<QString> enumerateNodeName(Node* parentNode);

    Attr* findAttr(Node* ptrNode, QString attrName);
protected:
    void traverseXmlNode(const QDomNode& node, Node* parent);
protected:
    Node* ptrRootNode; // root node
    int tabCount; // level
    QList< Node* > allNodes; // all list of heap node
};

}
#endif // XMLDOMREADER_H
