import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Ubuntu.Components 1.3 as UITK
import QTelegram 1.0
import "../actions"
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
        anchors.fill: parent ? parent : undefined
        ListView {
            id: msgList
            anchors.fill: parent
            model: Telegram.chats.messageList
            verticalLayoutDirection: ListView.BottomToTop
            delegate: ItemDelegate {
                property QTdMessage message: modelData
                height: layout.implicitHeight
                width: msgList.width
                UITK.ListItemLayout {
                    id: layout
                    title.text: message.summary
                    title.color: Suru.foregroundColor
                    summary.text: message.content.text.text
                    summary.color: Suru.foregroundColor
                }
            }
        }
    }
}
