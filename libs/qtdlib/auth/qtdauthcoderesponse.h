#ifndef QTDAUTHCODERESPONSE_H
#define QTDAUTHCODERESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdAuthCodeResponse : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdAuthCodeResponse(QObject *parent = nullptr);

    void setCode(const QString &code);

    QJsonObject marshalJson();

private:
    QString m_code;
};

#endif // QTDAUTHCODERESPONSE_H
