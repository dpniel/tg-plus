#include "qabstractint32id.h"

QAbstractInt32Id::QAbstractInt32Id(QObject *parent) : QAbstractTdObject(parent)
{
}

qint32 QAbstractInt32Id::id() const
{
    return m_id.value();
}

QString QAbstractInt32Id::qmlId() const
{
    return m_id.toQmlValue();
}

void QAbstractInt32Id::unmarshalJson(const QJsonObject &json)
{
    if (json.contains("id")) {
        m_id = json["id"];
    }
    QAbstractTdObject::unmarshalJson(json);
}

QAbstractInt32Id *QAbstractInt32Id::create(const QJsonObject &json, QObject *parent)
{
    auto *obj = new QAbstractInt32Id(parent);
    obj->unmarshalJson(json);
    return obj;
}
