#include "chatlist.h"
#include "client/qtdclient.h"

ChatList::ChatList(QObject *parent) : QObject(parent),
    m_model(Q_NULLPTR)
{
    m_model = new QQmlObjectListModel<QTdChat>(this, "", "id");
    connect(QTdClient::instance(), &QTdClient::updateNewChat, this, &ChatList::handleUpdateNewChat);
}

QObject *ChatList::model() const
{
    return m_model;
}

void ChatList::handleUpdateNewChat(const QJsonObject &chat)
{
    qDebug() << "[UPDATING CHAT]" << chat;
    const qint64 id = qint64(chat["id"].toDouble());
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (!tdchat) {
        qDebug() << "Adding new chat to model";
        tdchat = new QTdChat();
        tdchat->unmarshalJson(chat);
        m_model->append(tdchat);
    }
    tdchat->unmarshalJson(chat);
    qDebug() << "[CHAT TITLE] >> " << tdchat->title();
}
