#include "qtdmessage.h"
#include <QDebug>
QTdMessage::QTdMessage(QObject *parent) : QAbstractInt64Id(parent),
    m_date(0)
{
    setType(MESSAGE);
}

QDateTime QTdMessage::qmlDate() const
{
    return QDateTime::fromTime_t(m_date);
}

qint32 QTdMessage::date() const
{
    return m_date;
}

void QTdMessage::unmarshalJson(const QJsonObject &json)
{
    m_date = qint32(json["date"].toInt());
    emit messageChanged();
    QAbstractInt64Id::unmarshalJson(json);
}
