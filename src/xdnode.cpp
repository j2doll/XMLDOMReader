//

#include "xdattr.h"
#include "xdnode.h"

namespace XMLDOM {

Node::Node()
{
    level = -1;
    parentNode = NULL;
}

Node::~Node()
{
    // attribute
    for (int ia = 0 ; ia < attrList.size(); ia++ )
    {
        Attr* ptrAttr = attrList.at( ia );
        if ( ptrAttr == NULL )
            continue;

        delete ptrAttr;
        ptrAttr = NULL;
    }
    attrList.clear();
}

} // namespace XMLDOM
