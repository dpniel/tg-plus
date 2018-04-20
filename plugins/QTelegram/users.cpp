#include "users.h"
#include <QDebug>
#include "client/qtdclient.h"
#include "common/qtdint.h"
#include "user/qtduserstatusfactory.h"

Users::Users(QObject *parent) : QObject(parent),
    m_model(Q_NULLPTR)
{
    m_model = new QQmlObjectListModel<QTdUser>(this, "", "id");
    connect(QTdClient::instance(), &QTdClient::updateUser, this, &Users::handleUpdateUser);
    connect(QTdClient::instance(), &QTdClient::updateUserStatus, this, &Users::handleUpdateUserStatus);
}

QObject *Users::model() const
{
    return m_model;
}

void Users::handleUpdateUser(const QJsonObject &user)
{
    qDebug() << "[UPDATING USER]" << user;
    const qint32 uid = qint32(user["id"].toInt());
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QTdUser *tduser = m_model->getByUid(QString::number(uid));
    if (!tduser) {
        qDebug() << "Adding new user to model";
        tduser = new QTdUser();
        tduser->unmarshalJson(user);
        m_model->append(tduser);
    }
    tduser->unmarshalJson(user);
    qDebug() << "[USERNAME] >> " << tduser->username();
}

void Users::handleUpdateUserStatus(const QString &userId, const QJsonObject &status)
{
    qDebug() << "[UPDATING USER STATUS]" << userId;
    QTdUser *tduser = m_model->getByUid(userId);
    if (tduser) {
        qDebug() << "Updating existing user status: " << tduser->id();
        tduser->setStatus(QTdUserStatusFactory::create(status, tduser));
    }
}
