#include "qtdusertype.h"

QTdUserType::QTdUserType(QObject *parent) : QAbstractTdObject(parent)
{
}

QTdUserTypeBot::QTdUserTypeBot(QObject *parent) : QTdUserType(parent),
    m_canJoinGroups(false), m_canReadAllGroupMessages(false),
    m_isInline(false), m_needLocation(false)
{
    setType(USER_TYPE_BOT);
}

bool QTdUserTypeBot::canJoinGroups() const
{
    return m_canJoinGroups;
}

bool QTdUserTypeBot::canReadAllGroupMessages() const
{
    return m_canReadAllGroupMessages;
}

bool QTdUserTypeBot::isInline() const
{
    return m_isInline;
}

QString QTdUserTypeBot::placeholder() const
{
    return m_inlineQueryPlaceholder;
}

bool QTdUserTypeBot::needLocation() const
{
    return m_needLocation;
}

void QTdUserTypeBot::unmarshalJson(const QJsonObject &json)
{
    m_canJoinGroups = json["can_join_groups"].toBool();
    m_canReadAllGroupMessages = json["can_read_all_group_messages"].toBool();
    m_isInline = json["is_inline"].toBool();
    m_inlineQueryPlaceholder = json["inline_query_placeholder"].toString();
    m_needLocation = json["need_location"].toBool();
    QTdUserType::unmarshalJson(json);
    emit userTypeDataChanged();
}

QTdUserTypeDeleted::QTdUserTypeDeleted(QObject *parent) : QTdUserType(parent)
{
    setType(USER_TYPE_DELETED);
}

QTdUserTypeRegular::QTdUserTypeRegular(QObject *parent) : QTdUserType(parent)
{
    setType(USER_TYPE_REGULAR);
}

QTdUserTypeUnknown::QTdUserTypeUnknown(QObject *parent) : QTdUserType(parent)
{
    setType(USER_TYPE_UNKNOWN);
}
