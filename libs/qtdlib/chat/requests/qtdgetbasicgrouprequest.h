#ifndef QTDGETBASICGROUPREQUEST_H
#define QTDGETBASICGROUPREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdGetBasicGroupRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetBasicGroupRequest(QObject *parent = nullptr);

    void setGroupId(const qint32 groupId);

    QJsonObject marshalJson() Q_DECL_FINAL;
private:
    qint32 m_groupId;
};

#endif // QTDGETBASICGROUPREQUEST_H
