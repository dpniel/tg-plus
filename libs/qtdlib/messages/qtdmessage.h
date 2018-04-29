#ifndef QTDMESSAGE_H
#define QTDMESSAGE_H

#include <QObject>
#include <QDateTime>
#include "common/qabstractint64id.h"

class QTdMessage : public QAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QDateTime date READ qmlDate NOTIFY messageChanged)
public:
    explicit QTdMessage(QObject *parent = nullptr);

    QDateTime qmlDate() const;
    qint32 date() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void messageChanged();

public slots:

private:
    qint32 m_date;
};

#endif // QTDMESSAGE_H
