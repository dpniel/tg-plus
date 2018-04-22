#ifndef QTDBLOCKUSERREQUEST_H
#define QTDBLOCKUSERREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "user/qtduser.h"

/**
 * @brief The QTdBlockUserRequest class
 *
 * Add a user to the blacklist
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1block_user.html
 *
 * Usage:
 *
 *   auto *req = new QTdBlockUserRequest;
 *   req->setUserId(1);
 *   // or
 *   req->setUserId("1");
 *   // or
 *   QTdUser *user;
 *   req->setUser(user);
 *   QTdClient::instance()->send(req);
 */
class QTdBlockUserRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdBlockUserRequest(QObject *parent = nullptr);

    void setUser(QTdUser *user);
    void setUserId(const qint32 &id);
    void setUserId(const QString &id);

    QJsonObject marshalJson() Q_DECL_FINAL;

private:
    qint32 m_userId;
};

#endif // QTDBLOCKUSERREQUEST_H
