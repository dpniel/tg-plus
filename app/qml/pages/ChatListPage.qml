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

        model: Telegram.users.model
        delegate: ListItem {
            height: layout.implicitHeight
            property QtObject user: model.qtObject
            ListItemLayout {
                id: layout
                title.text: user.username
                subtitle.text: user.firstName + " " + user.lastName
                summary.text: user.id

                Icon {
                    name: user.status.type === QTdUserStatus.USER_STATUS_ONLINE ? "ok" : "close"
                    height: units.gu(3)
                    width: height
                }
            }
        }
    }
}
