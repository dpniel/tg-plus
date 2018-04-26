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

public slots:

private slots:
    void handleUpdateNewChat(const QJsonObject &chat);

    void handleAuthStateChanges(const QTdAuthState *state);

private:
    QQmlObjectListModel<QTdChat> *m_model;
};

#endif // QTDCHATLISTMODEL_H
