#include "qtdopenchatrequest.h"

QTdOpenChatRequest::QTdOpenChatRequest(QObject *parent) : QTdRequest(parent),
    m_chatId(0)
{
}

void QTdOpenChatRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QTdOpenChatRequest::marshalJson()
{
    return QJsonObject{
        {"@type", "openChat"},
        {"chat_id", m_chatId}
    };
}
