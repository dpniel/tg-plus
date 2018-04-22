#ifndef QTDREQUEST_H
#define QTDREQUEST_H

#include <QObject>
#include "qabstracttdobject.h"

class QTdRequest : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdRequest(QObject *parent = nullptr);
};

#endif // QTDREQUEST_H
