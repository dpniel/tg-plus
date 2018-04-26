#ifndef QTDSECRETCHATSTATE_H
#define QTDSECRETCHATSTATE_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdSecretChatState : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdSecretChatState(QObject *parent = nullptr);
};

class QTdSecretChatStateClosed : public QTdSecretChatState
{
    Q_OBJECT
public:
    explicit QTdSecretChatStateClosed(QObject *parent = nullptr);
};

class QTdSecretChatStatePending : public QTdSecretChatState
{
    Q_OBJECT
public:
    explicit QTdSecretChatStatePending(QObject *parent = nullptr);
};

class QTdSecretChatStateReady : public QTdSecretChatState
{
    Q_OBJECT
public:
    explicit QTdSecretChatStateReady(QObject *parent = nullptr);
};

#endif // QTDSECRETCHATSTATE_H
