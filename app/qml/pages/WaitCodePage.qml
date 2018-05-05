import QtQuick 2.4
import Ubuntu.Components 1.3
import "../actions"

Page {
    id: waitCodePage

    header: PageHeader {
        title: "Enter Code"
    }

    TextField {
        id: codeField
        anchors.centerIn: parent

    }
    Button {
        anchors {
            top: codeField.bottom
            topMargin: units.gu(1)
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: AppActions.auth.setCode(codeField.text)
    }
}
