#ifndef QTDCLIENT_H
#define QTDCLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QFuture>
#include <QThread>
#include <QJsonObject>
#include "auth/qtdauthstate.h"
#include "connections/qtdconnectionstate.h"

/**
 * @brief The QTdClient class
 *
 * QTdClient is the main interface for communication with
 * the tdlib backend. A static instance is used to easily share
 * between components.
 */
class QTdClient : public QObject
{
    Q_OBJECT
public:
    explicit QTdClient(QObject *parent = nullptr);

    /**
     * @brief Shared static instance in the main thread.
     */
    static QTdClient *instance();

    /**
     * @brief The current authentication state
     */
    QTdAuthState *authState() const;
    /**
     * @brief The current connection state
     */
    QTdConnectionState *connectionState() const;

    /**
     * @brief send
     *
     * Send a request in another thread.
     *
     * QTdClient will take ownership of obj and schedule deletion once
     * it is done with it,
     */
    void send(QAbstractTdObject *obj);
    void send(const QJsonObject &json);
    /**
     * @brief Execute synchronous request in another Thread
     *
     * This is a synchronous action in another
     * thread and will return the result via the
     * returned QFuture
     *
     * QTdClient will take ownership of obj and schedule deletion once
     * it is done with it,
     */
    QFuture<QJsonObject> exec(QAbstractTdObject *obj);
    QFuture<QJsonObject> exec(const QJsonObject &json);

signals:
    void authStateChanged(QTdAuthState *state);
    void connectionStateChanged(QTdConnectionState *state);
    void updateUser(QJsonObject user);
    void updateUserStatus(QString user_id, QJsonObject status);

private slots:
    void handleRecv(const QJsonObject &data);
private:
    void updateAuthState(const QJsonObject &data);
    void updateConnectionState(const QJsonObject &data);

    QThread *m_worker;
    QTdAuthState *m_authState;
    QTdConnectionState *m_connectionState;
};

#endif // QTDCLIENT_H
