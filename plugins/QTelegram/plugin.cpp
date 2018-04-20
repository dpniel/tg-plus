#include <QtQml>
#include <QtQml/QQmlContext>

#include "plugin.h"
#include "qtelegram.h"
#include "authmanager.h"
#include "users.h"

#include <auth/qtdauthstate.h>
#include <connections/qtdconnectionstate.h>
#include <user/qtduser.h>

void QTelegramPlugin::registerTypes(const char *uri) {
    //@uri QTelegram
    qmlRegisterSingletonType<QTelegram>(uri, 1, 0, "QTelegram", [](QQmlEngine*, QJSEngine*) -> QObject* { return new QTelegram; });

    qmlRegisterType<AuthState>(uri, 1, 0, "AuthState");
    qmlRegisterType<AuthParams>(uri, 1, 0, "AuthParams");

    // qtdlib common
    qmlRegisterUncreatableType<QAbstractTdObject>(uri, 1, 0, "QTdObject", "Base TD c++ class");

    // qtdlib auth
    qmlRegisterUncreatableType<QTdAuthState>(uri, 1, 0, "QTdAuthState", "Base TD auth state class");
    qmlRegisterUncreatableType<QTdAuthStateWaitParams>(uri, 1, 0, "QTdAuthStateWaitParams", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateWaitEncryptionKey>(uri, 1, 0, "QTdAuthStateWaitEncryptionKey", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateWaitPhoneNumber>(uri, 1, 0, "QTdAuthStateWaitPhoneNumber", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateWaitCode>(uri, 1, 0, "QTdAuthStateWaitCode", "c++ class");
    qmlRegisterUncreatableType<QTdAuthCodeInfo>(uri, 1, 0, "QTdAuthCodeInfo", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStatePassword>(uri, 1, 0, "QTdAuthStatePassword", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateReady>(uri, 1, 0, "QTdAuthStateReady", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateLoggingOut>(uri, 1, 0, "QTdAuthStateLoggingOut", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateClosing>(uri, 1, 0, "QTdAuthStateClosing", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateClosed>(uri, 1, 0, "QTdAuthStateClosed", "c++ class");

    // qtdlib connections
    qmlRegisterUncreatableType<QTdConnectionState>(uri, 1, 0, "QTdConnectionState", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateWaitingForNetwork>(uri, 1, 0, "QTdConnectionStateWaitingForNetwork", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateConnectingToProxy>(uri, 1, 0, "QTdConnectionStateConnectingToProxy", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateConnecting>(uri, 1, 0, "QTdConnectionStateConnecting", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateUpdating>(uri, 1, 0, "QTdConnectionStateUpdating", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateReady>(uri, 1, 0, "QTdConnectionStateReady", "c++ class");

    // qtdlib users
    qmlRegisterType<Users>(uri, 1, 0, "Users");

    qmlRegisterUncreatableType<QTdUser>(uri, 1, 0, "QTdUser", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatus>(uri, 1, 0, "QTdUserStatus", "Abstract status type");
    qmlRegisterUncreatableType<QTdUserStatusEmpty>(uri, 1, 0, "QTdUserStatusEmpty", "c++ class");
    qmlRegisterUncreatableType<QTdUserStateLastMonth>(uri, 1, 0, "QTdUserStateLastMonth", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusLastWeek>(uri, 1, 0, "QTdUserStatusLastWeek", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusOffline>(uri, 1, 0, "QTdUserStatusOffline", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusOnline>(uri, 1, 0, "QTdUserStatusOnline", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusRecently>(uri, 1, 0, "QTdUserStatusRecently", "c++ class");

}
