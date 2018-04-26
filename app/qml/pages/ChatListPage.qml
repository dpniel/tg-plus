import QtQuick 2.4
import Ubuntu.Components 1.3
import QTelegram 1.0
import "../actions"
import "../stores"

Page {
    id: chatListPage
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
                summary.text: {
                    switch (chat.chatType.type) {
                    case QTdChatType.CHAT_TYPE_BASIC_GROUP:
                    case QTdChatType.CHAT_TYPE_SUPERGROUP:
                        return "Members: " + chat.memberCount
                    default:
                        return ""
                    }
                }
                UbuntuShape {
                    height: units.gu(5)
                    width: height
                    source: Image {
                        source: Qt.resolvedUrl("file://" + chat.chatPhoto.small.local.path)
                    }
                    SlotsLayout.position: SlotsLayout.Leading
                }

                UbuntuShape {
                    height: units.gu(2.5)
                    width: units.gu(2.5)
                    color: UbuntuColors.green
                    visible: chat.hasUnreadMessages
                    Label {
                        anchors.centerIn: parent
                        text: chat.unreadCount
                        color: "white"
                        textSize: Label.Small
                    }
                }
                UbuntuShape {
                    height: units.gu(2.5)
                    width: units.gu(2.5)
                    color: UbuntuColors.green
                    visible: chat.hasUnreadMentions
                    Label {
                        anchors.centerIn: parent
                        text: "@" + chat.unreadMentionCount
                        color: "white"
                        textSize: Label.Small
                    }
                    SlotsLayout.position: SlotsLayout.Last
                }
            }
        }
    }
}
