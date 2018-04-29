#include "qtduser.h"
#include "qtduserstatusfactory.h"
#include "qtdlinkstatefactory.h"

QTdUser::QTdUser(QObject *parent) : QAbstractInt32Id(parent),
  m_status(Q_NULLPTR),
  m_profilePhoto(Q_NULLPTR),
  m_outgoingLink(Q_NULLPTR),
  m_incomingLink(Q_NULLPTR),
  m_isVerified(false),
  m_userType(Q_NULLPTR)
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
    m_isVerified = json["is_verified"].toBool();
    emit isVerifiedChanged(m_isVerified);
    m_restrictionReason = json["restriction_reason"].toString();
    emit restrictionReasonChanged(m_restrictionReason);
    m_languageCode = json["language_code"].toString();
    emit languageCodeChanged(m_languageCode);

    if (m_userType) {
        delete m_userType;
        m_userType = 0;
    }
    const QJsonObject typeObj = json["type"].toObject();
    const QString type = typeObj["@type"].toString();
    if (type == "userTypeRegular") {
        setType(USER_TYPE_REGULAR);
        m_userType = new QTdUserTypeRegular(this);
    } else if (type == "userTypeBot") {
        m_userType = new QTdUserTypeBot(this);
    } else if (type == "userTypeDeleted") {
        m_userType = new QTdUserTypeDeleted(this);
    } else if (type == "userTypeUnknown") {
        m_userType = new QTdUserTypeUnknown(this);
    }
    m_userType->unmarshalJson(typeObj);

    if (m_profilePhoto) {
        delete m_profilePhoto;
        m_profilePhoto = 0;
    }
    m_profilePhoto = new QTdProfilePhoto(this);
    m_profilePhoto->unmarshalJson(json["profile_photo"].toObject());
    emit profilePhotoChanged(m_profilePhoto);
    const bool hasProfilePhoto = m_profilePhoto->small()->id() > 0;
    const bool needsDownload = m_profilePhoto->small()->local()->path().isEmpty();
    if (hasProfilePhoto && needsDownload) {
        m_profilePhoto->small()->downloadFile();
    }

    if (m_outgoingLink) {
        delete m_outgoingLink;
        m_outgoingLink = 0;
    }
    m_outgoingLink = QTdLinkStateFactory::create(json["outgoing_link"].toObject(), this);
    emit outgoingLinkChanged(m_outgoingLink);

    if (m_incomingLink) {
        delete m_incomingLink;
        m_incomingLink = 0;
    }
    m_incomingLink = QTdLinkStateFactory::create(json["incoming_link"].toObject(), this);
    emit incomingLinkChanged(m_incomingLink);

    QAbstractInt32Id::unmarshalJson(json);
}

QTdUserType *QTdUser::userType() const
{
    return m_userType;
}

QString QTdUser::restrictionReason() const
{
    return m_restrictionReason;
}

QString QTdUser::languageCode() const
{
    return m_languageCode;
}

bool QTdUser::isVerified() const
{
    return m_isVerified;
}

QTdLinkState *QTdUser::outgoingLink() const
{
    return m_outgoingLink;
}

QTdLinkState *QTdUser::incomingLink() const
{
    return m_incomingLink;
}

QTdProfilePhoto *QTdUser::profilePhoto() const
{
    return m_profilePhoto;
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
    if (m_status) {
        delete m_status;
        m_status = 0;
    }
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
