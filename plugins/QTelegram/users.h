#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QJsonObject>
#include <user/qtduser.h>
#include "models/QmlObjectListModel.h"

class Users : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)
public:
    explicit Users(QObject *parent = nullptr);

    QObject* model() const;

signals:
    void modelChanged(QObject* model);

public slots:

private slots:
    void handleUpdateUser(const QJsonObject &user);
    void handleUpdateUserStatus(const QString &userId, const QJsonObject &status);

private:
    QQmlObjectListModel<QTdUser> *m_model;
};

#endif // USERS_H
