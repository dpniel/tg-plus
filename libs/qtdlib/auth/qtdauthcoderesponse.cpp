#include "qtdauthcoderesponse.h"

QTdAuthCodeResponse::QTdAuthCodeResponse(QObject *parent) : QTdRequest(parent)
{

}

void QTdAuthCodeResponse::setCode(const QString &code)
{
    m_code = code;
}

QJsonObject QTdAuthCodeResponse::marshalJson()
{
    return QJsonObject{
        {"@type", "checkAuthenticationCode"},
        {"code", m_code},
        {"first_name", "Dan"},
        {"last_name", "Chapman"},
    };
}
