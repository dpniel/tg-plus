#include "qtdfile.h"
#include <QDebug>
#include "client/qtdclient.h"
#include "files/qtddownloadfilerequest.h"

QTdFile::QTdFile(QObject *parent) : QAbstractInt32Id(parent),
    m_size(0), m_expectedSize(0), m_local(0), m_remote(0)
{
    setType(FILE);
    connect(QTdClient::instance(), &QTdClient::updateFile, this, &QTdFile::handleUpdateFile);
}

qint32 QTdFile::size() const
{
    return m_size.value();
}

QString QTdFile::qmlSize() const
{
    return m_size.toQmlValue();
}

qint32 QTdFile::expectedSize() const
{
    return m_expectedSize.value();
}

QString QTdFile::qmlExpectedSize() const
{
    return m_expectedSize.toQmlValue();
}

QTdLocalFile *QTdFile::local() const
{
    return m_local;
}

QTdRemoteFile *QTdFile::remote() const
{
    return m_remote;
}

void QTdFile::unmarshalJson(const QJsonObject &json)
{
    if (m_local) {
        delete m_local;
        m_local = 0;
    }
    m_local = new QTdLocalFile(this);
    m_local->unmarshalJson(json["local"].toObject());
    if (m_remote) {
        delete m_remote;
        m_remote = 0;
    }
    m_remote = new QTdRemoteFile(this);
    m_remote->unmarshalJson(json["remote"].toObject());
    m_size = json["size"];
    m_expectedSize = json["expected_size"];
    QAbstractInt32Id::unmarshalJson(json);
    emit fileChanged();
}

void QTdFile::downloadFile()
{
    if (!m_local->canBeDownloaded()) {
        qDebug() << "Cannot download file";
        return;
    }
    QTdDownloadFileRequest *req = new QTdDownloadFileRequest();
    req->setFileId(this->id());
    req->setPriority(QTdDownloadFileRequest::Priority::Medium);
    QTdClient::instance()->send(req);
}

void QTdFile::handleUpdateFile(const QJsonObject &json)
{
    if (qint32(json["id"].toInt()) != this->id()) {
        return;
    }
    this->unmarshalJson(json);
}
