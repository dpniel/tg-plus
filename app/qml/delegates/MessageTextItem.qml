import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0
import "../components"

MessageItemBase {

    property QTdMessageText textContent: message.content

    Column {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        spacing: Suru.units.gu(2)
        TextEdit {
            id: textEdit
            width: parent.width
            height: contentHeight
            readOnly: true
            selectByMouse: true
            text: textContent.text.text
            color: Suru.foregroundColor
            selectedTextColor: Suru.highlightColor
            wrapMode: TextEdit.Wrap
            onLinkActivated: {
                console.log("Link activated: ", link)
                Qt.openUrlExternally(link)
            }
        }

        Loader {
            visible: textContent.webPage
            active: visible
            asynchronous: true
            height: childrenRect.height
            width: parent.width
            sourceComponent: Component {
                WebPagePreview {
                    preview: textContent.webPage
                }
            }
        }
    }

    // Only load the formatter if there are
    // entities to be formatted.
    Loader {
        id: formatter
        active: textContent.text.entities.count > 0
        asynchronous: true
        sourceComponent: Component {
            TextFormatter {
                codeColor: Suru.color(Suru.LightBlue, 0.8)
                linkColor: Suru.color(Suru.LightBlue)
                textDocument: textEdit.textDocument
                content: textContent.text
            }
        }
    }
}
