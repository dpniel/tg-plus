import QtQuick 2.4
import Ubuntu.Components 1.3
import QTelegram 1.0
import "../actions"
import "../stores"

Page {
    id: waitCodePage
    header: PageHeader {
        title: "Chat List"
    }
    ListView {
        anchors.fill: parent
        model: Telegram.chats.list
        delegate: ListItem {
            height: layout.implicitHeight
            property QTdChat chat: model.qtObject
            ListItemLayout {
                id: layout
                title.text: chat.title
                UbuntuShape {
                    height: units.gu(5)
                    width: height
                    source: Image {
                        source: Qt.resolvedUrl("file://" + chat.chatPhoto.small.local.path)
                    }
                    SlotsLayout.position: SlotsLayout.Leading
                }

                UbuntuShape {
                    height: units.gu(3)
                    width: units.gu(3)
                    color: UbuntuColors.green
                    visible: parseInt(chat.unreadCount) > 0
                    Label {
                        anchors.centerIn: parent
                        text: chat.unreadCount
                        color: "white"
                    }
                }
            }
        }
    }
}
