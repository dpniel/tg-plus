#ifndef QTDLOCALFILE_H
#define QTDLOCALFILE_H

#include <QObject>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"

class QTdLocalFile : public QAbstractTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path NOTIFY pathChanged)
    Q_PROPERTY(bool canBeDownloaded READ canBeDownloaded NOTIFY canBeDownloadedChanged)
    Q_PROPERTY(bool canBeDeleted READ canBeDeleted NOTIFY canBeDeletedChanged)
    Q_PROPERTY(bool isDownloadingActive READ isDownloadingActive NOTIFY isDownloadingActiveChanged)
    Q_PROPERTY(bool isDownloadingCompleted READ isDownloadingCompleted NOTIFY isDownloadingCompletedChanged)
    Q_PROPERTY(QString downloadedPrefixSize READ qmlDownloadedPrefixSize NOTIFY downloadedPrefixSizeChanged)
    Q_PROPERTY(QString downloadedSize READ qmlDownloadedSize NOTIFY downloadedSizeChanged)
public:
    explicit QTdLocalFile(QObject *parent = nullptr);

    QString path() const;
    bool canBeDownloaded() const;
    bool canBeDeleted() const;
    bool isDownloadingActive() const;
    bool isDownloadingCompleted() const;

    QString qmlDownloadedPrefixSize() const;
    qint32 downloadedPrefixSize() const;

    QString qmlDownloadedSize() const;
    qint32 downloadedSize() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void pathChanged(QString path);
    void canBeDownloadedChanged(bool canBeDownloaded);
    void canBeDeletedChanged(bool canBeDeleted);
    void isDownloadingActiveChanged(bool isDownloadingActive);
    void isDownloadingCompletedChanged(bool isDownloadingCompleted);
    void downloadedPrefixSizeChanged();
    void downloadedSizeChanged();
private:
    QString m_path;
    bool m_canBeDownloaded;
    bool m_canBeDeleted;
    bool m_isDownloadingActive;
    bool m_isDownloadingCompleted;
    QTdInt32 m_prefixSize;
    QTdInt32 m_size;
};

#endif // QTDLOCALFILE_H
