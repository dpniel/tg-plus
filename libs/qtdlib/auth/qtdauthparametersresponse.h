#ifndef QTDAUTHPARAMETERSRESPONSE_H
#define QTDAUTHPARAMETERSRESPONSE_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdAuthParametersResponse : public QAbstractTdObject
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
