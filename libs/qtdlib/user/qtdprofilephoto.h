#ifndef QTDPROFILEPHOTO_H
#define QTDPROFILEPHOTO_H

#include <QObject>

#include "common/qabstractint64id.h"
#include "files/qtdfile.h"

class QTdProfilePhoto : public QAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QTdFile* small READ small NOTIFY smallChanged)
    Q_PROPERTY(QTdFile* big READ big NOTIFY bigChanged)
public:
    explicit QTdProfilePhoto(QObject *parent = nullptr);

    /**
     * @brief A small (160x160) user profile photo
     */
    QTdFile* small() const;
    /**
     * @brief A big (640x640) user profile photo
     */
    QTdFile* big() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void smallChanged(QTdFile* small);
    void bigChanged(QTdFile* big);

private:
    QTdFile* m_small;
    QTdFile* m_big;

    // QAbstractTdObject interface
public:
};

#endif // QTDPROFILEPHOTO_H
