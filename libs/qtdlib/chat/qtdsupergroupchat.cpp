#include "qtdsupergroupchat.h"
#include <QDateTime>
#include "chat/requests/qtdgetsupergrouprequest.h"
#include "client/qtdclient.h"

QTdSuperGroupChat::QTdSuperGroupChat(QObject *parent) : QTdChat(parent),
    m_sgId(0), m_date(0), m_status(Q_NULLPTR),
    m_memberCount(0), m_canInvite(false), m_signMessages(false),
    m_isChannel(false), m_isVerified(false)
{
    connect(this, &QTdChat::chatTypeChanged, this, &QTdSuperGroupChat::getSuperGroupData);
    connect(QTdClient::instance(), &QTdClient::superGroup, this, &QTdSuperGroupChat::updateSuperGroup);
    connect(QTdClient::instance(), &QTdClient::updateSuperGroup, this, &QTdSuperGroupChat::updateSuperGroup);
}

QString QTdSuperGroupChat::qmlSuperGroupId() const
{
    return m_sgId.toQmlValue();
}

qint32 QTdSuperGroupChat::superGroupId() const
{
    return m_sgId.value();
}

QString QTdSuperGroupChat::userName() const
{
    return m_username;
}

QDateTime QTdSuperGroupChat::qmlDate() const
{
    return QDateTime::fromTime_t(m_date);
}

qint32 QTdSuperGroupChat::date() const
{
    return m_date;
}

QTdChatMemberStatus *QTdSuperGroupChat::status() const
{
    return m_status;
}

QString QTdSuperGroupChat::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

qint32 QTdSuperGroupChat::memberCount() const
{
    return m_memberCount.value();
}

bool QTdSuperGroupChat::anyoneCanInvite() const
{
    return m_canInvite;
}

bool QTdSuperGroupChat::signMessages() const
{
    return m_signMessages;
}

bool QTdSuperGroupChat::isChannel() const
{
    return m_isChannel;
}

bool QTdSuperGroupChat::isVerified() const
{
    return m_isVerified;
}

QString QTdSuperGroupChat::restrictionReason() const
{
    return m_restrictionReason;
}

void QTdSuperGroupChat::getSuperGroupData()
{
    QTdChatTypeSuperGroup *group = qobject_cast<QTdChatTypeSuperGroup*>(chatType());
    if (group->superGroupId() > 0) {
        auto *req = new QTdGetSuperGroupRequest;
        req->setSuperGroupId(group->superGroupId());
        QTdClient::instance()->send(req);
    }
}

void QTdSuperGroupChat::updateSuperGroup(const QJsonObject &json)
{
    QTdChatTypeSuperGroup *group = qobject_cast<QTdChatTypeSuperGroup*>(chatType());
    const qint32 gid = qint32(json["id"].toInt());
    if (gid != group->superGroupId()) {
        return;
    }
    m_sgId = gid;
    m_memberCount = json["member_count"];

    if (m_status) {
        delete m_status;
        m_status = 0;
    }
    const QJsonObject status = json["status"].toObject();
    const QString type = status["@type"].toString();
    if (type == "chatMemberStatusAdministrator") {
        m_status = new QTdChatMemberStatusAdmin(this);
    } else if (type == "chatMemberStatusBanned") {
        m_status = new QTdChatMemberStatusBanned(this);
    } else if (type == "chatMemberStatusCreator") {
        m_status = new QTdChatMemberStatusCreator(this);
    } else if (type == "chatMemberStatusLeft") {
        m_status = new QTdChatMemberStatusLeft(this);
    } else if (type == "chatMemberStatusMember") {
        m_status = new QTdChatMemberStatusMember(this);
    } else if (type == "chatMemberStatusRestricted") {
        m_status = new QTdChatMemberStatusRestricted(this);
    }
    if (m_status) {
        m_status->unmarshalJson(status);
    }

    m_canInvite = json["anyone_can_invite"].toBool();
    m_signMessages = json["sign_messages"].toBool();
    m_isChannel = json["is_channel"].toBool();
    m_isVerified = json["is_verified"].toBool();
    m_restrictionReason = json["restriction_reason"].toString();
    emit superGroupChanged();
    emit chatStatusChanged();
}
