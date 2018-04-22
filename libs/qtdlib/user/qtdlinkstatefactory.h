#ifndef QTDLINKSTATEFACTORY_H
#define QTDLINKSTATEFACTORY_H

#include "qtdlinkstate.h"

class QTdLinkStateFactory
{
public:
    static QTdLinkState *create(const QJsonObject &json, QObject *parent);
};

#endif // QTDLINKSTATEFACTORY_H
