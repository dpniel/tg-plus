#include "qtduserstatusfactory.h"
#include <QDebug>

QTdUserStatus *QTdUserStatusFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    qDebug() << "[USERSTATUSTYPE] " << type;
    QTdUserStatus *obj = Q_NULLPTR;
    if (type == "userStatusEmpty") {
        obj = new QTdUserStatusEmpty(parent);
    } else if (type == "userStatusLastMonth") {
        obj = new QTdUserStateLastMonth(parent);
    } else if (type == "userStatusLastWeek") {
        obj = new QTdUserStatusLastWeek(parent);
    } else if (type == "userStatusOffline") {
        obj = new QTdUserStatusOffline(parent);
    } else if (type == "userStatusOnline") {
        obj = new QTdUserStatusOnline(parent);
    } else if (type == "userStatusRecently") {
        obj = new QTdUserStatusRecently(parent);
    } else {
        qWarning() << "Unknown user status type: " << type;
    }

    if (obj) {
        obj->unmarshalJson(json);
    }
    return obj;
}
