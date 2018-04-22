#ifndef QTDLINKSTATE_H
#define QTDLINKSTATE_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdLinkState : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdLinkState(QObject *parent = nullptr);
};

class QTdLinkStateIsContact : public QTdLinkState
{
    Q_OBJECT
public:
    explicit QTdLinkStateIsContact(QObject *parent = Q_NULLPTR);
};

class QTdLinkStateKnowsPhoneNumber : public QTdLinkState
{
    Q_OBJECT
public:
    explicit QTdLinkStateKnowsPhoneNumber(QObject *parent = Q_NULLPTR);
};

class QTdLinkStateNone : public QTdLinkState
{
    Q_OBJECT
public:
    explicit QTdLinkStateNone(QObject *parent = Q_NULLPTR);
};

#endif // QTDLINKSTATE_H
