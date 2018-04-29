#ifndef CHATLIST_H
#define CHATLIST_H

#include <QObject>
#include <qtdlib/chat/qtdchat.h>
#include <qtdlib/models/QmlObjectListModel.h>
#include <qtdlib/auth/qtdauthstate.h>

class ChatList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)
public:
    explicit ChatList(QObject *parent = nullptr);

    QObject* model() const;

signals:
    void modelChanged(QObject* model);

public slots:

private slots:
    void handleUpdateNewChat(const QJsonObject &chat);
    void handleAuthStateChanges(const QTdAuthState *state);

private:
    QQmlObjectListModel<QTdChat> *m_model;
};

#endif // CHATLIST_H
