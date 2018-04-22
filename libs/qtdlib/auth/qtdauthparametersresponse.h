#ifndef QTDAUTHPARAMETERSRESPONSE_H
#define QTDAUTHPARAMETERSRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdAuthParametersResponse : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdAuthParametersResponse(QObject *parent = nullptr);

    void setParameters(QAbstractTdObject *params);

    QJsonObject marshalJson();

private:
    QJsonObject m_params;
};

#endif // QTDAUTHPARAMETERSRESPONSE_H
