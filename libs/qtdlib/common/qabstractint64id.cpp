#include "qabstractint64id.h"


QAbstractInt64Id::QAbstractInt64Id(QObject *parent): QAbstractTdObject(parent)
{

}

qint32 QAbstractInt64Id::id() const
{
    return m_id.value();
}

QString QAbstractInt64Id::qmlId() const
{
    return m_id.toQmlValue();
}

void QAbstractInt64Id::unmarshalJson(const QJsonObject &json)
{
    if (json.contains("id")) {
        m_id = json["id"];
    }
    QAbstractTdObject::unmarshalJson(json);
}

QAbstractInt64Id *QAbstractInt64Id::create(const QJsonObject &json, QObject *parent)
{
    auto *obj = new QAbstractInt64Id(parent);
    obj->unmarshalJson(json);
    return obj;
}
