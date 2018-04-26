#include "qtdsecretchat.h"
#include "chat/requests/qtdgetsecretchatrequest.h"
#include "client/qtdclient.h"

QTdSecretChat::QTdSecretChat(QObject *parent) : QTdChat(parent),
    m_secretChatId(0), m_userId(0), m_isOutbound(false),
    m_ttl(0), m_layer(0), m_state(Q_NULLPTR)
{
    connect(this, &QTdChat::chatTypeChanged, this, &QTdSecretChat::getSecretChatData);
    connect(QTdClient::instance(), &QTdClient::secretChat, this, &QTdSecretChat::updateSecretChat);
    connect(QTdClient::instance(), &QTdClient::updateSecretChat, this, &QTdSecretChat::updateSecretChat);
}

QString QTdSecretChat::qmlSecretChatId() const
{
    return m_secretChatId.toQmlValue();
}

qint32 QTdSecretChat::secretChatId() const
{
    return m_secretChatId.value();
}

QString QTdSecretChat::qmlUserId() const
{
    return m_userId.toQmlValue();
}

qint32 QTdSecretChat::userId() const
{
    return m_userId.value();
}

bool QTdSecretChat::isOutbound() const
{
    return m_isOutbound;
}

qint32 QTdSecretChat::ttl() const
{
    return m_ttl;
}

QString QTdSecretChat::keyHash() const
{
    return m_keyHash;
}

qint32 QTdSecretChat::layer() const
{
    return m_layer;
}

QTdSecretChatState *QTdSecretChat::state() const
{
    return m_state;
}

void QTdSecretChat::getSecretChatData()
{
    QTdChatTypeSecret *secret = qobject_cast<QTdChatTypeSecret*>(chatType());
    if (secret->secretChatId() > 0) {
        auto *req = new QTdGetSecretChatRequest;
        req->setSecretChatId(secret->secretChatId());
        QTdClient::instance()->send(req);
    }
}

void QTdSecretChat::updateSecretChat(const QJsonObject &data)
{
    QTdChatTypeSecret *secret = qobject_cast<QTdChatTypeSecret*>(chatType());
    const qint32 sid = qint32(data["id"].toInt());
    if (sid != secret->secretChatId()) {
        return;
    }

    m_secretChatId = sid;
    m_userId = data["user_id"];
    const QJsonObject state = data["state"].toObject();
    const QString type = state["@type"].toString();
    if (type == "secretChatStateClosed") {
        m_state = new QTdSecretChatStateClosed(this);
    } else if (type == "secretChatStatePending") {
        m_state = new QTdSecretChatStatePending(this);
    } else if (type == "secretChatStateReady") {
        m_state = new QTdSecretChatStateReady(this);
    }
    if (m_state) {
        m_state->unmarshalJson(state);
        emit stateChanged(m_state);
    }
    m_isOutbound = data["is_outbound"].toBool();
    m_ttl = qint32(data["ttl"].toInt());
    m_keyHash = data["key_hash"].toString();
    m_layer = qint32(data["layer"].toInt());
    emit secretChatChanged();
}
