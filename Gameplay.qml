import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

GridLayout {
    id: gr
    width: 600
    height: 600

    columns: 10
    rows: 10

    columnSpacing: 0
    rowSpacing: 0

    property bool playing: false
    property int secondsLeft: 0

    function newGame() {
        playing = true
        secondsLeft = 360

        var newConfigs = helper.newGame()

        for(var i = 0; i < newConfigs.length; i++) {
            bricks.itemAt(i).config = newConfigs[i]
        }

        timer()
        light()
    }

    function light() {
        var bric = []
        var i

        for(i = 0; i < bricks.model; i++) {
            bric.push(bricks.itemAt(i).config)
        }

        var lights = helper.light(bric)

        for(i = 0; i < bricks.count; i++) {
            bricks.itemAt(i).light = lights[i]

        }
//        function light() {
//             var brickConfigs = []
//            for(var i = 0; i < bricks.count; i++)
//                brickConfigs.push(bricks.itemAt(i).config)
//            var brickLights = helper.light(brickConfigs)
//            for(var i = 0; i < brickLights.length; i++)
//                bricks.itemAt(i).light = brickLights[i]
//        }

        if(lights.indexOf(false) === -1) {
            playing = false
            winDialog.open()
        }
    }


    function timer() {
        var textTime = "Time left: " + String(Math.floor(secondsLeft / 60)) +
                ":" + String(secondsLeft % 60)
        toolbar.setTime(textTime)

        if(secondsLeft <= 0) {
            playing = false
            loseDialog.open()
        }
    }

    MessageDialog {
        id: winDialog

        title: "You won"
        text: "You won! It's all :/"
        onAccepted: newGame()
        visible: false
    }

    MessageDialog {
        id: loseDialog

        title: "You lose"
        text: "You lose. Again."
        onAccepted: newGame()
        visible: false
    }

    Timer {
        id: countdown
        interval: 1000
        repeat: true
        running: gameplay.playing
        triggeredOnStart: false
        onTriggered: {
            secondsLeft--
            timer()
        }
    }

    Repeater {
        id: bricks
        model: 100

        Bricks {
            onRotated: gr.light()
        }
    }

    Component.onCompleted: {
        newGame()
    }
}
