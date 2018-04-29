#include "qtdgetchatsrequest.h"

QTdGetChatsRequest::QTdGetChatsRequest(QObject *parent) : QTdRequest(parent)
{

}

QJsonObject QTdGetChatsRequest::marshalJson()
{
    return QJsonObject {
        { "@type",       "getChats" },
        { "offset_order", QString::number(std::numeric_limits<std::int64_t>::max())},
        { "offset_chat_id", 0 },
        { "limit",          20 },
    };
}
