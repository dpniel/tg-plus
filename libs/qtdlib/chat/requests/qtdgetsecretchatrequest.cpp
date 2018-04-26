#include "qtdgetsecretchatrequest.h"

QTdGetSecretChatRequest::QTdGetSecretChatRequest(QObject *parent) : QTdRequest(parent),
    m_chatId(0)
{
}

void QTdGetSecretChatRequest::setSecretChatId(const qint32 &id)
{
    m_chatId = id;
}

QJsonObject QTdGetSecretChatRequest::marshalJson()
{
    return QJsonObject{
        {"@type", "getSecretChat"},
        {"secret_chat_id", m_chatId},
    };
}
