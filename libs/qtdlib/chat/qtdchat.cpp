#include "qtdchat.h"
#include <QDebug>

QTdChat::QTdChat(QObject *parent) : QAbstractInt64Id(parent),
    m_chatType(0), m_chatPhoto(0), m_lastMessage(0), m_unreadCount(0)
{
    setType(CHAT);
}

void QTdChat::unmarshalJson(const QJsonObject &json)
{
    m_title = json["title"].toString();
    emit titleChanged(m_title);

    if (m_chatPhoto) {
        delete m_chatPhoto;
        m_chatPhoto = 0;
    }
    m_chatPhoto = new QTdChatPhoto(this);
    m_chatPhoto->unmarshalJson(json["photo"].toObject());
    emit chatPhotoChanged(m_chatPhoto);
    if (m_chatPhoto->small()->local()->path().isEmpty()) {
        m_chatPhoto->small()->downloadFile();
    }

    if (m_lastMessage) {
        delete m_lastMessage;
        m_lastMessage = 0;
    }
    m_lastMessage = new QTdMessage(this);
    m_lastMessage->unmarshalJson(json["last_message"].toObject());
    emit lastMessageChanged(m_lastMessage);

    m_unreadCount = json["unread_count"];
    emit unreadCountChanged();

    QAbstractInt64Id::unmarshalJson(json);
}

QString QTdChat::title() const
{
    return m_title;
}

QTdMessage *QTdChat::lastMessage() const
{
    return m_lastMessage;
}

QTdChatPhoto *QTdChat::chatPhoto() const
{
    return m_chatPhoto;
}

QString QTdChat::qmlUnreadCount() const
{
    return m_unreadCount.toQmlValue();
}

qint32 QTdChat::unreadCount() const
{
    return m_unreadCount.value();
}

QTdChatType *QTdChat::chatType() const
{
    return m_chatType;
}

QTdChatPhoto::QTdChatPhoto(QObject *parent) : QTdProfilePhoto(parent)
{
    setType(CHAT_PHOTO);
}
