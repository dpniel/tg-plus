#ifndef QTDGETSECRETCHATREQUEST_H
#define QTDGETSECRETCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdGetSecretChatRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetSecretChatRequest(QObject *parent = nullptr);

    void setSecretChatId(const qint32 &id);
    QJsonObject marshalJson() Q_DECL_FINAL;
private:
    qint32 m_chatId;
};

#endif // QTDGETSECRETCHATREQUEST_H
