//

#include "xdattr.h"
#include "xdnode.h"
#include "xdxmldomreader.h"

namespace XMLDOM {

XMLDOMReader::XMLDOMReader()
{
    tabCount = 0; // level
    ptrRootNode = NULL;
}

XMLDOMReader::~XMLDOMReader()
{
    clear();
}

bool XMLDOMReader::load(QIODevice* ioDevice)
{
    QDomDocument doc;
    if ( !doc.setContent(ioDevice) )
    {
        // qDebug() << "[debug][QDomDocument] failed to set content";
        return false;
    }

    // the root element of the document.

    QDomElement docElem = doc.documentElement();

    // root node
    ptrRootNode = new Node();
    ptrRootNode->nodeName = "root";
    ptrRootNode->level = 0; // root level
    ptrRootNode->parentNode = NULL;
    allNodes.append( ptrRootNode );

    traverseXmlNode( docElem, ptrRootNode );

    return true;
}

void XMLDOMReader::traverseXmlNode(const QDomNode& node, Node* parent)
{
    QDomNode domNode = node.firstChild();
    QDomElement domElement;

    tabCount++; // increase current tab count

    QString strTab;
    QString strTabSize = QString("    ");
    for (int ic = 0 ; ic < tabCount; ic++ )
    {
        strTab = strTab + strTabSize;
    }

    while(!(domNode.isNull()))
    {
        Node* ptrNewNode = NULL;

        if(domNode.isElement())
        {
            domElement = domNode.toElement();
            if ( domElement.isNull() )
                continue;

            ptrNewNode = new Node();
            ptrNewNode->level = tabCount; // level (from 1 to n)
            ptrNewNode->parentNode = parent; // set parent
            ptrNewNode->nodeName = domElement.tagName();
            ptrNewNode->nodeText = domElement.text();

            // element name
            // qDebug() << strTab << QString("[%1]").arg(tabCount) << domElement.tagName() << domElement.text();

            // attribute
            QDomNamedNodeMap map = domElement.attributes();
            for (int id = 0 ; id < map.size() ; id++ )
            {
                QDomNode node = map.item( id );

                // qDebug() << (strTab + strTabSize + strTabSize) << node.nodeName() << node.nodeValue();

                Attr* attr = new Attr();
                attr->name = node.nodeName();
                attr->value = node.nodeValue();

                ptrNewNode->attrList.append( attr );
            }

            parent->childNode.append( ptrNewNode ); // append child

            allNodes.append( ptrNewNode );
        }

        traverseXmlNode(domNode, ptrNewNode); // recursive function
        domNode = domNode.nextSibling();
    }

    tabCount--; // decrease current tab count
}

void XMLDOMReader::debugNodes()
{
    Q_ASSERT(NULL != ptrRootNode);

    for (int ic = 0 ; ic < ptrRootNode->childNode.size(); ic++ )
    {
        Node* node = ptrRootNode->childNode.at( ic );
        if ( node == NULL )
            continue;

        int level = node->level;
        QString nodeName = node->nodeName;

        qDebug() << QString("[%1]").arg( level ) << nodeName;
    }
}

Node* XMLDOMReader::findNode(int level, QString nodeName)
{
    if ( level < 0 )
        return NULL;

    if ( nodeName.isEmpty() )
        return NULL;

    for (int ifc = 0 ; ifc < this->allNodes.size() ; ifc++ )
    {
        Node* ptrNode = allNodes.at( ifc );
        if (ptrNode == NULL)
            continue;

        if ( ptrNode->level == level &&
             ptrNode->nodeName == nodeName )
        {
            return ptrNode;
        }
    }

    return NULL;
}

QVector<QString> XMLDOMReader::enumerateNodeName(int level)
{
    QVector<QString> ret;

    if ( level < 0 )
        return ret;

    for (int ifc = 0 ; ifc < this->allNodes.size() ; ifc++ )
    {
        Node* ptrNode = allNodes.at( ifc );
        if (ptrNode == NULL)
            continue;

        if ( ptrNode->level != level )
            continue;

        if ( ptrNode->nodeName.isEmpty() )
            continue;

        ret.append( ptrNode->nodeName );
    }

    return ret;
}

Node* XMLDOMReader::findNode(Node* parentNode, QString nodeName)
{
    if ( NULL == parentNode )
        return NULL;

    if ( nodeName.isEmpty() )
        return NULL;

    for (int ic = 0 ; ic < parentNode->childNode.size()  ; ic++ )
    {
       Node* ptrNode = parentNode->childNode.at( ic );
       if ( NULL == ptrNode )
           continue;

       if ( ptrNode->nodeName == nodeName)
           return ptrNode;
    }

    return NULL;
}

QVector<QString> XMLDOMReader::enumerateNodeName(Node* parentNode)
{
    QVector<QString> ret;

    if ( NULL == parentNode )
        return ret;

    for (int ic = 0 ; ic < parentNode->childNode.size()  ; ic++ )
    {
       Node* ptrNode = parentNode->childNode.at( ic );
       if ( NULL == ptrNode )
           continue;

       if ( ptrNode->nodeName.isEmpty() )
           continue;

        ret.append( ptrNode->nodeName );
    }

    return ret;
}

Attr* XMLDOMReader::findAttr(Node* ptrNode, QString attrName)
{
    if ( NULL == ptrNode )
        return NULL;

    if ( attrName.isEmpty() )
        return NULL;

    for (int ic = 0 ; ic < ptrNode->attrList.size() ; ic++ )
    {
       Attr* ptrAttr = ptrNode->attrList.at( ic );
       if ( NULL == ptrAttr )
           continue;

       if ( ptrAttr->name == attrName )
           return ptrAttr;
    }

    return NULL;
}

void XMLDOMReader::clear()
{
    for (int ic = 0; ic < allNodes.size(); ic++)
    {
        Node* ptr = allNodes.at( ic );
        if ( ptr == NULL )
            continue;

        delete ptr; // clear heaps
        ptr = NULL;
    }

    allNodes.clear();
}

} // namespace XMLDOM
