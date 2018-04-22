#ifndef QTDDOWNLOADFILEREQUEST_H
#define QTDDOWNLOADFILEREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

class QTdDownloadFileRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdDownloadFileRequest(QObject *parent = nullptr);

    enum Priority {
        Low = 1,
        Medium = 16,
        High = 32
    };
    Q_ENUM(Priority)

    void setPriority(const Priority &priority);
    void setFileId(const qint32 &fileId);

    QJsonObject marshalJson();

private:
    Priority m_priority;
    qint32 m_fileId;

};

#endif // QTDDOWNLOADFILEREQUEST_H
