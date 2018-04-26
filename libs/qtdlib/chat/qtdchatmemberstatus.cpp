#include "qtdchatmemberstatus.h"

QTdChatMemberStatus::QTdChatMemberStatus(QObject *parent) : QAbstractTdObject(parent)
{
}

QTdChatMemberStatusAdmin::QTdChatMemberStatusAdmin(QObject *parent) : QTdChatMemberStatus(parent),
    m_canBeEdited(false), m_canChangeInfo(false), m_canPostMessages(false),
    m_canEditMessages(false), m_canDeleteMessages(false), m_canInviteUsers(false),
    m_canRestrictMembers(false), m_canPinMessages(false), m_canPromoteMembers(false)
{
    setType(CHAT_MEMBER_STATUS_ADMIN);
}

bool QTdChatMemberStatusAdmin::canBeEdited() const
{
    return m_canBeEdited;
}

bool QTdChatMemberStatusAdmin::canChangeInfo() const
{
    return m_canChangeInfo;
}

bool QTdChatMemberStatusAdmin::canPostMessages() const
{
    return m_canPostMessages;
}

bool QTdChatMemberStatusAdmin::canEditMessages() const
{
    return m_canEditMessages;
}

bool QTdChatMemberStatusAdmin::canDeleteMessages() const
{
    return m_canDeleteMessages;
}

bool QTdChatMemberStatusAdmin::canInviteUsers() const
{
    return m_canInviteUsers;
}

bool QTdChatMemberStatusAdmin::canRestrictMembers() const
{
    return m_canRestrictMembers;
}

bool QTdChatMemberStatusAdmin::canPinMessages() const
{
    return m_canPinMessages;
}

bool QTdChatMemberStatusAdmin::canPromoteMembers() const
{
    return m_canPromoteMembers;
}

void QTdChatMemberStatusAdmin::unmarshalJson(const QJsonObject &json)
{
    m_canBeEdited = json["can_be_edited"].toBool();
    m_canChangeInfo = json["can_change_info"].toBool();
    m_canPostMessages = json["can_post_messages"].toBool();
    m_canEditMessages = json["can_edit_messages"].toBool();
    m_canDeleteMessages = json["can_delete_messages"].toBool();
    m_canInviteUsers = json["can_invite_users"].toBool();
    m_canRestrictMembers = json["can_restrict_members"].toBool();
    m_canPinMessages = json["can_pin_messages"].toBool();
    m_canPromoteMembers = json["can_promote_members"].toBool();
    emit statusChanged();
}

QTdChatMemberStatusBanned::QTdChatMemberStatusBanned(QObject *parent) : QTdChatMemberStatus(parent),
    m_bannedTil(0)
{
    setType(CHAT_MEMBER_STATUS_BANNED);
}

QDateTime QTdChatMemberStatusBanned::qmlBannedUntilDate() const
{
    return QDateTime::fromTime_t(m_bannedTil);
}

qint32 QTdChatMemberStatusBanned::bannedUntilDate() const
{
    return m_bannedTil;
}

void QTdChatMemberStatusBanned::unmarshalJson(const QJsonObject &json)
{
    m_bannedTil = qint32(json["banned_until_date"].toInt());
    emit statusChanged();
}

QTdChatMemberStatusCreator::QTdChatMemberStatusCreator(QObject *parent) : QTdChatMemberStatus(parent),
    m_isMember(false)
{
    setType(CHAT_MEMBER_STATUS_CREATOR);
}

bool QTdChatMemberStatusCreator::isMember() const
{
    return m_isMember;
}

void QTdChatMemberStatusCreator::unmarshalJson(const QJsonObject &json)
{
    m_isMember = json["is_member"].toBool();
    emit statusChanged();
}

QTdChatMemberStatusLeft::QTdChatMemberStatusLeft(QObject *parent) : QTdChatMemberStatus(parent)
{
    setType(CHAT_MEMBER_STATUS_LEFT);
}

QTdChatMemberStatusMember::QTdChatMemberStatusMember(QObject *parent) : QTdChatMemberStatus(parent)
{
    setType(CHAT_MEMBER_STATUS_MEMBER);
}

QTdChatMemberStatusRestricted::QTdChatMemberStatusRestricted(QObject *parent) : QTdChatMemberStatus(parent),
    m_isMember(false), m_restrictedUntil(0), m_canSendMessages(false),
    m_canSendMediaMessages(false), m_canSendOtherMessages(false), m_canAddWebPagePreviews(false)
{
    setType(CHAT_MEMBER_STATUS_RESTRICTED);
}

void QTdChatMemberStatusRestricted::unmarshalJson(const QJsonObject &json)
{
    m_isMember = json["is_member"].toBool();
    m_restrictedUntil = qint32(json["restricted_until_date"].toInt());
    m_canSendMessages = json["can_send_messages"].toBool();
    m_canSendMediaMessages = json["can_send_media_messages"].toBool();
    m_canSendOtherMessages = json["can_send_other_messages"].toBool();
    m_canAddWebPagePreviews = json["can_add_web_page_previews"].toBool();
    emit statusChanged();
}

bool QTdChatMemberStatusRestricted::isMember() const
{
    return m_isMember;
}

QDateTime QTdChatMemberStatusRestricted::qmlRestrictedUntil() const
{
    return QDateTime::fromTime_t(m_restrictedUntil);
}

qint32 QTdChatMemberStatusRestricted::restrictedUntil() const
{
    return m_restrictedUntil;
}

bool QTdChatMemberStatusRestricted::canSendMessages() const
{
    return m_canSendMessages;
}

bool QTdChatMemberStatusRestricted::canSendMediaMessages() const
{
    return m_canSendMediaMessages;
}

bool QTdChatMemberStatusRestricted::canSendOtherMessages() const
{
    return m_canSendOtherMessages;
}

bool QTdChatMemberStatusRestricted::canAddWebPagePreviews() const
{
    return m_canAddWebPagePreviews;
}
