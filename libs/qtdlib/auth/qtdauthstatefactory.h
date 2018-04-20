#ifndef QTDAUTHSTATEFACTORY_H
#define QTDAUTHSTATEFACTORY_H

#include "qtdauthstate.h"

class QTdAuthStateFactory
{
public:
    static QTdAuthState *create(const QJsonObject &data, QObject *parent);
};

#endif // QTDAUTHSTATEFACTORY_H
