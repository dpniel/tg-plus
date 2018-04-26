#include "messagelist.h"

MessageList::MessageList(QObject *parent) : QObject(parent),
    m_chatList(0)
{

}

ChatList *MessageList::chatList() const
{
    return m_chatList;
}

void MessageList::setChatList(ChatList *chatList)
{
    if (m_chatList == chatList)
        return;

    m_chatList = chatList;
    emit chatListChanged(m_chatList);
}
