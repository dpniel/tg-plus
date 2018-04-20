import QtQuick 2.4
import QtQuick.Window 2.3
import Ubuntu.Components 1.3
import QuickFlux 1.1
import QTelegram 1.0
import "./stores"

Window {
    /**
     * Only show the window once we have reached a state
     * that has something to display.
     * TODO: Unless we want to show a progress spinner or something
     * during the AuthStateWaitTdParams and AuthStateWaitEncryptionKey
     * state???
     */
    visible: Telegram.auth.state > AuthState.WaitEncryptionKey
    width: units.gu(45)
    height: units.gu(75)

    MainView {
        id: root
        anchors.fill: parent
        visible: true
        PageStack {
            id: pageStack

        }
        AppListener {
            Filter {
                type: "pushToStack"
                onDispatched: {
                    pageStack.push(message.view)
                }
            }

            Filter {
                type: "replaceOnStack"
                onDispatched: {
                    if (pageStack.depth) {
                        pageStack.clear()
                    }
                    pageStack.push(message.view)
                }
            }
        }
    }
}
