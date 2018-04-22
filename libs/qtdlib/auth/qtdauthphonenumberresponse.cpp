#include "qtdauthphonenumberresponse.h"

QTdAuthPhoneNumberResponse::QTdAuthPhoneNumberResponse(QObject *parent) : QTdRequest(parent)
{
}

void QTdAuthPhoneNumberResponse::setPhoneNumber(const QString &number)
{
    m_number = number;
}

QJsonObject QTdAuthPhoneNumberResponse::marshalJson()
{
    return QJsonObject {
        {"@type", "setAuthenticationPhoneNumber"},
        {"phone_number", m_number},
        {"allow_flash_call", false},
        {"is_current_phone_number", true}
    };
}
