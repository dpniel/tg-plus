#ifndef QTDCONNECTIONSTATEFACTORY_H
#define QTDCONNECTIONSTATEFACTORY_H

#include "qtdconnectionstate.h"
#include <QJsonObject>

class QTdConnectionStateFactory
{
public:
    static QTdConnectionState *create(const QJsonObject &json, QObject *parent);
};

#endif // QTDCONNECTIONSTATEFACTORY_H
