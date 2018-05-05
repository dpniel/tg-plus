import QtQuick 2.4
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QuickFlux 1.1
import QTelegram 1.0
import "./stores"

ApplicationWindow {
    Suru.theme: Suru.Dark
    /**
     * Only show the window once we have reached a state
     * that has something to display.
     * TODO: Unless we want to show a progress spinner or something
     * during the AuthStateWaitTdParams and AuthStateWaitEncryptionKey
     * state???
     */
    visible: Telegram.auth.state > AuthState.WaitEncryptionKey
    width: Suru.units.gu(45)
    height: Suru.units.gu(75)

    StackView {
        id: pageStack
        anchors.fill: parent
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
