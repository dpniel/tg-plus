#include "qtdclient.h"
#include <QDebug>
#include <QPointer>
#include <QJsonDocument>
#include <QtConcurrent>
#include "qtdthread.h"
#include "qtdhandle.h"
#include "auth/qtdauthstatefactory.h"
#include "connections/qtdconnectionstatefactory.h"

QJsonObject execTd(const QJsonObject &json) {
    qDebug() << "[EXEC]" << json;
    const QByteArray  tmp = (QJsonDocument(json).toJson(QJsonDocument::Compact) % '\0');
    QSharedPointer<Handle> tdlib = QTdHandle::instance();
    const QByteArray  str = QByteArray(td_json_client_execute(tdlib->handle(), tmp.constData()));
    const QJsonObject ret = QJsonDocument::fromJson(str).object();
    qDebug() << "[EXEC RESULT]" << ret;
    return ret;
}

void sendTd(const QJsonObject &json) {
    qDebug() << "[SEND] :" << json;
    const QByteArray msg = QJsonDocument(json).toJson(QJsonDocument::Compact).append('\0');
    QSharedPointer<Handle> tdlib = QTdHandle::instance();
    td_json_client_send(tdlib->handle(), msg.constData());
}

QTdClient::QTdClient(QObject *parent) : QObject(parent),
    m_worker(Q_NULLPTR),
    m_authState(Q_NULLPTR),
    m_connectionState(Q_NULLPTR)
{
    m_worker = new QThread(this);
    QTdWorker *w = new QTdWorker;
    w->moveToThread(m_worker);
    connect(m_worker, &QThread::started, w, &QTdWorker::run);
    connect(w, &QTdWorker::recv, this, &QTdClient::handleRecv);
    m_worker->start();
}

static QPointer<QTdClient> s_tdclient;
QTdClient *QTdClient::instance()
{
    if (s_tdclient.isNull()) {
        s_tdclient = new QTdClient();
    }
    return s_tdclient;
}

QTdAuthState *QTdClient::authState() const
{
    return m_authState;
}

QTdConnectionState *QTdClient::connectionState() const
{
    return m_connectionState;
}

void QTdClient::send(QAbstractTdObject *obj)
{
    // Take ownership of the object and schedule
    // it's deletion when done;
    obj->setParent(this);
    send(obj->marshalJson());
    obj->deleteLater();
}

void QTdClient::send(const QJsonObject &json)
{
    if (json.isEmpty()) {
        qDebug() << "Empty Json object, nothing to send?";
        return;
    }
    QtConcurrent::run(sendTd, json);
}

QFuture<QJsonObject> QTdClient::exec(QAbstractTdObject *obj)
{
    // Take ownership of the object and schedule
    // it's deletion when done;
    obj->setParent(this);
    const QJsonObject json = obj->marshalJson();
    obj->deleteLater();
    return exec(json);
}

QFuture<QJsonObject> QTdClient::exec(const QJsonObject &json)
{
    return QtConcurrent::run(execTd, json);
}

void QTdClient::handleRecv(const QJsonObject &data)
{
    const QString type = data["@type"].toString();
    qDebug() << "-------------[ RCV ]-----------------------";
    qDebug() << "TYPE >> " << type;
    qDebug() << "DATA >> " << data;
    qDebug() << "-------------------------------------------";
    if (type == "updateAuthorizationState") {
        updateAuthState(data);
    } else if (type == "updateConnectionState") {
        updateConnectionState(data["state"].toObject());
    } else if (type == "updateUser") {
        qDebug() << "Emitting updateUser";
        emit updateUser(data["user"].toObject());
    } else if (type == "updateUserStatus") {
        qDebug() << "Emitting updateUserStatus";
        const QString userId = QString::number(qint32(data["user_id"].toInt()));
        emit updateUserStatus(userId, data["status"].toObject());
    }
}

void QTdClient::updateAuthState(const QJsonObject &data)
{
    QTdAuthState *state = QTdAuthStateFactory::create(data, this);
    if (!state) {
        qDebug() << "Unknown auth state: " << data;
        return;
    }
    if (!m_authState || (state->type() != m_authState->type())) {
        if (m_authState) {
            delete m_authState;
            m_authState = 0;
        }
        m_authState = state;
        emit authStateChanged(m_authState);
    }
}

void QTdClient::updateConnectionState(const QJsonObject &data)
{
    qDebug() << "[ConnectionStateChanged] >> " << data;
    if (m_connectionState) {
        delete m_connectionState;
        m_connectionState = 0;
    }
    m_connectionState = QTdConnectionStateFactory::create(data, this);
    emit connectionStateChanged(m_connectionState);
}


