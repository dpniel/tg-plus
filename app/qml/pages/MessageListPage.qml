import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Ubuntu.Components 1.3 as UITK
import QTelegram 1.0
import "../actions"
import "../delegates"
import "../stores"

Page {
    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor
    header: UITK.PageHeader {
        title: Telegram.chats.currentChat.title
        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }
        leadingActionBar.actions: [
            UITK.Action {
                iconName: "back"
                text: "Back"
                onTriggered: {
                    AppActions.chat.closeCurrentChat()
                    pageStack.pop()
                }
            }
        ]
    }

    ScrollView {
        anchors.fill: parent

        ListView {
            id: msgList
            anchors.fill: parent
            model: Telegram.chats.messageList
            verticalLayoutDirection: ListView.BottomToTop
            delegate: Item {
                id: messageDelegate
                width: parent.width
                height: childrenRect.height

                /**
                 * Instead of using a Loader and creating a new
                 * context which brings in alot of overhead for
                 * each delegate we just create the component
                 * manually.
                 */
                Component.onCompleted: {
                    var comp = Qt.createComponent(
                        delegateMap.findComponent(modelData.content.type),
                        messageDelegate
                    )
                    comp.createObject(messageDelegate, {message: modelData})
                }
            }

            /**
             * When we are near the top of the listview
             * we want to load more messages.
             * the visible area positioning goes from
             * 1.0 to 0.0 because we start at y end
             * so when we get below 0.02 we trigger another load action
             */
            visibleArea.onYPositionChanged: {
                if (visibleArea.yPosition < 0.02 && model.count > 20) {
                    AppActions.chat.loadMoreMessages()
                }
            }
        }
    }

    footer: Rectangle {
        id: input
        width: parent.width
        height: entry.height + Suru.units.gu(2)
        color: Suru.backgroundColor

        Rectangle {
            anchors {
                top: parent.top
                right: parent.right
                left: parent.left
            }
            height: Suru.units.dp(1)
            color: Suru.neutralColor
        }

        RowLayout {
            anchors.fill: parent
            anchors.margins: Suru.units.gu(1)

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                TextArea {
                    id: entry
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        right: parent.right
                    }
                }
            }
        }
    }
}
