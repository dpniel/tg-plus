#include "qtdlinkstatefactory.h"


QTdLinkState *QTdLinkStateFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    if (type == "linkStateNone") {
        return new QTdLinkStateNone(parent);
    } else if (type == "linkStateKnowsPhoneNumber") {
        return new QTdLinkStateKnowsPhoneNumber(parent);
    } else if (type == "linkStateIsContact") {
        return new QTdLinkStateIsContact(parent);
    } else {
        return new QTdLinkState(parent);
    }
}
