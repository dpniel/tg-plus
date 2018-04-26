#include "qtdchattypefactory.h"
#include "qtdbasicgroupchat.h"
#include "qtdsecretchat.h"
#include "qtdsupergroupchat.h"

QTdChatType *QTdChatFactory::createType(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QTdChatType *chatType = Q_NULLPTR;
    if (type == "chatTypeBasicGroup") {
        chatType = new QTdChatTypeBasicGroup(parent);
    } else if (type == "chatTypePrivate") {
        chatType = new QTdChatTypePrivate(parent);
    } else if (type == "chatTypeSecret") {
        chatType = new QTdChatTypeSecret(parent);
    } else if (type == "chatTypeSupergroup") {
        chatType = new QTdChatTypeSuperGroup(parent);
    }
    if (chatType) {
        chatType->unmarshalJson(json);
    }
    return chatType;
}

QTdChat *QTdChatFactory::createChat(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QTdChat *chat = Q_NULLPTR;
    if (type == "chatTypeBasicGroup") {
        chat = new QTdBasicGroupChat(parent);
    } else if (type == "chatTypeSecret") {
        chat = new QTdSecretChat(parent);
    } else if (type == "chatTypeSupergroup") {
        chat = new QTdSuperGroupChat(parent);
    } else {
        chat = new QTdChat(parent);
    }
    return chat;
}
