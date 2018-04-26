#ifndef QTDGETSUPERGROUPREQUEST_H
#define QTDGETSUPERGROUPREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdGetSuperGroupRequest : public QTdRequest
{
    Q_OBJECT
    qint32 m_sgId;
public:
    explicit QTdGetSuperGroupRequest(QObject *parent = nullptr);
    void setSuperGroupId(const qint32 &id);
    QJsonObject marshalJson() Q_DECL_FINAL;
};

#endif // QTDGETSUPERGROUPREQUEST_H
