pragma Singleton
import QtQuick 2.4
import QuickFlux 1.1
import "./"

ActionCreator {

    /**
     * Phone number actions
     *
     * Designed to be used in an AppScript to encapsulate logic.
     *
     * example usage:
     *
     * AppScript {
     *    id: sendNumber
     *    script: {
     *        AuthAction.setPhoneNumber(textfield.text)
     *        once(AuthKey.authPhoneNumberError, function(message) {
     *            errorLabel.text = message.error;
     *            exit(1);
     *        }
     *        once(AuthKey.authPhoneNumberAccepted, exit.bind(this,0));
     *    }
     * }
     * Button { onClicked: sendNumber.run() }
     */
    signal setPhoneNumber(string dialcode, string phonenumber)
    signal authPhoneNumberError(string error)
    signal authPhoneNumberAccepted()

    /**
     * Auth code actions
     *
     * Designed to be used in an AppScript to encapsulate logic.
     *
     * example usage:
     *
     * AppScript {
     *    id: sendCode
     *    script: {
     *        AuthAction.setCode(textfield.text)
     *        once(AuthKey.authCodeError, function(message) {
     *            errorLabel.text = message.error;
     *            exit(1);
     *        }
     *        once(AuthKey.authCodeAccepted, exit.bind(this,0));
     *    }
     * }
     * Button { onClicked: sendCode.run() }
     */
    signal setCode(string code)
    signal authCodeAccepted()
    signal authCodeError(string error)

    /**
     * Auth password actions
     *
     * Designed to be used in an AppScript to encapsulate logic.
     *
     * example usage:
     *
     * AppScript {
     *    id: sendPassword
     *    script: {
     *        AuthAction.setPassword(textfield.text)
     *        once(AuthKey.authPasswordError, function(message) {
     *            errorLabel.text = message.error;
     *            exit(1);
     *        }
     *        once(AuthKey.authPasswordAccepted, exit.bind(this,0));
     *    }
     * }
     * Button { onClicked: sendCode.run() }
     */
    signal setPassword(string code)
    signal authPasswordAccepted()
    signal authPasswordError(string error)
}
