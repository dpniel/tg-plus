#include "qtdauthstatefactory.h"
#include <QDebug>

QTdAuthState *QTdAuthStateFactory::create(const QJsonObject &data, QObject *parent)
{
    const QJsonObject state = data["authorization_state"].toObject();
    const QString type = state["@type"].toString();
    qDebug() << "[AUTHSTATE] " << type;
    QTdAuthState *stateObj = Q_NULLPTR;
    if (type == "authorizationStateWaitTdlibParameters") {
        stateObj = new QTdAuthStateWaitParams(parent);
    } else if (type == "authorizationStateWaitEncryptionKey") {
        stateObj = new QTdAuthStateWaitEncryptionKey(parent);
    } else if (type == "authorizationStateWaitPhoneNumber") {
        stateObj = new QTdAuthStateWaitPhoneNumber(parent);
    } else if (type == "authorizationStateWaitCode") {
        stateObj = new QTdAuthStateWaitCode(parent);
    } else if (type == "authorizationStateReady") {
        stateObj = new QTdAuthStateReady(parent);
    } else if (type == "authorizationStateLoggingOut") {
        stateObj = new QTdAuthStateLoggingOut(parent);
    } else if (type == "authorizationStateClosing") {
        stateObj = new QTdAuthStateClosing(parent);
    } else if (type == "authorizationStateClosed") {
        stateObj = new QTdAuthStateClosed(parent);
    } else if (type == "authorizationStateWaitPassword") {
        stateObj = new QTdAuthStatePassword(parent);
    } else {
        qWarning() << "Unknown auth state type: " << type;
    }

    if (stateObj) {
        stateObj->unmarshalJson(state);
    }
    return stateObj;
}
