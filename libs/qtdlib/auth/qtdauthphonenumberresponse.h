#ifndef QTDAUTHPHONENUMBERRESPONSE_H
#define QTDAUTHPHONENUMBERRESPONSE_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdAuthPhoneNumberResponse : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdAuthPhoneNumberResponse(QObject *parent = nullptr);

    void setPhoneNumber(const QString &number);

    QJsonObject marshalJson();
private:
    QString m_number;
};

#endif // QTDAUTHPHONENUMBERRESPONSE_H
