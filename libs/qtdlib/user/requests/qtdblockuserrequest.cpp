#include "qtdblockuserrequest.h"

QTdBlockUserRequest::QTdBlockUserRequest(QObject *parent) : QTdRequest(parent)
{
}

void QTdBlockUserRequest::setUser(QTdUser *user)
{
    m_userId = user->id();
}

void QTdBlockUserRequest::setUserId(const qint32 &id)
{
    m_userId = id;
}

void QTdBlockUserRequest::setUserId(const QString &id)
{
    m_userId = qint32(id.toInt());
}

QJsonObject QTdBlockUserRequest::marshalJson()
{
    return QJsonObject{
        {"@type", "blockUser"},
        {"user_id", m_userId},
    };
}
