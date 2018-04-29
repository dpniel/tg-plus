#ifndef QTDCLOSECHATREQUEST_H
#define QTDCLOSECHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdCloseChatRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_chatId;
public:
    explicit QTdCloseChatRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QTDCLOSECHATREQUEST_H
