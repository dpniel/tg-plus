#include "qtduserstatus.h"

QTdUserStatus::QTdUserStatus(QObject *parent) : QAbstractTdObject(parent)
{
}

QTdUserStatusEmpty::QTdUserStatusEmpty(QObject *parent) : QTdUserStatus(parent)
{
    setType(USER_STATUS_EMPTY);
}

QTdUserStateLastMonth::QTdUserStateLastMonth(QObject *parent) : QTdUserStatus(parent)
{
    setType(USER_STATUS_LAST_MONTH);
}

QTdUserStatusLastWeek::QTdUserStatusLastWeek(QObject *parent) : QTdUserStatus(parent)
{
    setType(USER_STATUS_LAST_WEEK);
}

QTdUserStatusOffline::QTdUserStatusOffline(QObject *parent) : QTdUserStatus(parent)
{
    setType(USER_STATUS_OFFLINE);
}

QDateTime QTdUserStatusOffline::wasOnline() const
{
    return m_wasOnline;
}

void QTdUserStatusOffline::unmarshalJson(const QJsonObject &json)
{
    m_wasOnline.setTime_t(json["was_online"].toInt());
    emit wasOnlineChanged(m_wasOnline);
    QAbstractTdObject::unmarshalJson(json);
}

QTdUserStatusOnline::QTdUserStatusOnline(QObject *parent) : QTdUserStatus(parent)
{
    setType(USER_STATUS_ONLINE);
}

QDateTime QTdUserStatusOnline::expires() const
{
    return m_expires;
}

void QTdUserStatusOnline::unmarshalJson(const QJsonObject &json)
{
    m_expires.setTime_t(json["expires"].toInt());
    emit expiresChanged();
    QAbstractTdObject::unmarshalJson(json);
}

QTdUserStatusRecently::QTdUserStatusRecently(QObject *parent) : QTdUserStatus(parent)
{
    setType(USER_STATUS_RECENTLY);
}
