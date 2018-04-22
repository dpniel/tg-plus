#ifndef QTDMESSAGE_H
#define QTDMESSAGE_H

#include <QObject>
#include "common/qabstractint64id.h"

class QTdMessage : public QAbstractInt64Id
{
    Q_OBJECT
public:
    explicit QTdMessage(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QTDMESSAGE_H
