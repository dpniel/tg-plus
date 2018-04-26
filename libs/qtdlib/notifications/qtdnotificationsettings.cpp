#include "qtdnotificationsettings.h"

QTdNotificationSettings::QTdNotificationSettings(QObject *parent) : QAbstractTdObject(parent),
    m_muteFor(0), m_showPreview(false)
{
    setType(NOTIFICATION_SETTINGS);
}

qint32 QTdNotificationSettings::muteFor() const
{
    return m_muteFor;
}

bool QTdNotificationSettings::showPreview() const
{
    return m_showPreview;
}

void QTdNotificationSettings::unmarshalJson(const QJsonObject &json)
{
    m_muteFor = qint32(json["mute_for"].toInt());
    emit muteForChanged(m_muteFor);

    m_showPreview = json["show_preview"].toBool();
    emit showPreviewChanged(m_showPreview);

    QAbstractTdObject::unmarshalJson(json);
}
