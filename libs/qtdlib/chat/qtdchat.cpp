#include "qtdchat.h"
#include <QDebug>
#include "qtdchattypefactory.h"


QTdChat::QTdChat(QObject *parent) : QAbstractInt64Id(parent),
    m_chatType(0), m_chatPhoto(0), m_lastMessage(0),
    m_order(0), m_isPinned(false), m_canBeReported(false),
    m_unreadCount(0), m_lastReadInboxMsg(0), m_lastReadOutboxMsg(0),
    m_unreadMentionCount(0), m_notifySettings(Q_NULLPTR),
    m_messages(0)
{
    setType(CHAT);
    m_messages = new QQmlObjectListModel<QTdMessage>(this, "", "id");
    emit messagesChanged();
}

void QTdChat::unmarshalJson(const QJsonObject &json)
{
    m_title = json["title"].toString();
    emit titleChanged(m_title);

    if (m_chatType) {
        delete m_chatType;
        m_chatType = 0;
    }
    m_chatType = QTdChatFactory::createType(json["type"].toObject(), this);
    emit chatTypeChanged(m_chatType);

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

    m_order = json["order"];
    emit orderChanged();

    m_isPinned = json["is_pinned"].toBool();
    emit isPinnedChanged();

    m_canBeReported = json["can_be_reported"].toBool();
    emit canBeReportedChanged();

    m_unreadCount = json["unread_count"];
    emit unreadCountChanged();

    m_lastReadInboxMsg = json["last_read_inbox_message_id"];
    emit lastReadInboxMessageIdChanged();

    m_lastReadOutboxMsg = json["last_read_outbox_message_id"];
    emit lastReadOutboxMessageIdChanged();

    m_unreadMentionCount = json["unread_mention_count"];
    emit unreadMentionCountChanged();

    if (m_notifySettings) {
        delete m_notifySettings;
        m_notifySettings = 0;
    }
    m_notifySettings = new QTdNotificationSettings(this);
    m_notifySettings->unmarshalJson(json["notification_settings"].toObject());
    emit notificationSettingsChanged();

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

QString QTdChat::qmlOrder() const
{
    return m_order.toQmlValue();
}

qint64 QTdChat::order() const
{
    return m_order.value();
}

bool QTdChat::isPinned() const
{
    return m_isPinned;
}

bool QTdChat::canBeReported() const
{
    return m_canBeReported;
}

bool QTdChat::hasUnreadMessages() const
{
    return unreadCount() > 0;
}

QString QTdChat::qmlUnreadCount() const
{
    return m_unreadCount.toQmlValue();
}

qint32 QTdChat::unreadCount() const
{
    return m_unreadCount.value();
}

QString QTdChat::qmlLastReadInboxMessageId() const
{
    return m_lastReadInboxMsg.toQmlValue();
}

qint64 QTdChat::lastReadInboxMessageId() const
{
    return m_lastReadInboxMsg.value();
}

QString QTdChat::qmlLastReadOutboxMessageId() const
{
    return m_lastReadOutboxMsg.toQmlValue();
}

qint64 QTdChat::lastReadOutboxMessageId() const
{
    return m_lastReadOutboxMsg.value();
}

bool QTdChat::hasUnreadMentions() const
{
    return unreadMentionCount() > 0;
}

QString QTdChat::qmlUnreadMentionCount() const
{
    return m_unreadMentionCount.toQmlValue();
}

qint32 QTdChat::unreadMentionCount() const
{
    return m_unreadMentionCount.value();
}

QTdNotificationSettings *QTdChat::notificationSettings() const
{
    return m_notifySettings;
}

QTdChatType *QTdChat::chatType() const
{
    return m_chatType;
}

QTdChatPhoto::QTdChatPhoto(QObject *parent) : QTdPhoto(parent)
{
    setType(CHAT_PHOTO);
}
