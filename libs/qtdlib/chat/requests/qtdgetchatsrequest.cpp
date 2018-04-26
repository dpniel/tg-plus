#include "qtdgetchatsrequest.h"

QTdGetChatsRequest::QTdGetChatsRequest(QObject *parent) : QTdRequest(parent)
{

}

QJsonObject QTdGetChatsRequest::marshalJson()
{
    return QJsonObject {
        { "@type",       "getChats" },
        { "offset_order", "1000000" },
        { "offset_chat_id", 1000000 },
        { "limit",          1000000 },
    };
}
