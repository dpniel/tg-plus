#ifndef QTDAUTHENCRYPTIONKEYRESPONSE_H
#define QTDAUTHENCRYPTIONKEYRESPONSE_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdAuthEncryptionKeyResponse : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdAuthEncryptionKeyResponse(QObject *parent = nullptr);

    void setKey(const QString &key);

    QJsonObject marshalJson();

private:
    QString m_key;
};

#endif // QTDAUTHENCRYPTIONKEYRESPONSE_H
