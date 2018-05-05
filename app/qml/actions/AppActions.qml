pragma Singleton
import QtQuick 2.8

Item {

    property alias auth: auth
    AuthAction {
        id: auth
    }

    property alias chat: chat
    ChatActions {
        id: chat
    }
}
