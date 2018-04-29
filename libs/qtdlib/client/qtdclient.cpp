#include "qtdclient.h"
#include <QDebug>
#include <QPointer>
#include <QJsonDocument>
#include <QtConcurrent>
#include "qtdthread.h"
#include "qtdhandle.h"
#include "auth/qtdauthstatefactory.h"
#include "connections/qtdconnectionstatefactory.h"
#include <functional>

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
    init();
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

void QTdClient::send(QTdRequest *obj)
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

QFuture<QJsonObject> QTdClient::exec(QTdRequest *obj)
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
    if (m_events.contains(type)) {
        m_events.value(type)(data);
    } else {
        qDebug() << "---------[UNHANDLED]-------------";
        qDebug() << type;
        qDebug() << "---------------------------------";
    }
}

void QTdClient::init()
{
    m_events.insert("updateAuthorizationState", [=](const QJsonObject &data) {
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
    });

    m_events.insert("updateConnectionState", [=](const QJsonObject &data) {
        qDebug() << "[ConnectionStateChanged] >> " << data;
        if (m_connectionState) {
            delete m_connectionState;
            m_connectionState = 0;
        }
        m_connectionState = QTdConnectionStateFactory::create(data, this);
        emit connectionStateChanged(m_connectionState);
    });

    m_events.insert("updateUser", [=](const QJsonObject &data){ emit updateUser(data["user"].toObject()); });
    m_events.insert("updateUserStatus", [=](const QJsonObject &data){
        const QString userId = QString::number(qint32(data["user_id"].toInt()));
        emit updateUserStatus(userId, data["status"].toObject());
    });
    m_events.insert("updateFile", [=](const QJsonObject &data){ emit updateFile(data["file"].toObject()); });
    m_events.insert("updateNewChat", [=](const QJsonObject &data){ emit updateNewChat(data["chat"].toObject()); });
    m_events.insert("updateBasicGroup", [=](const QJsonObject &data){ emit updateBasicGroup(data["basic_group"].toObject()); });
    m_events.insert("basicGroup", [=](const QJsonObject &data){ emit updateBasicGroup(data); });
    m_events.insert("secretChat", [=](const QJsonObject &data){ emit secretChat(data); });
    m_events.insert("updateSecretChat", [=](const QJsonObject &data){ emit updateSecretChat(data["secret_chat"].toObject()); });
    m_events.insert("supergroup", [=](const QJsonObject &data){ emit superGroup(data); });
    m_events.insert("updateSupergroup", [=](const QJsonObject &data){ emit updateSuperGroup(data["supergroup"].toObject()); });
    m_events.insert("updateChatOrder", [=](const QJsonObject &data){ emit updateChatOrder(data); });
    m_events.insert("updateChatLastMessage", [=](const QJsonObject &data){ emit updateChatLastMessage(data); });
    m_events.insert("updateChatReadInbox", [=](const QJsonObject &data){ emit updateChatReadInbox(data); });
    m_events.insert("updateChatIsPinned", [=](const QJsonObject &data){ emit updateChatIsPinned(data); });
    m_events.insert("updateChatPhoto", [=](const QJsonObject &data){ emit updateChatPhoto(data); });
    m_events.insert("updateChatReadOutbox", [=](const QJsonObject &data){ emit updateChatReadOutbox(data); });
    m_events.insert("updateChatReplyMarkup", [=](const QJsonObject &data){ emit updateChatReplyMarkup(data); });
    m_events.insert("updateChatTitle", [=](const QJsonObject &data){ emit updateChatTitle(data); });
    m_events.insert("updateChatUnreadMentionCount", [=](const QJsonObject &data){ emit updateChatUnreadMentionCount(data); });
}


