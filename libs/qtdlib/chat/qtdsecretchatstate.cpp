#include "qtdsecretchatstate.h"

QTdSecretChatState::QTdSecretChatState(QObject *parent) : QAbstractTdObject(parent)
{
}

QTdSecretChatStateClosed::QTdSecretChatStateClosed(QObject *parent) : QTdSecretChatState(parent)
{
}

QTdSecretChatStatePending::QTdSecretChatStatePending(QObject *parent) : QTdSecretChatState(parent)
{
}

QTdSecretChatStateReady::QTdSecretChatStateReady(QObject *parent) : QTdSecretChatState(parent)
{
}
