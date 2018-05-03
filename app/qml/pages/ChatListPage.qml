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
        anchors{
            topMargin:units.gu(7)
            fill: parent
        }
        model: Telegram.chats.sortedList
        delegate: ListItem {
            height: layout.implicitHeight
            readonly property QTdChat chat: modelData
            // We need to explicitly open the chat
            // on click and then close again on pop.
            // Todo: move this to the flux api
//            onClicked: chat.openChat()
            // TODO: Move to a context action
//            onClicked: chat.isPinned ? chat.unpinChat() : chat.pinChat()
            ListItemLayout {
                id: layout
                title.text: chat.isPinned ? chat.title + " (pinned)" : chat.title
                // TODO: This should just be a `chat.lastMessage.summary` property that returns a correctly formatted
                // string representation of lastMessage
                subtitle.text: (chat.lastMessage && chat.lastMessage.sender) ? chat.lastMessage.sender.firstName : ""
                summary.text: chat.lastMessage ? Qt.formatDateTime(chat.lastMessage.date) : ""
                UbuntuShape {
                    height: units.gu(5)
                    width: height
                    source: Image {
                        source: chat.chatPhoto.small.local.path ? Qt.resolvedUrl("file://" + chat.chatPhoto.small.local.path) : ""
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
