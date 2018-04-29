#ifndef QTDOPENCHATREQUEST_H
#define QTDOPENCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdOpenChatRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_chatId;
public:
    explicit QTdOpenChatRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QTDOPENCHATREQUEST_H
