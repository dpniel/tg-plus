#include "qtdgetsupergrouprequest.h"

QTdGetSuperGroupRequest::QTdGetSuperGroupRequest(QObject *parent) : QTdRequest(parent),
    m_sgId(0)
{
}

void QTdGetSuperGroupRequest::setSuperGroupId(const qint32 &id)
{
    m_sgId = id;
}

QJsonObject QTdGetSuperGroupRequest::marshalJson()
{
    return QJsonObject{
        {"@type", "getSupergroup"},
        {"supergroup_id", m_sgId},
    };
}
