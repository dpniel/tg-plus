#ifndef QTDNOTIFICATIONSETTINGS_H
#define QTDNOTIFICATIONSETTINGS_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdNotificationSettings : public QAbstractTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 muteFor READ muteFor NOTIFY muteForChanged)
    Q_PROPERTY(bool showPreview READ showPreview NOTIFY showPreviewChanged)
public:
    explicit QTdNotificationSettings(QObject *parent = nullptr);

    qint32 muteFor() const;

    bool showPreview() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void muteForChanged(qint32 muteFor);

    void showPreviewChanged(bool showPreview);

private:
    qint32 m_muteFor;
    bool m_showPreview;
};

#endif // QTDNOTIFICATIONSETTINGS_H
