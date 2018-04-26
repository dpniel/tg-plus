#include "qtdint.h"


QJsonValue QTdInt32::toJsonValue() const
{
    return QJsonValue{int(_value)};
}

QString QTdInt32::toQmlValue() const
{
    return QString::number(_value);
}

qint32 QTdInt32::value() const
{
    return _value;
}


QJsonValue QTdInt53::toJsonValue() const
{
    return QJsonValue{double(_value)};
}

QString QTdInt53::toQmlValue() const
{
    return QString::number(_value);
}

qint64 QTdInt53::value() const
{
    return _value;
}

QJsonValue QTdInt64::toJsonValue() const
{
    return QJsonValue{QString::number(_value)};
}

QString QTdInt64::toQmlValue() const
{
    return QString::number(_value);
}

qint64 QTdInt64::value() const
{
    return _value;
}



