#include "qtdauthencryptionkeyresponse.h"

QTdAuthEncryptionKeyResponse::QTdAuthEncryptionKeyResponse(QObject *parent) : QTdRequest(parent)
{
}

void QTdAuthEncryptionKeyResponse::setKey(const QString &key)
{
    m_key = key;
}

QJsonObject QTdAuthEncryptionKeyResponse::marshalJson()
{
    return QJsonObject{
        {"@type", "setDatabaseEncryptionKey"},
        {"new_encryption_key", m_key},
    };
}
