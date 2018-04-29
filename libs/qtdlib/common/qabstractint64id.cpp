#include "qabstractint64id.h"
#include <QDebug>

QAbstractInt64Id::QAbstractInt64Id(QObject *parent): QAbstractTdObject(parent),
    m_id(0)
{
}

qint64 QAbstractInt64Id::id() const
{
    return m_id.value();
}

QString QAbstractInt64Id::qmlId() const
{
    return m_id.toQmlValue();
}

void QAbstractInt64Id::unmarshalJson(const QJsonObject &json)
{
    m_id = json["id"];
    emit idChanged(m_id.value());
    QAbstractTdObject::unmarshalJson(json);
}

QAbstractInt64Id *QAbstractInt64Id::create(const QJsonObject &json, QObject *parent)
{
    auto *obj = new QAbstractInt64Id(parent);
    obj->unmarshalJson(json);
    return obj;
}
