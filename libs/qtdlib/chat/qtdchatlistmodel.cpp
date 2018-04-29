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
    connect(QTdClient::instance(), &QTdClient::updateChatOrder, this, &QTdChatListModel::handleUpdateChatOrder);
    connect(QTdClient::instance(), &QTdClient::updateChatLastMessage, this, &QTdChatListModel::handleUpdateChatLastMessage);
    connect(QTdClient::instance(), &QTdClient::updateChatReadInbox, this, &QTdChatListModel::updateChatReadInbox);
    connect(QTdClient::instance(), &QTdClient::updateChatIsPinned, this, &QTdChatListModel::handleUpdateChatIsPinned);
    connect(QTdClient::instance(), &QTdClient::updateChatPhoto, this, &QTdChatListModel::handleUpdateChatPhoto);
    connect(QTdClient::instance(), &QTdClient::updateChatReplyMarkup, this, &QTdChatListModel::handleUpdateChatReplyMarkup);
    connect(QTdClient::instance(), &QTdClient::updateChatTitle, this, &QTdChatListModel::handleUpdateChatTitle);
    connect(QTdClient::instance(), &QTdClient::updateChatUnreadMentionCount, this, &QTdChatListModel::handleUpdateChatUnreadMentionCount);
}

QObject *QTdChatListModel::model() const
{
    return m_model;
}

void QTdChatListModel::handleUpdateNewChat(const QJsonObject &chat)
{
    const qint64 id = qint64(chat["id"].toDouble());
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (!tdchat) {
        tdchat = QTdChatFactory::createChat(chat["type"].toObject());
        tdchat->unmarshalJson(chat);
        m_model->append(tdchat);
        connect(tdchat, &QTdChat::chatStatusChanged, this, &QTdChatListModel::chatStatusChanged);
    }
    tdchat->unmarshalJson(chat);
    emit contentsChanged();
}

void QTdChatListModel::handleUpdateChatOrder(const QJsonObject &json)
{
    const qint64 id = qint64(json["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        tdchat->updateChatOrder(json);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatLastMessage(const QJsonObject chat)
{
    const qint64 id = qint64(chat["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        // TODO: update last message
        tdchat->lastMessage()->unmarshalJson(chat["last_message"].toObject());
        qDebug() << "Updating chat order";
        tdchat->updateChatOrder(chat);
        emit contentsChanged();
//        QTdClient::instance()->send(QJsonObject{
//                                        {"@type", "getChatHistory"},
//                                        {"chat_id", QString::number(tdchat->id())},
//                                        {"from_message_id", tdchat->lastMessage()->id()},
//                                        {"offset", 0},
//                                        {"limit", 100},
//                                        {"only_local", false},
//                                        {"@extra", tdchat->title()},
//                                    });
    }
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

void QTdChatListModel::updateChatReadInbox(const QJsonObject &json)
{
    const qint64 id = qint64(json["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        qDebug() << "Updating chat read inbox";
        tdchat->updateChatReadInbox(json);
        emit contentsChanged();
    }
}

void QTdChatListModel::updateChatReadOutbox(const QJsonObject &json)
{
    const qint64 id = qint64(json["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        qDebug() << "Updating chat read outbox";
        tdchat->updateChatReadOutbox(json);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatIsPinned(const QJsonObject &json)
{
    const qint64 id = qint64(json["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        qDebug() << "Updating chat isPinned";
        tdchat->updateChatIsPinned(json);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatPhoto(const QJsonObject &chat)
{
    const qint64 id = qint64(chat["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        qDebug() << "Updating chat photo";
        tdchat->updateChatPhoto(chat["photo"].toObject());
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatReplyMarkup(const QJsonObject &chat)
{
    const qint64 id = qint64(chat["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        qDebug() << "Updating chat reply markup";
        tdchat->updateChatReplyMarkup(chat);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatTitle(const QJsonObject &chat)
{
    const qint64 id = qint64(chat["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        qDebug() << "Updating chat title";
        tdchat->updateChatTitle(chat);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatUnreadMentionCount(const QJsonObject &chat)
{
    const qint64 id = qint64(chat["chat_id"].toDouble());
    QTdChat *tdchat = m_model->getByUid(QString::number(id));
    if (tdchat) {
        qDebug() << "Updating chat unread mention count";
        tdchat->updateChatUnreadMentionCount(chat);
        emit contentsChanged();
    }
}
