import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Ubuntu.Components 1.3 as UITK
import QTelegram 1.0

Item {
    property QTdProfilePhoto photo: null

    UITK.UbuntuShape {
        anchors.fill: parent
        aspect: UITK.UbuntuShape.Flat
        source: Image {
            asynchronous: true
            source: photo && photo.small.local.path ? Qt.resolvedUrl("file://" + photo.small.local.path) : ""
        }
    }
}
