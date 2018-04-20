#ifndef QTDUSERSTATUSFACTORY_H
#define QTDUSERSTATUSFACTORY_H

#include "qtduserstatus.h"

class QTdUserStatusFactory
{
public:
    static QTdUserStatus *create(const QJsonObject &json, QObject *parent);
};

#endif // QTDUSERSTATUSFACTORY_H
