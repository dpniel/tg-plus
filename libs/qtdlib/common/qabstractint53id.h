#ifndef QABSTRACTINT53ID_H
#define QABSTRACTINT53ID_H

#include <QObject>
#include "qabstracttdobject.h"
#include "qtdint.h"

class QAbstractInt53Id : public QAbstractTdObject
{
    Q_OBJECT
    // We expose all ID's as strings to qml to make sure
    // all id bit lengths are passable. tdlib returns either
    // 32, 53 and 64 bit id's
    Q_PROPERTY(QString id READ qmlId NOTIFY idChanged)
public:
    explicit QAbstractInt53Id(QObject *parent = nullptr);

    qint64 id() const;
    QString qmlId() const;

    // QAbstractTdObject interface
    virtual void unmarshalJson(const QJsonObject &json);

    static QAbstractInt53Id *create(const QJsonObject &json, QObject *parent);

signals:
    void idChanged(int id);

private:
    QTdInt53 m_id;
};

#endif // QABSTRACTINT53ID_H
