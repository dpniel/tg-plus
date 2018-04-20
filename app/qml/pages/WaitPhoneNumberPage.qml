import QtQuick 2.4
import Ubuntu.Components 1.3
import QuickFlux 1.1
import "../actions"

Page {
    id: waitPhoneNumberPage

    header: PageHeader {
        title: "Phone Number"
    }

    TextField {
        id: textfield
        anchors.centerIn: parent
        text: ""
    }

    Button {
        anchors {
            top: textfield.bottom
            topMargin: untis.gu(1)
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: sendNumber.run({number: textfield.text})
    }

    AppScript {
       id: sendNumber
       script: {

           AuthAction.setPhoneNumber("+44", message.number);

           once(AuthKey.authPhoneNumberError, function(message) {
               errorLabel.text = message.error;
               exit(1);
           })

           once(AuthKey.authPhoneNumberAccepted, exit.bind(this,0))
       }
    }
}
