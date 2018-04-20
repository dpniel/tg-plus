#include "qabstracttdobject.h"

QAbstractTdObject::QAbstractTdObject(QObject *parent) : QObject(parent),
    m_type(UNKNOWN)
{
}

QAbstractTdObject::Type QAbstractTdObject::type() const {
    return m_type;
}

void QAbstractTdObject::unmarshalJson(const QJsonObject &json) {
    Q_UNUSED(json);
}

QJsonObject QAbstractTdObject::marshalJson() {
    return QJsonObject();
}

void QAbstractTdObject::setType(const QAbstractTdObject::Type type) {
    m_type = type;
    emit typeChanged(m_type);
}
