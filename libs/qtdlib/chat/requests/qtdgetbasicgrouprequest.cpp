#include "qtdgetbasicgrouprequest.h"

QTdGetBasicGroupRequest::QTdGetBasicGroupRequest(QObject *parent) : QTdRequest(parent),
    m_groupId(0)
{
}

void QTdGetBasicGroupRequest::setGroupId(const qint32 groupId)
{
    m_groupId = groupId;
}

QJsonObject QTdGetBasicGroupRequest::marshalJson()
{
    return QJsonObject{
        {"@type", "getBasicGroup"},
        {"basic_group_id", m_groupId},
    };
}
