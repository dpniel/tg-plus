#ifndef QTDGETCHATSREQUEST_H
#define QTDGETCHATSREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdGetChatsRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetChatsRequest(QObject *parent = nullptr);

    QJsonObject marshalJson() Q_DECL_FINAL;
};

#endif // QTDGETCHATSREQUEST_H
