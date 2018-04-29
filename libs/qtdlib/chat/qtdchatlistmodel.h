#ifndef QTDCHATLISTMODEL_H
#define QTDCHATLISTMODEL_H

#include <QObject>
#include "auth/qtdauthstate.h"
#include "models/QmlObjectListModel.h"
#include "qtdchat.h"

class QTdChatListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)
public:
    explicit QTdChatListModel(QObject *parent = nullptr);

    QObject* model() const;

signals:
    void modelChanged(QObject* model);
    void contentsChanged();
    void chatStatusChanged();

private slots:
    void handleUpdateNewChat(const QJsonObject &chat);
    void handleUpdateChatOrder(const QJsonObject &json);
    void handleUpdateChatLastMessage(const QJsonObject chat);
    void handleAuthStateChanges(const QTdAuthState *state);
    void updateChatReadInbox(const QJsonObject &json);
    void updateChatReadOutbox(const QJsonObject &json);
    void handleUpdateChatIsPinned(const QJsonObject &json);
    void handleUpdateChatPhoto(const QJsonObject &chat);
    void handleUpdateChatReplyMarkup(const QJsonObject &chat);
    void handleUpdateChatTitle(const QJsonObject &chat);
    void handleUpdateChatUnreadMentionCount(const QJsonObject &chat);
private:
    QQmlObjectListModel<QTdChat> *m_model;
};

#endif // QTDCHATLISTMODEL_H
