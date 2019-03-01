#ifndef ATTR_H
#define ATTR_H

#include <QtGlobal>
#include <QObject>
#include <QString>

namespace XMLDOM {

class Attr
{
public:
    explicit Attr();
    ~Attr();
public:
    QString name;
    QString value;
};

}
#endif // ATTR_H
