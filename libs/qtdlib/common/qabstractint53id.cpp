#include "qabstractint53id.h"

QAbstractInt53Id::QAbstractInt53Id(QObject *parent) : QAbstractTdObject(parent)
{

}

qint32 QAbstractInt53Id::id() const
{
    return m_id.value();
}

QString QAbstractInt53Id::qmlId() const
{
    return m_id.toQmlValue();
}

void QAbstractInt53Id::unmarshalJson(const QJsonObject &json)
{
    if (json.contains("id")) {
        m_id = json["id"];
    }
    QAbstractTdObject::unmarshalJson(json);
}

QAbstractInt53Id *QAbstractInt53Id::create(const QJsonObject &json, QObject *parent)
{
    auto *obj = new QAbstractInt53Id(parent);
    obj->unmarshalJson(json);
    return obj;
}
