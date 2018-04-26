#ifndef MESSAGELIST_H
#define MESSAGELIST_H

#include <QObject>
#include <QPointer>
#include "chatlist.h"

class MessageList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChatList* chatList READ chatList WRITE setChatList NOTIFY chatListChanged)

public:
    explicit MessageList(QObject *parent = nullptr);

    ChatList *chatList() const;

signals:
    void chatListChanged(ChatList *chatList);

public slots:
    void setChatList(ChatList *chatList);
private:
    QPointer<ChatList> m_chatList;
};

#endif // MESSAGELIST_H
