import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
    id: w

    visible: true

    minimumWidth: 604
    maximumWidth: 604
    width: 604


    minimumHeight: cl.height+4
    maximumHeight: cl.height+4
    height: cl.height+4

    title: qsTr("Light'em Up!")

    ColumnLayout {
        id: cl

        anchors.centerIn: w.contentItem
        spacing: 2

        Gameplay {
            id: gameplay
        }

        Toolbar {
            id: toolbar

            onNewGame: gameplay.newGame()
            onQuitApp: Qt.quit()
        }
    }
}
