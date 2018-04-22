#include "qtdlocalfile.h"

QTdLocalFile::QTdLocalFile(QObject *parent) : QAbstractTdObject(parent),
    m_canBeDownloaded(false), m_canBeDeleted(false),
    m_isDownloadingActive(false), m_isDownloadingCompleted(false),
    m_prefixSize(0), m_size(0)
{
    setType(LOCAL_FILE);
}

QString QTdLocalFile::path() const
{
    return m_path;
}

bool QTdLocalFile::canBeDownloaded() const
{
    return m_canBeDownloaded;
}

bool QTdLocalFile::canBeDeleted() const
{
    return m_canBeDeleted;
}

bool QTdLocalFile::isDownloadingActive() const
{
    return m_isDownloadingActive;
}

bool QTdLocalFile::isDownloadingCompleted() const
{
    return m_isDownloadingCompleted;
}

QString QTdLocalFile::qmlDownloadedPrefixSize() const
{
    return m_prefixSize.toQmlValue();
}

qint32 QTdLocalFile::downloadedPrefixSize() const
{
    return m_prefixSize.value();
}

QString QTdLocalFile::qmlDownloadedSize() const
{
    return m_size.toQmlValue();
}

qint32 QTdLocalFile::downloadedSize() const
{
    return m_size.value();
}

void QTdLocalFile::unmarshalJson(const QJsonObject &json)
{
    m_path = json["path"].toString();
    emit pathChanged(m_path);
    m_canBeDownloaded = json["can_be_downloaded"].toBool();
    emit canBeDownloadedChanged(m_canBeDownloaded);
    m_canBeDeleted = json["can_be_deleted"].toBool();
    emit canBeDeletedChanged(m_canBeDeleted);
    m_isDownloadingActive = json["is_downloading_active"].toBool();
    emit isDownloadingActiveChanged(m_isDownloadingActive);
    m_isDownloadingCompleted = json["is_downloading_completed"].toBool();
    emit isDownloadingCompletedChanged(m_isDownloadingCompleted);
    m_prefixSize = json["downloaded_prefix_size"];
    emit downloadedPrefixSizeChanged();
    m_size = json["downloaded_size"];
    emit downloadedSizeChanged();
    QAbstractTdObject::unmarshalJson(json);
}
