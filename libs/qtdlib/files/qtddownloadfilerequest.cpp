#include "qtddownloadfilerequest.h"

QTdDownloadFileRequest::QTdDownloadFileRequest(QObject *parent) : QTdRequest(parent),
    m_priority(Low), m_fileId(0)
{
}

void QTdDownloadFileRequest::setPriority(const QTdDownloadFileRequest::Priority &priority)
{
    m_priority = priority;
}

void QTdDownloadFileRequest::setFileId(const qint32 &fileId)
{
    m_fileId = fileId;
}

QJsonObject QTdDownloadFileRequest::marshalJson()
{
    return QJsonObject{
        {"@type", "downloadFile"},
        {"file_id", m_fileId},
        {"priority", (qint32)m_priority},
    };
}
