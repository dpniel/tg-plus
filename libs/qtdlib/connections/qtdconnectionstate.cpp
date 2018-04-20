#include "qtdconnectionstate.h"

QTdConnectionState::QTdConnectionState(QObject *parent) : QAbstractTdObject(parent)
{

}

QTdConnectionStateWaitingForNetwork::QTdConnectionStateWaitingForNetwork(QObject *parent): QTdConnectionState(parent)
{
    setType(CONNECTION_STATE_WAITING_FOR_NETWORK);
}

QTdConnectionStateConnectingToProxy::QTdConnectionStateConnectingToProxy(QObject *parent): QTdConnectionState(parent)
{
    setType(CONNECTION_STATE_CONNECTING_TO_PROXY);
}

QTdConnectionStateConnecting::QTdConnectionStateConnecting(QObject *parent) : QTdConnectionState(parent)
{
    setType(CONNECTION_STATE_CONNECTING);
}

QTdConnectionStateUpdating::QTdConnectionStateUpdating(QObject *parent) : QTdConnectionState(parent)
{
    setType(CONNECTION_STATE_UPDATING);
}

QTdConnectionStateReady::QTdConnectionStateReady(QObject *parent) : QTdConnectionState(parent)
{
    setType(CONNECTION_STATE_READY);
}
