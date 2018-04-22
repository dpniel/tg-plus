#ifndef QTDCHAT_H
#define QTDCHAT_H

#include <QObject>
#include "common/qabstractint64id.h"
#include "qtdchattype.h"
#include "messages/qtdmessage.h"
#include "user/qtdprofilephoto.h"

class QTdChatPhoto : public QTdProfilePhoto
{
    Q_OBJECT
public:
    explicit QTdChatPhoto(QObject *parent = Q_NULLPTR);
};

class QTdChat : public QAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QTdChatType* chatType READ chatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QTdChatPhoto* chatPhoto READ chatPhoto NOTIFY chatPhotoChanged)
    Q_PROPERTY(QTdMessage* lastMessage READ lastMessage NOTIFY lastMessageChanged)
    Q_PROPERTY(QString unreadCount READ qmlUnreadCount NOTIFY unreadCountChanged)
public:
    explicit QTdChat(QObject *parent = nullptr);
    void unmarshalJson(const QJsonObject &json);
    QTdChatType *chatType() const;
    QString title() const;
    QTdMessage *lastMessage() const;
    QTdChatPhoto *chatPhoto() const;
    QString qmlUnreadCount() const;
    qint32 unreadCount() const;

signals:
    void chatTypeChanged(QTdChatType *chatType);
    void titleChanged(QString title);
    void lastMessageChanged(QTdMessage *lastMessage);
    void chatPhotoChanged(QTdChatPhoto *chatPhoto);
    void unreadCountChanged();

private:
    QTdChatType *m_chatType;
    QString m_title;
    QTdMessage *m_lastMessage;
    QTdChatPhoto *m_chatPhoto;
    QTdInt32 m_unreadCount;
};

#endif // QTDCHAT_H
