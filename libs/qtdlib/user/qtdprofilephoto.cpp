#include "qtdprofilephoto.h"
#include "files/qtdlocalfile.h"
#include "files/qtdremotefile.h"

QTdProfilePhoto::QTdProfilePhoto(QObject *parent) : QAbstractInt64Id(parent)
{
    setType(PROFILE_PHOTO);
}

QTdFile *QTdProfilePhoto::small() const
{
    return m_small;
}

QTdFile *QTdProfilePhoto::big() const
{
    return m_big;
}

void QTdProfilePhoto::unmarshalJson(const QJsonObject &json)
{
    m_small = new QTdFile(this);
    m_small->unmarshalJson(json["small"].toObject());
    emit smallChanged(m_small);
    m_big = new QTdFile(this);
    m_big->unmarshalJson(json["big"].toObject());
    emit bigChanged(m_big);
    QAbstractInt64Id::unmarshalJson(json);
}
