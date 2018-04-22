#include "qtdremotefile.h"

QTdRemoteFile::QTdRemoteFile(QObject *parent) : QAbstractTdObject(parent),
    m_isUploadingActive(false), m_isUploadingCompleted(false),
    m_uploadedSize(0)
{
    setType(REMOTE_FILE);
}

QString QTdRemoteFile::id() const
{
    return m_id;
}

bool QTdRemoteFile::isUploadingActive() const
{
    return m_isUploadingActive;
}

bool QTdRemoteFile::isUploadingCompleted() const
{
    return m_isUploadingCompleted;
}

QString QTdRemoteFile::qmlUploadedSize() const
{
    return m_uploadedSize.toQmlValue();
}

qint32 QTdRemoteFile::uploadedSize() const
{
    return m_uploadedSize.value();
}

void QTdRemoteFile::unmarshalJson(const QJsonObject &json)
{
    m_id = json["id"].toString();
    emit idChanged(m_id);
    m_isUploadingActive = json["is_uploading_active"].toBool();
    emit isUploadingActiveChanged(m_isUploadingActive);
    m_isUploadingCompleted = json["is_uploading_completed"].toBool();
    emit isUploadingCompletedChanged(m_isUploadingCompleted);
    m_uploadedSize = json["uploaded_size"];
    emit uploadedSizeChanged(m_uploadedSize.toQmlValue());
}
