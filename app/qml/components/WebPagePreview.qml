import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Ubuntu.Components 1.3 as UITK
import QTelegram 1.0

Item {
    property QTdWebPage preview: null

    visible: preview
    width: parent.width
    height: Math.max(previewImage.height, pageDescription.height)
    Rectangle {
        id: colorBlock
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: Suru.units.dp(3)
        color: Suru.neutralColor
    }

    RowLayout {
        anchors {
            left: colorBlock.right
            leftMargin: Suru.units.gu(1)
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }

        Column {
            id: pageDescription
            Layout.fillWidth: true

            Label {
                width: parent.width
                text: preview ? preview.title : ""
                Suru.textStyle: Suru.SecondaryText
                Suru.textLevel: Suru.Paragraph
                font.weight: Font.DemiBold
            }
            Label {
                width: parent.width
                text: preview ? preview.description : ""
                maximumLineCount: 3
                Suru.textStyle: Suru.TertiaryText
                Suru.textLevel: Suru.Caption
            }
        }

        UITK.UbuntuShape {
            id: previewImage
            aspect: UITK.UbuntuShape.Flat
            source: Image {
                asynchronous: true
                source: preview && preview.photo.sizes.count ? Qt.resolvedUrl("file://" + preview.photo.sizes.getFirst().photo.local.path) : ""
            }
            Layout.alignment: Qt.AlignTop

            MouseArea {
                anchors.fill: parent
                onClicked: Qt.openUrlExternally(preview.url)
            }
        }
    }
}
