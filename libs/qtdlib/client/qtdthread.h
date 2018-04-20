#ifndef QTDTHREAD_H
#define QTDTHREAD_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include "qtdhandle.h"

/**
 * @brief The QTdWorker class
 *
 * This worker is designed to be run on a QThread and events
 * proxied back
 */
class QTdWorker : public QObject
{
    Q_OBJECT
public:
    explicit QTdWorker(QObject *parent = nullptr);
    ~QTdWorker();

signals:
    void recv(const QJsonObject &data);

public slots:
    void run();

private:
    QSharedPointer<Handle> m_tdlib;
};

#endif // QTDTHREAD_H
