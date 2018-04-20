#ifndef QTDCONNECTIONSTATE_H
#define QTDCONNECTIONSTATE_H

#include <QObject>
#include "common/qabstracttdobject.h"

/**
 * @brief The QTdConnectionState class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_connection_state.html
 */
class QTdConnectionState : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdConnectionState(QObject *parent = nullptr);
};

/**
 * @brief The QTdConnectionStateWaitingForNetwork class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_waiting_for_network.html
 */
class QTdConnectionStateWaitingForNetwork : public QTdConnectionState {
    Q_OBJECT

public:
    explicit QTdConnectionStateWaitingForNetwork (QObject * parent = Q_NULLPTR);
};

/**
 * @brief The QTdConnectionStateConnectingToProxy class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_connecting_to_proxy.html
 */
class QTdConnectionStateConnectingToProxy : public QTdConnectionState {
    Q_OBJECT

public:
    explicit QTdConnectionStateConnectingToProxy (QObject * parent = Q_NULLPTR);
};

/**
 * @brief The QTdConnectionStateConnecting class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_connecting.html
 */
class QTdConnectionStateConnecting : public QTdConnectionState {
    Q_OBJECT

public:
    explicit QTdConnectionStateConnecting (QObject * parent = Q_NULLPTR);
};

/**
 * @brief The QTdConnectionStateUpdating class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_updating.html
 */
class QTdConnectionStateUpdating : public QTdConnectionState {
    Q_OBJECT

public:
    explicit QTdConnectionStateUpdating (QObject * parent = Q_NULLPTR);
};

/**
 * @brief The QTdConnectionStateReady class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_ready.html
 */
class QTdConnectionStateReady : public QTdConnectionState {
    Q_OBJECT

public:
    explicit QTdConnectionStateReady (QObject * parent = Q_NULLPTR);
};

#endif // QTDCONNECTIONSTATE_H
