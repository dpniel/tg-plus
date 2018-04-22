#ifndef QTDREMOTEFILE_H
#define QTDREMOTEFILE_H

#include <QObject>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"

class QTdRemoteFile : public QAbstractTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(bool isUploadingActive READ isUploadingActive NOTIFY isUploadingActiveChanged)
    Q_PROPERTY(bool isUploadingCompleted READ isUploadingCompleted NOTIFY isUploadingCompletedChanged)
    Q_PROPERTY(QString uploadedSize READ qmlUploadedSize NOTIFY uploadedSizeChanged)
public:
    explicit QTdRemoteFile(QObject *parent = nullptr);

    QString id() const;
    bool isUploadingActive() const;
    bool isUploadingCompleted() const;
    QString qmlUploadedSize() const;
    qint32 uploadedSize() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void idChanged(QString id);
    void isUploadingActiveChanged(bool isUploadingActive);
    void isUploadingCompletedChanged(bool isUploadingCompleted);
    void uploadedSizeChanged(QString uploadedSize);

private:
    QString m_id;
    bool m_isUploadingActive;
    bool m_isUploadingCompleted;
    QTdInt32 m_uploadedSize;
};

#endif // QTDREMOTEFILE_H
