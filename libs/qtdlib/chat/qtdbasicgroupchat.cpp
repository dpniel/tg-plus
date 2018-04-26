#include "qtdbasicgroupchat.h"
#include <QDebug>
#include "chat/requests/qtdgetbasicgrouprequest.h"
#include "client/qtdclient.h"

QTdBasicGroupChat::QTdBasicGroupChat(QObject *parent) : QTdChat(parent),
    m_groupId(0), m_memberCount(0), m_status(Q_NULLPTR),
    m_everyoneIsAdmin(false), m_isActive(false), m_upgradedSGID(0)
{
    connect(this, &QTdChat::chatTypeChanged, this, &QTdBasicGroupChat::requestGroupData);
    connect(QTdClient::instance(), &QTdClient::updateBasicGroup, this, &QTdBasicGroupChat::updateGroupData);
}

QString QTdBasicGroupChat::qmlGroupId() const
{
    return m_groupId.toQmlValue();
}

qint32 QTdBasicGroupChat::groupId() const
{
    return m_groupId.value();
}

QString QTdBasicGroupChat::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

qint32 QTdBasicGroupChat::memberCount() const
{
    return m_memberCount.value();
}

QTdChatMemberStatus *QTdBasicGroupChat::status() const
{
    return m_status;
}

bool QTdBasicGroupChat::everyoneIsAdmin() const
{
    return m_everyoneIsAdmin;
}

bool QTdBasicGroupChat::isActive() const
{
    return m_isActive;
}

QString QTdBasicGroupChat::qmlUpgradedToSuperGroupId() const
{
    return m_upgradedSGID.toQmlValue();
}

qint32 QTdBasicGroupChat::upgradedToSuperGroupId() const
{
    return m_upgradedSGID.value();
}

void QTdBasicGroupChat::requestGroupData()
{
    QTdChatTypeBasicGroup *group = qobject_cast<QTdChatTypeBasicGroup*>(chatType());
    if (group->basicGroupId() > 0) {
        auto *req = new QTdGetBasicGroupRequest;
        req->setGroupId(group->basicGroupId());
        QTdClient::instance()->send(req);
    }
}

void QTdBasicGroupChat::updateGroupData(const QJsonObject &json)
{
    QTdChatTypeBasicGroup *group = qobject_cast<QTdChatTypeBasicGroup*>(chatType());
    const qint32 gid = qint32(json["id"].toInt());
    if (gid != group->basicGroupId()) {
        return;
    }
    m_groupId = gid;
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

    m_everyoneIsAdmin = json["everyone_is_administrator"].toBool();
    m_isActive = json["is_active"].toBool();
    m_upgradedSGID = json["upgraded_to_supergroup_id"];
    emit groupChanged();
}
