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
#include <QVector>
#include <QList>

#include "xdattr.h"
#include "xdnode.h"
#include "xdxmldomreader.h"
// using namespace XMLDOM;

extern int test(QVector<QString> args);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QString> args;
    int ret = test(args);

    return 0;
}

