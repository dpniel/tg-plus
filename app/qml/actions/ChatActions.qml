import QtQuick 2.4
import QuickFlux 1.1
import "./"

ActionCreator {
    signal setCurrentChat(var chat)
    signal closeCurrentChat()

    signal loadMoreMessages();
}
