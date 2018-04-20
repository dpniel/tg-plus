#ifndef QTDUSER_H
#define QTDUSER_H

#include <QObject>
#include "common/qabstractint32id.h"
#include "qtduserstatus.h"

/**
 * @brief The QTdUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user.html
 */
class QTdUser : public QAbstractInt32Id
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QTdUserStatus* status READ status WRITE setStatus NOTIFY statusChanged)
public:
    explicit QTdUser(QObject *parent = nullptr);

    QString firstName() const;
    QString lastName() const;
    QString username() const;
    QString phoneNumber() const;
    QTdUserStatus* status() const;

    void unmarshalJson(const QJsonObject &json) Q_DECL_FINAL;

signals:
    void firstNameChanged(QString firstName);
    void lastNameChanged(QString lastName);
    void usernameChanged(QString username);
    void phoneNumberChanged(QString phoneNumber);
    void statusChanged(QTdUserStatus* status);

public slots:
    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setUsername(QString username);
    void setPhoneNumber(QString phoneNumber);
    void setStatus(QTdUserStatus* status);

private:
    QString m_firstName;
    QString m_lastName;
    QString m_username;
    QString m_phoneNumber;
    QTdUserStatus* m_status;
};

#endif // QTDUSER_H
