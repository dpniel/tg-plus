#include "qtdchatlistmodel.h"
#include "client/qtdclient.h"
#include "chat/requests/qtdgetchatsrequest.h"
#include "chat/qtdchattypefactory.h"

QTdChatListModel::QTdChatListModel(QObject *parent) : QObject(parent),
    m_model(Q_NULLPTR)
{
    m_model = new QQmlObjectListModel<QTdChat>(this, "", "id");
    connect(QTdClient::instance(), &QTdClient::updateNewChat, this, &QTdChatListModel::handleUpdateNewChat);
    connect(QTdClient::instance(), &QTdClient::authStateChanged, this, &QTdChatListModel::handleAuthStateChanges);
}

QObject *QTdChatListModel::model() const
{
    return m_model;
}

void QTdChatListModel::handleUpdateNewChat(const QJsonObject &chat)
{
    qDebug() << "[UPDATING CHAT]" << chat;
    const qint64 id = qint64(chat["id"].toDouble());
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (!tdchat) {
        qDebug() << "Adding new chat to model";
        tdchat = QTdChatFactory::createChat(chat["type"].toObject());
        tdchat->unmarshalJson(chat);
        m_model->append(tdchat);
    }
    tdchat->unmarshalJson(chat);
    qDebug() << "[CHAT TITLE] >> " << tdchat->title();
}

void QTdChatListModel::handleAuthStateChanges(const QTdAuthState *state)
{
    switch (state->type()) {
    case QTdAuthState::Type::AUTHORIZATION_STATE_READY:
    {
        QTdGetChatsRequest *req = new QTdGetChatsRequest;
        QTdClient::instance()->send(req);
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_CLOSED:
    {
        m_model->clear();
        break;
    }
    default:
        return;
    }
}
