#include "qtduser.h"
#include "qtduserstatusfactory.h"

QTdUser::QTdUser(QObject *parent) : QAbstractInt32Id(parent),
  m_status(Q_NULLPTR)
{
    setType(USER);
}

void QTdUser::unmarshalJson(const QJsonObject &json)
{
    setFirstName(json["first_name"].toString());
    setLastName(json["last_name"].toString());
    setUsername(json["username"].toString());
    setPhoneNumber(json["phone_number"].toString());
    setStatus(QTdUserStatusFactory::create(json["status"].toObject(), this));

    const QJsonObject typeObj = json["type"].toObject();
    const QString type = typeObj["@type"].toString();
    if (type == "userTypeRegular") {
        setType(USER_TYPE_REGULAR);
    } else if (type == "userTypeBot") {
        setType(USER_TYPE_BOT);
    } else if (type == "userTypeDeleted") {
        setType(USER_TYPE_DELETED);
    } else if (type == "userTypeUnknown") {
        setType(USER_TYPE_UNKNOWN);
    }
    QAbstractInt32Id::unmarshalJson(json);
}

QTdUserStatus *QTdUser::status() const
{
    return m_status;
}

void QTdUser::setFirstName(QString firstName)
{
    if (m_firstName == firstName)
        return;

    m_firstName = firstName;
    emit firstNameChanged(m_firstName);
}

void QTdUser::setLastName(QString lastName)
{
    if (m_lastName == lastName)
        return;

    m_lastName = lastName;
    emit lastNameChanged(m_lastName);
}

void QTdUser::setUsername(QString username)
{
    if (m_username == username)
        return;

    m_username = username;
    emit usernameChanged(m_username);
}

void QTdUser::setPhoneNumber(QString phoneNumber)
{
    if (m_phoneNumber == phoneNumber)
        return;

    m_phoneNumber = phoneNumber;
    emit phoneNumberChanged(m_phoneNumber);
}

void QTdUser::setStatus(QTdUserStatus *status)
{
    m_status = status;
    emit statusChanged(m_status);
}

QString QTdUser::firstName() const
{
    return m_firstName;
}

QString QTdUser::lastName() const
{
    return m_lastName;
}

QString QTdUser::username() const
{
    return m_username;
}

QString QTdUser::phoneNumber() const
{
    return m_phoneNumber;
}
