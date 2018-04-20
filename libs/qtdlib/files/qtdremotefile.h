#ifndef QTDREMOTEFILE_H
#define QTDREMOTEFILE_H

#include <QObject>

class QTdRemoteFile : public QObject
{
    Q_OBJECT
public:
    explicit QTdRemoteFile(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QTDREMOTEFILE_H