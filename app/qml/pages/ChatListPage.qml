import QtQuick 2.4
import QtQuick.Controls 2.2
import Ubuntu.Components 1.3 as UITK
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0
import "../actions"
import "../stores"

Page {
    id: chatListPage
    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor
    header: UITK.PageHeader {
        title: "Chat List"

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }
    }

    ScrollView {
        anchors.fill: parent

        ListView {
            anchors{
                fill: parent
            }
            model: Telegram.chats.sortedList
            delegate: ItemDelegate {
                height: layout.implicitHeight
                width: parent.width
                readonly property QTdChat chat: modelData
                onClicked: {
                    AppActions.chat.setCurrentChat(chat)
                    pageStack.push("qrc:///pages/MessageListPage.qml")
                }

                // TODO: Move to a context action
                //            onClicked: chat.isPinned ? chat.unpinChat() : chat.pinChat()
                UITK.ListItemLayout {
                    id: layout
                    title.text: chat.isPinned ? chat.title + " (pinned)" : chat.title
                    title.color: Suru.foregroundColor
                    subtitle.text: chat.summary
                    subtitle.color: Suru.foregroundColor
                    summary.color: Suru.foregroundColor
                    //                summary.text: chat.lastMessage ? Qt.formatDateTime(chat.lastMessage.date) : ""
                    summary.text: {
                        switch (chat.chatType.type) {
                        case QTdChatType.CHAT_TYPE_BASIC_GROUP:
                        case QTdChatType.CHAT_TYPE_SUPERGROUP:
                            // TODO: why are supergroup members counts
                            // always 0??
                            return "Members: " + chat.memberCount
                        default:
                            return ""
                        }
                    }
                    UITK.UbuntuShape {
                        aspect: UITK.UbuntuShape.Flat
                        height: Suru.units.gu(5)
                        width: height
                        source: Image {
                            asynchronous: true
                            source: chat.chatPhoto.small.local.path ? Qt.resolvedUrl("file://" + chat.chatPhoto.small.local.path) : ""
                        }
                        UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                    }

                    UITK.UbuntuShape {
                        height: Suru.units.gu(2.5)
                        width: Suru.units.gu(2.5)
                        color: Suru.darkPositive
                        visible: chat.hasUnreadMessages
                        UITK.Label {
                            anchors.centerIn: parent
                            text: chat.unreadCount
                            color: "white"
                            textSize: UITK.Label.Small
                        }
                    }
                    UITK.UbuntuShape {
                        height: Suru.units.gu(2.5)
                        width: Suru.units.gu(2.5)
                        color: UITK.UbuntuColors.green
                        visible: chat.hasUnreadMentions
                        UITK.Label {
                            anchors.centerIn: parent
                            text: "@" + chat.unreadMentionCount
                            color: "white"
                            textSize: UITK.Label.Small
                        }
                        UITK.SlotsLayout.position: UITK.SlotsLayout.Last
                    }
                }
            }
        }
    }
}
