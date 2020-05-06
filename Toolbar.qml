import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

RowLayout {
    signal newGame()
    signal quitApp()

    function setTime(t) {
        timerField.text = t
    }

    Button {
        id: newGameButton
        text: "New Game"
        onClicked: newGame()
    }

    Text {
        id: timerField
        Layout.fillWidth: true
    }

    Button {
        id: quitButton
        text: "Quit"
        onClicked: quitApp()
    }

    Shortcut {
        context: Qt.ApplicationShortcut
        sequence: ["Ctrl+N"]
        onActivated: newGame()
    }

    Shortcut {
        context: Qt.ApplicationShortcut
        sequence: [StandardKey.Close, "Ctrl+Q"]
        onActivated: quitApp()
    }
}
