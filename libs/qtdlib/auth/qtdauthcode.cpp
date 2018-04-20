#include "qtdauthcode.h"
#include <QDebug>

QTdAuthCode::QTdAuthCode(QObject *parent) : QAbstractTdObject(parent)
{

}

QTdAuthCodeTelegramMessage::QTdAuthCodeTelegramMessage(QObject *parent) : QTdAuthCode(parent),
    m_length(0)
{
    setType(AUTHENTICATION_CODE_TYPE_TELEGRAM_MESSAGE);
}

QString QTdAuthCodeTelegramMessage::qmlLength() const
{
    return m_length.toQmlValue();
}

qint32 QTdAuthCodeTelegramMessage::length() const
{
    return m_length.value();
}

void QTdAuthCodeTelegramMessage::unmarshalJson(const QJsonObject &json)
{
    if (json.contains("length")) {
        m_length = json["length"];
        emit lengthChanged();
    }
    QTdAuthCode::unmarshalJson(json);
}

QTdAuthCodeSms::QTdAuthCodeSms(QObject *parent) : QTdAuthCode(parent),
    m_length(0)
{
    setType(AUTHENTICATION_CODE_TYPE_SMS);
}

QString QTdAuthCodeSms::qmlLength() const
{
    return m_length.toQmlValue();
}

qint32 QTdAuthCodeSms::length() const
{
    return m_length.value();
}

void QTdAuthCodeSms::unmarshalJson(const QJsonObject &json)
{
    if (json.contains("length")) {
        m_length = json["length"];
        emit lengthChanged();
    }
    QTdAuthCode::unmarshalJson(json);
}

QTdAuthCodeCall::QTdAuthCodeCall(QObject *parent) : QTdAuthCode(parent),
    m_length(0)
{
    setType(AUTHENTICATION_CODE_TYPE_CALL);
}

QString QTdAuthCodeCall::qmlLength() const
{
    return m_length.toQmlValue();
}

qint32 QTdAuthCodeCall::length() const
{
    return m_length.value();
}

void QTdAuthCodeCall::unmarshalJson(const QJsonObject &json)
{
    if (json.contains("length")) {
        m_length = json["length"];
        emit lengthChanged();
    }
    QTdAuthCode::unmarshalJson(json);
}

QTdAuthCodeFlashCall::QTdAuthCodeFlashCall(QObject *parent) : QTdAuthCode(parent)
{
    setType(AUTHENTICATION_CODE_TYPE_FLASH_CALL);
}

QString QTdAuthCodeFlashCall::pattern() const
{
    return m_pattern;
}

void QTdAuthCodeFlashCall::unmarshalJson(const QJsonObject &json)
{

    if (json.contains("pattern")) {
        m_pattern = json["pattern"].toString();
        emit patternChanged();
    }
    QTdAuthCode::unmarshalJson(json);
}

QTdAuthCodeInfo::QTdAuthCodeInfo(QObject *parent) : QAbstractTdObject(parent),
    m_timeout(0), m_type(0), m_nextType(0)
{
}

QString QTdAuthCodeInfo::qmlTimeout() const
{
    return m_timeout.toQmlValue();
}

qint32 QTdAuthCodeInfo::timeout() const
{
    return m_timeout.value();
}

QTdAuthCode *QTdAuthCodeInfo::type() const
{
    return m_type;
}

QTdAuthCode *QTdAuthCodeInfo::nextType() const
{
    return m_nextType;
}

void QTdAuthCodeInfo::unmarshalJson(const QJsonObject &json)
{
    m_timeout = json["timeout"];
    if (m_type) {
        delete m_type;
        m_type = 0;
    }
    m_type = QTdAuthCodeInfo::create(json["type"].toObject(), this);
    if (m_nextType) {
        delete m_nextType;
        m_nextType = 0;
    }
    m_nextType = QTdAuthCodeInfo::create(json["next_type"].toObject(), this);
    emit infoChanged();
}

QTdAuthCode *QTdAuthCodeInfo::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    if (type == QStringLiteral("authenticationCodeTypeSms")) {
        QTdAuthCodeSms *sms = new QTdAuthCodeSms(parent);
        sms->unmarshalJson(json);
        return sms;
    } else if (type == QStringLiteral("authenticationCodeTypeTelegramMessage")) {
        QTdAuthCodeTelegramMessage *msg = new QTdAuthCodeTelegramMessage(parent);
        msg->unmarshalJson(json);
        return msg;
    } else if (type == QStringLiteral("authenticationCodeTypeCall")) {
        QTdAuthCodeCall *msg = new QTdAuthCodeCall(parent);
        msg->unmarshalJson(json);
        return msg;
    } else if (type == QStringLiteral("authenticationCodeTypeFlashCall")) {
        QTdAuthCodeFlashCall *msg = new QTdAuthCodeFlashCall(parent);
        msg->unmarshalJson(json);
        return msg;
    }
    return Q_NULLPTR;
}
